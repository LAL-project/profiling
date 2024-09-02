/***********************************************************************
 *
 * Profiling programs for LAL
 * Copyright (C) 2019 - 2024 Lluís Alemany Puig
 *
 * The full code is available at:
 *     https://github.com/LAL-project/profiling.git
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
 *    Lluís Alemany Puig (lluis.alemany.puig@upc.edu)
 *
 ***********************************************************************/

// C++ includes
#include <algorithm>
#include <iostream>
#include <random>
#include <string>

// lal includes
#include <lal/graphs/free_tree.hpp>
#include <lal/graphs/rooted_tree.hpp>
#include <lal/utilities/tree_isomorphism.hpp>
#include <lal/generate/all_ulab_free_trees.hpp>
#include <lal/generate/all_ulab_rooted_trees.hpp>
#include <lal/detail/macros/basic_convert.hpp>

#include "time.hpp"

namespace profiling {

void relabel_edges(std::vector<lal::edge>& edges, lal::node& r) {
	const uint64_t n = edges.size() + 1;

	std::mt19937 gen(1234);

	std::vector<lal::node> relab(n);
	std::iota(relab.begin(), relab.end(), 0);

	for (uint64_t i = 0; i < n; ++i) {
		shuffle(relab.begin(), relab.end(), gen);

		// relabel each vertex accoring to 'relab'
		for (lal::edge& e : edges) {
			lal::node& s = e.first;
			lal::node& t = e.second;
			s = relab[s];
			t = relab[t];
		}
		r = relab[r];
	}
}

void shuffle_tree(std::vector<lal::edge>& edges, lal::graphs::rooted_tree& T) {
	lal::node r = T.get_root();
	relabel_edges(edges, r);

	T.clear();

	T.init(edges.size() + 1);
	T.set_root(r);
	T.set_edges(edges);
}

void shuffle_tree(std::vector<lal::edge>& edges, lal::graphs::free_tree& T) {
	T.clear();
	T.init(edges.size() + 1);

	lal::node dummy = 0;
	relabel_edges(edges, dummy);
	T.set_edges(edges);
}

void output_info(uint64_t n, uint64_t N_relabs, uint64_t n_calls, double total_time) {
	std::cout << "Number of vertices: " << n << '\n';
	std::cout << "Total calls: " << n_calls << '\n';
	std::cout << "Total time: " << time_to_str(total_time) << '\n';
	std::cout << "    Time per tree: " << time_to_str(total_time/lal::detail::to_double(N_relabs)) << '\n';
	std::cout << "    Time per call: " << time_to_str(total_time/lal::detail::to_double(n_calls)) << '\n';
}

// ground truth: ISOMORPHIC

template<class tree_t, class GEN>
void pos_exh_test(uint64_t n, uint64_t N_relabs) {
	uint64_t n_calls = 0;
	double total_time = 0.0;

	tree_t relab_tree;
	GEN Gen(n);

	while (not Gen.end()) {
		const tree_t cur_tree = Gen.get_tree();
		Gen.next();

		std::vector<lal::edge> edges_cur = cur_tree.get_edges();
		if constexpr (std::is_base_of_v<lal::graphs::directed_graph, tree_t>) {
			relab_tree.init(n);
			relab_tree.set_root(cur_tree.get_root());
		}

		for (uint64_t N = 0; N < N_relabs; ++N) {
			relab_tree.clear();
			shuffle_tree(edges_cur, relab_tree);

			const auto begin = now();
			std::ignore = lal::utilities::are_trees_isomorphic(cur_tree, relab_tree);
			const auto end = now();
			total_time += elapsed_time(begin, end);
		}

		n_calls += N_relabs;
	}

	output_info(n, N_relabs, n_calls, total_time);
}

// ground truth: NON-ISOMORPHIC

template<class Tree, class GEN>
void neg_exh_test(uint64_t n, uint64_t N_relabs) {

	if constexpr (std::is_base_of_v<lal::graphs::undirected_graph, Tree>) {
		if (n > 21) {
			std::cerr << "ERROR" << '\n';
			std::cerr << "    Using n>21 (n=" << n << ") is going to freeze the computer." << '\n';
			std::cerr << "    Aborting." << '\n';
			return;
		}
	}
	else if constexpr (std::is_base_of_v<lal::graphs::directed_graph, Tree>) {
		if (n > 18) {
			std::cerr << "ERROR" << '\n';
			std::cerr << "    Using n>18 (n=" << n << ") is going to freeze the computer." << '\n';
			std::cerr << "    Aborting." << '\n';
			return;
		}
	}

	std::vector<Tree> all_trees;
	GEN Gen(n);
	while (not Gen.end()) {
		all_trees.push_back(Gen.get_tree());
		Gen.next();
	}

	uint64_t n_calls = 0;
	double total_time = 0.0;

	Tree relab_tree;
	for (size_t i = 0; i < all_trees.size(); ++i) {
		const Tree& ti = all_trees[i];
		for (size_t j = i + 1; j < all_trees.size(); ++j) {

			const Tree& tj = all_trees[j];
			std::vector<lal::edge> edges_tj = tj.get_edges();
			if constexpr (std::is_base_of_v<lal::graphs::directed_graph, Tree>) {
				relab_tree.init(n);
				relab_tree.set_root(tj.get_root());
			}

			for (uint64_t l = 0; l < N_relabs; ++l) {
				shuffle_tree(edges_tj, relab_tree);

				const auto begin = now();
				std::ignore = lal::utilities::are_trees_isomorphic(ti, relab_tree);
				const auto end = now();
				total_time += elapsed_time(begin, end);
			}

			n_calls += N_relabs;
		}
	}

	output_info(n, N_relabs, n_calls, total_time);
}

void utilities_tree_isomorphism(uint64_t argc, char *argv[]) {
	if (argc != 4) {
		std::cout << "free positive   n r" << '\n';
		std::cout << "free negative   n r" << '\n';
		std::cout << "rooted positive n r" << '\n';
		std::cout << "rooted negative n r" << '\n';
		std::cout << '\n';
		std::cout << "free/rooted positive/negative - profile the test for free/rooted" << '\n';
		std::cout << "trees where the answer of the test is known to be positive/negative" << '\n';
		std::cout << '\n';
		std::cout << "    n: number of vertices" << '\n';
		std::cout << "    r: number of times each tree's vertices will be relabelled" << '\n';
		std::cout << '\n';
		return;
	}

	const std::string tree_type(argv[0]);
	const std::string expected_answer(argv[1]);
	const uint64_t n = static_cast<uint64_t>(atoi(argv[2]));
	const uint64_t r = static_cast<uint64_t>(atoi(argv[3]));

	std::cout << "tree_type= " << tree_type << '\n';
	std::cout << "expected_answer= " << expected_answer << '\n';
	std::cout << "n= " << n << '\n';
	std::cout << "r= " << r << '\n';

	if (tree_type == "free") {
		if (expected_answer == "positive") {
			pos_exh_test<lal::graphs::free_tree, lal::generate::all_ulab_free_trees>(n, r);
		}
		else {
			neg_exh_test<lal::graphs::free_tree, lal::generate::all_ulab_free_trees>(n, r);
		}
	}
	else if (tree_type == "rooted") {
		if (expected_answer == "positive") {
			pos_exh_test<lal::graphs::rooted_tree, lal::generate::all_ulab_rooted_trees>(n, r);
		}
		else {
			neg_exh_test<lal::graphs::rooted_tree, lal::generate::all_ulab_rooted_trees>(n, r);
		}
	}
}

} // -- namespace profiling
