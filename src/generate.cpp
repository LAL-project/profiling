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
#include <iostream>
#include <string>

// lal includes
#include <lal/iterators/E_iterator.hpp>
#include <lal/generate.hpp>

// common includes
#include "time.hpp"
#include "generate_trees_pp.hpp"
#include "generate_arrangements_pp.hpp"

namespace profiling {
namespace generate {

template <class tree_t>
inline lal::edge gimme_edge(const tree_t& t) noexcept {
	lal::iterators::E_iterator it(t);
	it.next();
	return it.get_edge();
}

void output_execution_time_trees(double total_ms, uint64_t n, uint64_t N, uint64_t R) {
	std::cout << "n= " << n << '\n';
	std::cout << "N= " << N << '\n';
	std::cout << "R= " << R << '\n';
	std::cout << "Total execution time: " << profiling::time_to_str(total_ms) << '\n';
	std::cout << "    Average (ms/replica): " << profiling::time_to_str(total_ms/R) << '\n';
	std::cout << "    Average (ms/get_tree): " << profiling::time_to_str(total_ms/(R*N)) << '\n';
}

template <class tree_t, class gen_t>
void profile_exhaustive_trees(uint64_t n, uint64_t N, uint64_t R) noexcept {
	double total = 0.0;

	for (uint64_t r = 0; r < R; ++r) {
		gen_t Gen(n);
		Gen.deactivate_all_postprocessing_actions();
		for (uint64_t i = 0; i < N and not Gen.end(); ++i) {
			const auto begin = profiling::now();
			tree_t tree = Gen.get_tree();
			Gen.next();
			const auto end = profiling::now();
			total += profiling::elapsed_time(begin, end);
		}
		Gen.reset();
	}

	output_execution_time_trees(total, n, N, R);
}

template <class tree_t, class gen_t>
void profile_random_trees(uint64_t n, uint64_t N, uint64_t R) noexcept {
	double total = 0.0;

	for (uint64_t r = 0; r < R; ++r) {
		gen_t Gen(n, 1234);
		Gen.deactivate_all_postprocessing_actions();
		for (uint64_t i = 0; i < N; ++i) {
			const auto begin = profiling::now();
			tree_t tree = Gen.get_tree();
			const auto end = profiling::now();
			total += profiling::elapsed_time(begin, end);

#if defined DEBUG
			const auto hv = tree.get_head_vector();
			std::cout << hv[0];
			for (std::size_t j = 1; j < hv.size(); ++j) {
				std::cout << ' ' << hv[j];
			}
			std::cout << '\n';
#endif
		}
	}

	output_execution_time_trees(total, n, N, R);
}

} // -- namespace generate

void generate_trees(uint64_t argc, char *argv[]) {
	generate::generate_trees_pp parser(argc, argv);
	{
	if (parser.parse_params() > 0) { return; }
	if (parser.check_errors() > 0) { return; }
	}

	const std::string& what = parser.get_gen_class();
	const uint64_t n = parser.get_n();
	const uint64_t N = parser.get_N();
	const uint64_t R = parser.get_R();

	if (what == "all_lab_free") {
		generate::profile_exhaustive_trees<lal::graphs::free_tree, lal::generate::all_lab_free_trees>(n, N, R);
	}
	else if (what == "all_lab_rooted") {
		generate::profile_exhaustive_trees<lal::graphs::rooted_tree, lal::generate::all_lab_rooted_trees>(n, N, R);
	}
	else if (what == "all_ulab_free") {
		generate::profile_exhaustive_trees<lal::graphs::free_tree, lal::generate::all_ulab_free_trees>(n, N, R);
	}
	else if (what == "all_ulab_rooted") {
		generate::profile_exhaustive_trees<lal::graphs::rooted_tree, lal::generate::all_ulab_rooted_trees>(n, N, R);
	}
	else if (what == "rand_lab_free") {
		generate::profile_random_trees<lal::graphs::free_tree, lal::generate::rand_lab_free_trees>(n, N, R);
	}
	else if (what == "rand_lab_rooted") {
		generate::profile_random_trees<lal::graphs::rooted_tree, lal::generate::rand_lab_rooted_trees>(n, N, R);
	}
	else if (what == "rand_ulab_free") {
		generate::profile_random_trees<lal::graphs::free_tree, lal::generate::rand_ulab_free_trees>(n, N, R);
	}
	else if (what == "rand_ulab_rooted") {
		generate::profile_random_trees<lal::graphs::rooted_tree, lal::generate::rand_ulab_rooted_trees>(n, N, R);
	}
	else {
		std::cout << "Error:" << '\n';
		std::cout << "Unknown/Unhandled '" << what << "'." << '\n';
	}
}

// -------------------------------------------------------------------------- //

namespace generate {

void output_execution_time_arrangements
(double total_ms, uint64_t n, uint64_t R, uint64_t T, uint64_t N)
{
	std::cout << "n= " << n << '\n';
	std::cout << "R= " << R << '\n';
	std::cout << "T= " << T << '\n';
	std::cout << "N= " << N << '\n';
	std::cout << "Total execution time: "
		 << profiling::time_to_str(total_ms)
		 << '\n';
	std::cout << "    Average (ms/replica): "
		 << profiling::time_to_str(total_ms/R)
		 << '\n';
	std::cout << "    Average (ms/(replica*tree)): "
		 << profiling::time_to_str(total_ms/(R*T))
		 << '\n';
	std::cout << "    Average (ms/(replica*tree*arrangement)): "
		 << profiling::time_to_str(total_ms/(R*T*N))
		 << '\n';
}

template<class tree_type, class tree_randgen_type, class arr_gen_type>
void profile_exhaustive_arrangements
(uint64_t n, uint64_t R, uint64_t T, uint64_t N)
{
	double total = 0.0;

	for (uint64_t r = 0; r < R; ++r) {
		tree_randgen_type TreeGen(n);
		for (size_t i = 0; i < T; ++i) {
			const tree_type randtree = TreeGen.get_tree();

			const auto begin = profiling::now();
			size_t k = 0;
			arr_gen_type ArrGen(randtree);
			while (k < N and not ArrGen.end()) {
				auto arr = ArrGen.get_arrangement();
				arr.assign(0ULL, 1ULL);
				ArrGen.next();
				++k;
			}
			const auto end = profiling::now();
			total += profiling::elapsed_time(begin, end);
		}
	}

	output_execution_time_arrangements(total, n, R, T, N);
}

template<class tree_type, class tree_randgen_type, class arr_gen_type>
void profile_random_arrangements
(uint64_t n, uint64_t R, uint64_t T, uint64_t N)
{
	double total = 0.0;

	for (uint64_t r = 0; r < R; ++r) {
		tree_randgen_type TreeGen(n);
		for (size_t i = 0; i < T; ++i) {
			const tree_type randtree = TreeGen.get_tree();

			const auto begin = profiling::now();
			arr_gen_type ArrGen(randtree);
			for (size_t k = 0; k < N; ++k) {
				auto arr = ArrGen.get_arrangement();
				arr.assign(0ULL, 1ULL);
			}
			const auto end = profiling::now();
			total += profiling::elapsed_time(begin, end);
		}
	}

	output_execution_time_arrangements(total, n, R, T, N);
}

} // -- namespace generate

void generate_arrangements(uint64_t argc, char *argv[]) {
	generate::generate_arrangements_pp parser(argc, argv);
	{
	if (parser.parse_params() > 0) { return; }
	if (parser.check_errors() > 0) { return; }
	}

	const std::string& what = parser.get_gen_class();
	const uint64_t n = parser.get_n();
	const uint64_t R = parser.get_R();
	const uint64_t T = parser.get_T();
	const uint64_t N = parser.get_N();

	if (what == "all_arrangements") {
		generate::profile_exhaustive_arrangements
		<lal::graphs::free_tree, lal::generate::rand_ulab_free_trees, lal::generate::all_arrangements>
		(n, R, T, N);
	}
	else if (what == "all_projective_arrangements") {
		generate::profile_exhaustive_arrangements
		<lal::graphs::rooted_tree, lal::generate::rand_ulab_rooted_trees, lal::generate::all_projective_arrangements>
		(n, R, T, N);
	}
	else if (what == "all_planar_arrangements") {
		generate::profile_exhaustive_arrangements
		<lal::graphs::free_tree, lal::generate::rand_ulab_free_trees, lal::generate::all_planar_arrangements>
		(n, R, T, N);
	}
	else if (what == "rand_arrangements") {
		generate::profile_random_arrangements
		<lal::graphs::free_tree, lal::generate::rand_ulab_free_trees, lal::generate::rand_arrangements>
		(n, R, T, N);
	}
	else if (what == "rand_projective_arrangements") {
		generate::profile_random_arrangements
		<lal::graphs::rooted_tree, lal::generate::rand_ulab_rooted_trees, lal::generate::rand_projective_arrangements>
		(n, R, T, N);
	}
	else if (what == "rand_planar_arrangements") {
		generate::profile_random_arrangements
		<lal::graphs::free_tree, lal::generate::rand_ulab_free_trees, lal::generate::rand_planar_arrangements>
		(n, R, T, N);
	}
	else {
		std::cout << "Error:" << '\n';
		std::cout << "Unknown/Unhandled '" << what << "'." << '\n';
	}
}

} // -- namespace profiling
