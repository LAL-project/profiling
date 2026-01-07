/***********************************************************************
 *
 * Profiling programs for LAL
 * Copyright (C) 2019 - 2026 Lluís Alemany Puig
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
#include <functional>
#include <iostream>
#include <string>

// lal includes
#include <lal/generate/rand_arrangements.hpp>
#include <lal/generate/rand_ulab_free_trees.hpp>
#include <lal/linarr/C/C.hpp>
#include <lal/graphs/free_tree.hpp>

// common includes
#include "time.hpp"
#include "linarr_C_pp.hpp"

namespace profiling {
namespace linarr_C {

void output_execution_time(
	const double total_ms, const uint64_t n, const uint64_t T, const uint64_t N
) noexcept
{
	std::cout << "Number of vertices (n)= " << n << '\n';
	std::cout << "Number of trees generated (T)= " << T << '\n';
	std::cout << "Number of arrangements generated (N)= " << N << '\n';
	std::cout << "Total execution time: " << profiling::time_to_str(total_ms)
			  << '\n';
	std::cout << "    Average (ms/tree): "
			  << profiling::time_to_str(total_ms / static_cast<double>(T))
			  << '\n';
	std::cout << "    Average (ms/tree*pi): "
			  << profiling::time_to_str(total_ms / static_cast<double>(T * N))
			  << '\n';
}

uint64_t profile_algo(
	const std::function<
		uint64_t(const lal::graphs::free_tree&, const lal::linear_arrangement&)>&
		A,
	const uint64_t n,
	const uint64_t T,
	const uint64_t N
) noexcept
{
	double total = 0.0;

	uint64_t asdf = 0;

	lal::generate::rand_ulab_free_trees Gen(n, 1234);

	for (uint64_t t = 0; t < T; ++t) {
		const lal::graphs::free_tree tree = Gen.get_tree();

		lal::generate::rand_arrangements RandArr(tree.get_num_nodes(), 1234);

		for (uint64_t i = 0; i < N; ++i) {
			// make the random arrangement
			const auto arr = RandArr.get_arrangement();

			const auto begin = profiling::now();
			auto res = A(tree, arr);
			const auto end = profiling::now();
			total += profiling::elapsed_time(begin, end);

			res += 3;
			res += 4;
			asdf += res;
		}
	}

	output_execution_time(total, n, T, N);
	return asdf;
}

void profile_algo_list(
	const std::function<std::vector<
		uint64_t>(const lal::graphs::free_tree&, const std::vector<lal::linear_arrangement>&)>&
		A,
	const uint64_t n,
	const uint64_t T,
	const uint64_t N
) noexcept
{
	double total = 0.0;

	lal::generate::rand_ulab_free_trees Gen(n, 1234);

	for (uint64_t t = 0; t < T; ++t) {
		const lal::graphs::free_tree tree = Gen.get_tree();

		lal::generate::rand_arrangements RandArr(tree.get_num_nodes(), 1234);

		std::vector<lal::linear_arrangement> rand_arr(N);
		for (uint64_t i = 0; i < N; ++i) {
			rand_arr[i] = RandArr.get_arrangement();
			;
		}

		const auto begin = profiling::now();
		auto res = A(tree, rand_arr);
		const auto end = profiling::now();
		total += profiling::elapsed_time(begin, end);

		res[0] += 3;
		res[1] += 4;
	}

	output_execution_time(total, n, T, N);
}

} // namespace linarr_C

void linarr_crossings(uint64_t argc, char *argv[]) noexcept
{
	linarr_C::linarr_C_pp parser(argc, argv);
	{
		if (parser.parse_params() > 0) {
			return;
		}
		if (parser.check_errors() > 0) {
			return;
		}
	}

	const std::string what = parser.get_algo();
	const uint64_t n = parser.get_n();
	const uint64_t T = parser.get_T();
	const uint64_t N = parser.get_N();

	// bruteforce
	if (what == "brute_force") {
		linarr_C::profile_algo(
			[](const lal::graphs::free_tree& t,
			   const lal::linear_arrangement& arr)
			{
				return num_crossings(
					t, arr, lal::linarr::algorithms_C::brute_force
				);
			},
			n,
			T,
			N
		);
	}
	else if (what == "brute_force_list") {
		linarr_C::profile_algo_list(
			[](const lal::graphs::free_tree& t,
			   const std::vector<lal::linear_arrangement>& arrs)
			{
				return num_crossings_list(
					t, arrs, lal::linarr::algorithms_C::brute_force
				);
			},
			n,
			T,
			N
		);
	}
	// dynamic programming
	else if (what == "dynamic_programming") {
		linarr_C::profile_algo(
			[](const lal::graphs::free_tree& t,
			   const lal::linear_arrangement& arr)
			{
				return num_crossings(
					t, arr, lal::linarr::algorithms_C::dynamic_programming
				);
			},
			n,
			T,
			N
		);
	}
	else if (what == "dynamic_programming_list") {
		linarr_C::profile_algo_list(
			[](const lal::graphs::free_tree& t,
			   const std::vector<lal::linear_arrangement>& arr)
			{
				return num_crossings_list(
					t, arr, lal::linarr::algorithms_C::dynamic_programming
				);
			},
			n,
			T,
			N
		);
	}
	// ladder
	else if (what == "ladder") {
		linarr_C::profile_algo(
			[](const lal::graphs::free_tree& t,
			   const lal::linear_arrangement& arr)
			{
				return num_crossings(t, arr, lal::linarr::algorithms_C::ladder);
			},
			n,
			T,
			N
		);
	}
	else if (what == "ladder_list") {
		linarr_C::profile_algo_list(
			[](const lal::graphs::free_tree& t,
			   const std::vector<lal::linear_arrangement>& arr)
			{
				return num_crossings_list(
					t, arr, lal::linarr::algorithms_C::ladder
				);
			},
			n,
			T,
			N
		);
	}
	// stack based
	else if (what == "stack_based") {
		linarr_C::profile_algo(
			[](const lal::graphs::free_tree& t,
			   const lal::linear_arrangement& arr)
			{
				return num_crossings(
					t, arr, lal::linarr::algorithms_C::stack_based
				);
			},
			n,
			T,
			N
		);
	}
	else if (what == "stack_based_list") {
		linarr_C::profile_algo_list(
			[](const lal::graphs::free_tree& t,
			   const std::vector<lal::linear_arrangement>& arr)
			{
				return num_crossings_list(
					t, arr, lal::linarr::algorithms_C::stack_based
				);
			},
			n,
			T,
			N
		);
	}
	else {
		std::cout << "Error:" << '\n';
		std::cout << "Unknown/Unhandled '" << what << "'." << '\n';
	}
}

} // namespace profiling
