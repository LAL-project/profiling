/***********************************************************************
 *
 * Profiling programs for LAL
 * Copyright (C) 2019 - 2025 Lluís Alemany Puig
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

void relabel_edges(
	std::vector<lal::edge>& edges, lal::node& r, std::mt19937& gen
) noexcept
{
	const uint64_t n = edges.size() + 1;

	lal::detail::array<lal::node> relab(n);
	std::iota(relab.begin(), relab.end(), 0);

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

void shuffle_tree(
	std::vector<lal::edge>& edges,
	lal::graphs::rooted_tree& T,
	std::mt19937& gen
) noexcept
{
	lal::node r = T.get_root();
	relabel_edges(edges, r, gen);

	T.clear();

	T.init(edges.size() + 1);
	T.set_root(r);
	T.set_edges(edges);
}

void shuffle_tree(
	std::vector<lal::edge>& edges, lal::graphs::free_tree& T, std::mt19937& gen
) noexcept
{
	T.clear();
	T.init(edges.size() + 1);

	lal::node dummy = 0;
	relabel_edges(edges, dummy, gen);
	T.set_edges(edges);
}

void output_info(
	const uint64_t n,
	const uint64_t N_relabs,
	const uint64_t n_calls,
	const double total_time
) noexcept
{
	std::cout << "Number of vertices: " << n << '\n';
	std::cout << "Total calls: " << n_calls << '\n';
	std::cout << "Total time: " << time_to_str(total_time) << '\n';
	std::cout << "    Time per tree: "
			  << time_to_str(total_time / lal::detail::to_double(N_relabs))
			  << '\n';
	std::cout << "    Time per call: "
			  << time_to_str(total_time / lal::detail::to_double(n_calls))
			  << '\n';
}

// ground truth: ISOMORPHIC

template <class tree_t, class gen_t>
void pos_exh_test(const uint64_t n, const uint64_t N_relabs, std::mt19937& gen)
{
	uint64_t n_calls = 0;
	double total_time = 0.0;

	tree_t relab_tree;
	gen_t Gen(n);

	while (not Gen.end()) {
		const tree_t cur_tree = Gen.get_tree();
		Gen.next();

		std::vector<lal::edge> edges_cur = cur_tree.get_edges();
		if constexpr (std::is_base_of_v<lal::graphs::directed_graph, tree_t>) {
			relab_tree.init(n);
			relab_tree.set_root(cur_tree.get_root());
		}

		for (uint64_t N = 0; N < N_relabs; ++N) {
			shuffle_tree(edges_cur, relab_tree, gen);

			const auto begin = now();
			[[maybe_unused]] const bool r =
				lal::utilities::are_trees_isomorphic(cur_tree, relab_tree);
			const auto end = now();
			total_time += elapsed_time(begin, end);
		}

		n_calls += N_relabs;
	}

	output_info(n, N_relabs, n_calls, total_time);
}

// ground truth: NON-ISOMORPHIC

template <class tree_t, class gen_t>
void neg_exh_test(const uint64_t n, const uint64_t N_relabs, std::mt19937& gen)
{

	if constexpr (std::is_base_of_v<lal::graphs::undirected_graph, tree_t>) {
		if (n > 21) {
			std::cerr << "ERROR\n";
			std::cerr << "    Using n>21 (n=" << n
					  << ") is going to freeze the computer.\n";
			std::cerr << "    Aborting.\n";
			return;
		}
	}
	else if constexpr (std::is_base_of_v<lal::graphs::directed_graph, tree_t>) {
		if (n > 18) {
			std::cerr << "ERROR\n";
			std::cerr << "    Using n>18 (n=" << n
					  << ") is going to freeze the computer.\n";
			std::cerr << "    Aborting.\n";
			return;
		}
	}

	std::vector<tree_t> all_trees;
	gen_t Gen(n);
	while (not Gen.end()) {
		all_trees.push_back(Gen.get_tree());
		Gen.next();
	}

	uint64_t n_calls = 0;
	double total_time = 0.0;

	tree_t relab_tree;
	for (size_t i = 0; i < all_trees.size(); ++i) {
		const tree_t& ti = all_trees[i];
		for (size_t j = i + 1; j < all_trees.size(); ++j) {

			const tree_t& tj = all_trees[j];
			std::vector<lal::edge> edges_tj = tj.get_edges();
			if constexpr (std::is_base_of_v<
							  lal::graphs::directed_graph,
							  tree_t>) {
				relab_tree.init(n);
				relab_tree.set_root(tj.get_root());
			}

			for (uint64_t l = 0; l < N_relabs; ++l) {
				shuffle_tree(edges_tj, relab_tree, gen);

				const auto begin = now();
				std::ignore =
					lal::utilities::are_trees_isomorphic(ti, relab_tree);
				const auto end = now();
				total_time += elapsed_time(begin, end);
			}

			n_calls += N_relabs;
		}
	}

	output_info(n, N_relabs, n_calls, total_time);
}

void utilities_tree_isomorphism(uint64_t argc, char *argv[]) noexcept
{
	if (argc != 4) {
		// clang-format off
		std::cout << "free positive   n r\n";
		std::cout << "free negative   n r\n";
		std::cout << "rooted positive n r\n";
		std::cout << "rooted negative n r\n";
		std::cout << '\n';
		std::cout << "free/rooted positive/negative - profile the test for free/rooted\n";
		std::cout << "trees where the answer of the test is known to be positive/negative\n";
		std::cout << '\n';
		std::cout << "    n: number of vertices\n";
		std::cout << "    r: number of times each tree's vertices will be relabelled\n";
		std::cout << '\n';
		// clang-format on
		return;
	}

	std::mt19937 gen(1234);

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
			pos_exh_test<
				lal::graphs::free_tree,
				lal::generate::all_ulab_free_trees>(n, r, gen);
		}
		else {
			neg_exh_test<
				lal::graphs::free_tree,
				lal::generate::all_ulab_free_trees>(n, r, gen);
		}
	}
	else if (tree_type == "rooted") {
		if (expected_answer == "positive") {
			pos_exh_test<
				lal::graphs::rooted_tree,
				lal::generate::all_ulab_rooted_trees>(n, r, gen);
		}
		else {
			neg_exh_test<
				lal::graphs::rooted_tree,
				lal::generate::all_ulab_rooted_trees>(n, r, gen);
		}
	}
}

} // namespace profiling
