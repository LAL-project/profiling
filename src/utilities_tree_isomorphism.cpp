/***********************************************************************
 *
 * Research on Linear Arrangements project
 * Copyright (C) 2019,2020 Lluís Alemany Puig
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Contact:
 *
 *    Lluís Alemany Puig (lalemany@cs.upc.edu)
 *
 ***********************************************************************/

// C++ includes
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
using namespace std;

// lal includes
#include <lal/graphs/free_tree.hpp>
#include <lal/graphs/rooted_tree.hpp>
#include <lal/utilities/tree_isomorphism.hpp>
#include <lal/generate/all_ulab_free_trees.hpp>
#include <lal/generate/all_ulab_rooted_trees.hpp>
using namespace lal;
using namespace graphs;
using namespace generate;

#include "time.hpp"

#define to_uint32(x) static_cast<uint32_t>(x)

namespace profiling {

void relabel_edges(vector<edge>& edges, node& r) {
	const uint32_t n = to_uint32(edges.size() + 1);

	mt19937 gen(1234);

	vector<node> relab(n);
	iota(relab.begin(), relab.end(), 0);

	for (uint32_t i = 0; i < n; ++i) {
		shuffle(relab.begin(), relab.end(), gen);

		// relabel each vertex accoring to 'relab'
		for (edge& e : edges) {
			node& s = e.first;
			node& t = e.second;
			s = relab[s];
			t = relab[t];
		}
		r = relab[r];
	}
}

void shuffle_tree(vector<edge>& edges, rooted_tree& T) {
	node r = T.get_root();
	relabel_edges(edges, r);

	T.clear();

	T.init(to_uint32(edges.size() + 1));
	T.set_root(r);
	T.add_all_edges(edges);
	T.set_valid_orientation(true);
}

void shuffle_tree(vector<edge>& edges, free_tree& T) {
	T.clear();
	T.init(to_uint32(edges.size() + 1));

	node dummy = 0;
	relabel_edges(edges, dummy);
	T.add_all_edges(edges);
}

void output_info(uint32_t n, uint32_t N_relabs, uint32_t n_calls, double total_time) {
	cout << "Number of vertices: " << n << endl;
	cout << "Total calls: " << n_calls << endl;
	cout << "Total time: " << time_to_str(total_time) << endl;
	cout << "    Time per tree: " << time_to_str(total_time/N_relabs) << endl;
	cout << "    Time per call: " << time_to_str(total_time/n_calls) << endl;
}

// ground truth: ISOMORPHIC

template<class Tree, class GEN>
void pos_exh_test(uint32_t n, uint32_t N_relabs) {
	uint32_t n_calls = 0;
	double total_time = 0.0;

	Tree relab_tree;
	GEN Gen(n);

	while (Gen.has_next()) {
		Gen.next();
		const Tree cur_tree = Gen.get_tree();
		vector<edge> edges_cur = cur_tree.edges();
		if constexpr (is_base_of_v<directed_graph, Tree>) {
			relab_tree.init(n);
			relab_tree.set_root(cur_tree.get_root());
		}

		for (uint32_t N = 0; N < N_relabs; ++N) {
			relab_tree.clear();
			shuffle_tree(edges_cur, relab_tree);

			const auto begin = now();
			utilities::are_trees_isomorphic(cur_tree, relab_tree);
			const auto end = now();
			total_time += elapsed_time(begin, end);
		}

		n_calls += N_relabs;
	}

	output_info(n, N_relabs, n_calls, total_time);
}

// ground truth: NON-ISOMORPHIC

template<class Tree, class GEN>
void neg_exh_test(uint32_t n, uint32_t N_relabs) {

	if constexpr (is_base_of_v<undirected_graph, Tree>) {
		if (n > 21) {
			cerr << "ERROR" << endl;
			cerr << "    Using n>21 (n=" << n << ") is going to freeze the computer." << endl;
			cerr << "    Aborting." << endl;
			return;
		}
	}
	else if constexpr (is_base_of_v<directed_graph, Tree>) {
		if (n > 18) {
			cerr << "ERROR" << endl;
			cerr << "    Using n>18 (n=" << n << ") is going to freeze the computer." << endl;
			cerr << "    Aborting." << endl;
			return;
		}
	}

	vector<Tree> all_trees;
	GEN Gen(n);
	while (Gen.has_next()) {
		Gen.next();
		all_trees.push_back(Gen.get_tree());
	}

	uint32_t n_calls = 0;
	double total_time = 0.0;

	Tree relab_tree;
	for (size_t i = 0; i < all_trees.size(); ++i) {
		const Tree& ti = all_trees[i];
		for (size_t j = i + 1; j < all_trees.size(); ++j) {

			const Tree& tj = all_trees[j];
			vector<edge> edges_tj = tj.edges();
			if constexpr (is_base_of_v<directed_graph, Tree>) {
				relab_tree.init(n);
				relab_tree.set_root(tj.get_root());
			}

			for (uint32_t l = 0; l < N_relabs; ++l) {
				shuffle_tree(edges_tj, relab_tree);

				const auto begin = now();
				utilities::are_trees_isomorphic(ti, relab_tree);
				const auto end = now();
				total_time += elapsed_time(begin, end);
			}

			n_calls += N_relabs;
		}
	}

	output_info(n, N_relabs, n_calls, total_time);
}

void utilities_tree_isomorphism(int argc, char *argv[]) {
	if (argc != 6) {
		cout << "free positive   n r" << endl;
		cout << "free negative   n r" << endl;
		cout << "rooted positive n r" << endl;
		cout << "rooted negative n r" << endl;
		cout << endl;
		cout << "free/rooted positive/negative - profile the test for free/rooted" << endl;
		cout << "trees where the answer of the test is known to be positive/negative" << endl;
		cout << endl;
		cout << "    n: number of vertices" << endl;
		cout << "    r: number of times each tree's vertices will be relabelled" << endl;
		cout << endl;
		return;
	}

	const string tree_type(argv[2]);
	const string expected_answer(argv[3]);
	const uint32_t n = atoi(argv[4]);
	const uint32_t r = atoi(argv[5]);
	if (tree_type == "free") {
		if (expected_answer == "positive") {
			pos_exh_test<free_tree, all_ulab_free_trees>(n, r);
		}
		else {
			neg_exh_test<free_tree, all_ulab_free_trees>(n, r);
		}
	}
	else if (tree_type == "rooted") {
		if (expected_answer == "positive") {
			pos_exh_test<rooted_tree, all_ulab_rooted_trees>(n, r);
		}
		else {
			neg_exh_test<rooted_tree, all_ulab_rooted_trees>(n, r);
		}
	}
}

} // -- namespace profiling
