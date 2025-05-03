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
#include <lal/generate/all_ulab_free_trees.hpp>
#include <lal/generate/all_ulab_rooted_trees.hpp>

#include <lal/detail/macros/basic_convert.hpp>
#include <lal/detail/utilities/tree_isomorphism.hpp>

#include "time.hpp"

typedef lal::detail::isomorphism::algorithm algorithm;
static constexpr auto string = lal::detail::isomorphism::algorithm::string;
static constexpr auto tuple = lal::detail::isomorphism::algorithm::tuple;

namespace profiling {

void relabel_edges(
	std::vector<lal::edge>& edges, lal::node& r, std::mt19937& gen
) noexcept
{
	const uint64_t n = edges.size() + 1;

	lal::detail::array<lal::node> relab(n);
	std::iota(relab.begin(), relab.end(), 0);

	std::shuffle(relab.begin(), relab.end(), gen);

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
	const uint64_t n,
	lal::node r,
	std::vector<lal::edge>& edges,
	lal::graphs::rooted_tree& T,
	std::mt19937& gen
) noexcept
{
	relabel_edges(edges, r, gen);

	T.clear();
	T.init(n);
	T.set_root(r);
	T.set_edges(edges);
}

void shuffle_tree(
	const uint64_t n,
	std::vector<lal::edge>& edges,
	lal::graphs::free_tree& T,
	std::mt19937& gen
) noexcept
{
	lal::node dummy = 0;
	relabel_edges(edges, dummy, gen);
	T.init(n);
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

template <algorithm algo, class tree_t, class gen_t>
void positive_exhaustive_test(
	const uint64_t n, const uint64_t N, const uint64_t T, std::mt19937& gen
)
{
	static constexpr bool is_rooted =
		std::is_same_v<lal::graphs::rooted_tree, tree_t>;

	uint64_t n_calls = 0;
	double total_time = 0.0;

	tree_t relab_tree;
	gen_t Gen(n);

	std::size_t idx = 0;
	while (not Gen.end() and idx < T) {
		const tree_t cur_tree = Gen.get_tree();
		Gen.next();

		std::vector<lal::edge> edges_cur = cur_tree.get_edges();

		for (uint64_t r = 0; r < N; ++r) {
			if constexpr (is_rooted) {
				shuffle_tree(
					n, cur_tree.get_root(), edges_cur, relab_tree, gen
				);
			}
			else {
				shuffle_tree(n, edges_cur, relab_tree, gen);
			}

			const auto begin = now();
			const bool res = lal::detail::are_trees_isomorphic<algo, true>(
				cur_tree, relab_tree
			);
			const auto end = now();
			total_time += elapsed_time(begin, end);

			if (not res) {
				std::cerr << "ERROR!\n";
				std::abort();
			}
		}

		n_calls += N;
		++idx;
	}

	output_info(n, N, n_calls, total_time);
}

// ground truth: NON-ISOMORPHIC

template <algorithm algo, class tree_t, class gen_t>
void negative_exhaustive_test(
	const uint64_t n, const uint64_t N, const uint64_t T, std::mt19937& gen
)
{
	static constexpr bool is_rooted =
		std::is_same_v<lal::graphs::rooted_tree, tree_t>;

	std::vector<tree_t> all_trees;
	{
		std::size_t idx = 0;
		gen_t Gen(n);
		while (not Gen.end() and idx < T) {
			all_trees.push_back(Gen.get_tree());
			Gen.next();
			++idx;
		}
		std::cout << "idx= " << idx << '\n';
	}

	uint64_t n_calls = 0;
	double total_time = 0.0;

	tree_t relab_tree;
	for (size_t i = 0; i < all_trees.size(); ++i) {
		const tree_t& ti = all_trees[i];
		for (size_t j = i + 1; j < all_trees.size(); ++j) {

			const tree_t& tj = all_trees[j];
			std::vector<lal::edge> edges_tj = tj.get_edges();

			for (uint64_t r = 0; r < N; ++r) {

				if constexpr (is_rooted) {
					shuffle_tree(n, ti.get_root(), edges_tj, relab_tree, gen);
				}
				else {
					shuffle_tree(n, edges_tj, relab_tree, gen);
				}

				const auto begin = now();
				const bool res = lal::detail::are_trees_isomorphic<algo, true>(
					ti, relab_tree
				);
				const auto end = now();
				total_time += elapsed_time(begin, end);

				if (res) {
					std::cerr << "ERROR!\n";
					std::abort();
				}
			}

			n_calls += N;
		}
	}

	output_info(n, N, n_calls, total_time);
}

void utilities_tree_isomorphism(uint64_t argc, char *argv[]) noexcept
{
	if (argc != 6) {
		// clang-format off
		std::cout << "    tree_type test_type num_vertices relabelings trees\n";
		std::cout << '\n';
		std::cout << "    algorithm:    string/tuple - the algorithm to profile\n";
		std::cout << "    tree_type:    free/rooted - profile the test for free/rooted trees\n";
		std::cout << "    test_type:    positive/negative - the answer of the test\n";
		std::cout << "    num_vertices: number of vertices of the tree\n";
		std::cout << "    relabelings:  number of times the vertices of a tree should be relabelled\n";
		std::cout << "    trees:        number of trees to use\n";
		std::cout << '\n';
		// clang-format on
		return;
	}

	std::mt19937 gen(1234);

	const std::string algorithm(argv[0]);
	const std::string tree_type(argv[1]);
	const std::string test_type(argv[2]);
	const uint64_t n = static_cast<uint64_t>(atoi(argv[3]));
	const uint64_t r = static_cast<uint64_t>(atoi(argv[4]));
	const uint64_t T = static_cast<uint64_t>(atoi(argv[5]));

	std::cout << "algorithm= " << algorithm << '\n';
	std::cout << "tree_type= " << tree_type << '\n';
	std::cout << "expected_answer= " << test_type << '\n';
	std::cout << "n= " << n << '\n';
	std::cout << "r= " << r << '\n';
	std::cout << "T= " << T << '\n';

	if (algorithm == "string") {
		if (tree_type == "free") {
			if (test_type == "positive") {
				positive_exhaustive_test<
					string,
					lal::graphs::free_tree,
					lal::generate::all_ulab_free_trees>(n, r, T, gen);
			}
			else {
				negative_exhaustive_test<
					string,
					lal::graphs::free_tree,
					lal::generate::all_ulab_free_trees>(n, r, T, gen);
			}
		}
		else if (tree_type == "rooted") {
			if (test_type == "positive") {
				positive_exhaustive_test<
					string,
					lal::graphs::rooted_tree,
					lal::generate::all_ulab_rooted_trees>(n, r, T, gen);
			}
			else {
				negative_exhaustive_test<
					string,
					lal::graphs::rooted_tree,
					lal::generate::all_ulab_rooted_trees>(n, r, T, gen);
			}
		}
	}
	else {
		if (tree_type == "free") {
			if (test_type == "positive") {
				positive_exhaustive_test<
					tuple,
					lal::graphs::free_tree,
					lal::generate::all_ulab_free_trees>(n, r, T, gen);
			}
			else {
				negative_exhaustive_test<
					tuple,
					lal::graphs::free_tree,
					lal::generate::all_ulab_free_trees>(n, r, T, gen);
			}
		}
		else if (tree_type == "rooted") {
			if (test_type == "positive") {
				positive_exhaustive_test<
					tuple,
					lal::graphs::rooted_tree,
					lal::generate::all_ulab_rooted_trees>(n, r, T, gen);
			}
			else {
				negative_exhaustive_test<
					tuple,
					lal::graphs::rooted_tree,
					lal::generate::all_ulab_rooted_trees>(n, r, T, gen);
			}
		}
	}
}

} // namespace profiling
