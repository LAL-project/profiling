/***********************************************************************
 *
 * Research on Linear Arrangements project
 * Copyright (C) 2019 - 2021 Lluís Alemany Puig
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
#include <functional>
#include <iostream>
#include <random>
#include <string>
using namespace std;

// lal includes
#include <lal/generate/rand_ulab_free_trees.hpp>
#include <lal/linarr/C.hpp>
#include <lal/graphs/free_tree.hpp>
using namespace lal;
using namespace graphs;
using namespace linarr;

// common includes
#include "time.hpp"
#include "linarr_C_pp.hpp"

namespace profiling {
namespace linarr_C {

void output_execution_time(double total_ms, uint64_t n, uint64_t T, uint64_t N) {
	cout << "Number of vertices (n)= " << n << endl;
	cout << "Number of trees generated (T)= " << T << endl;
	cout << "Number of arrangements generated (N)= " << N << endl;
	cout << "Total execution time: " << profiling::time_to_str(total_ms) << endl;
	cout << "    Average (ms/tree): " << profiling::time_to_str(total_ms/T) << endl;
	cout << "    Average (ms/tree*pi): " << profiling::time_to_str(total_ms/(T*N)) << endl;
}

uint64_t profile_algo(
	const function<uint64_t (const free_tree&, const linear_arrangement&)>& A,
	uint64_t n, uint64_t T, uint64_t N, bool seed = true
)
{
	double total = 0.0;

	std::mt19937 rand_gen;
	if (seed == 0) {
		random_device rd;
		rand_gen = mt19937(rd());
	}
	else {
		rand_gen = mt19937(seed);
	}

	linear_arrangement arr(n);
	std::iota(arr.begin(), arr.end(), 0);

	uint64_t asdf = 0;

	generate::rand_ulab_free_trees Gen(n);

	for (uint64_t t = 0; t < T; ++t) {
		const free_tree tree = Gen.get_tree();

		for (uint64_t i = 0; i < N; ++i) {
			// make the random arrangement
			shuffle(arr.begin(), arr.end(), rand_gen);
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
	const function<
		vector<uint64_t> (const free_tree&, const vector<linear_arrangement>&)
	>& A,
	uint64_t n, uint64_t T, uint64_t N, bool seed = true
)
{
	double total = 0.0;

	std::mt19937 rand_gen;
	if (seed == 0) {
		random_device rd;
		rand_gen = mt19937(rd());
	}
	else {
		rand_gen = mt19937(seed);
	}

	linear_arrangement arr(n);
	std::iota(arr.begin(), arr.end(), 0);

	generate::rand_ulab_free_trees Gen(n);

	for (uint64_t t = 0; t < T; ++t) {
		const free_tree tree = Gen.get_tree();

		vector<linear_arrangement> rand_arr(N);
		for (uint64_t i = 0; i < N; ++i) {
			// make the random arrangement
			shuffle(arr.begin(), arr.end(), rand_gen);
			rand_arr[i] = arr;
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

} // -- namespace linarr_C

void linarr_crossings(int argc, char *argv[]) {
	linarr_C::linarr_C_pp parser(argc, argv);
	{
	if (parser.parse_params() > 0) { return; }
	if (parser.check_errors() > 0) { return; }
	}

	const string what = parser.get_algo();
	const uint64_t n = parser.get_n();
	const uint64_t T = parser.get_T();
	const uint64_t N = parser.get_N();

	// bruteforce
	if (what == "brute_force") {
		linarr_C::profile_algo(
		[](const free_tree& t, const linear_arrangement& arr) {
			return num_crossings(t, arr, algorithms_C::brute_force);
		},
		n, T, N
		);
	}
	else if (what == "brute_force_list") {
		linarr_C::profile_algo_list(
		[](const free_tree& t, const vector<linear_arrangement>& arrs) {
			return num_crossings_list(t, arrs, algorithms_C::brute_force);
		},
		n, T, N
		);
	}
	// dynamic programming
	else if (what == "dynamic_programming") {
		linarr_C::profile_algo(
		[](const free_tree& t, const linear_arrangement& arr) {
			return num_crossings(t, arr, algorithms_C::dynamic_programming);
		},
		n, T, N
		);
	}
	else if (what == "dynamic_programming_list") {
		linarr_C::profile_algo_list(
		[](const free_tree& t, const vector<linear_arrangement>& arr) {
			return num_crossings_list(t, arr, algorithms_C::dynamic_programming);
		},
		n, T, N
		);
	}
	// ladder
	else if (what == "ladder") {
		linarr_C::profile_algo(
		[](const free_tree& t, const linear_arrangement& arr) {
			return num_crossings(t, arr, algorithms_C::ladder);
		},
		n, T, N
		);
	}
	else if (what == "ladder_list") {
		linarr_C::profile_algo_list(
		[](const free_tree& t, const vector<linear_arrangement>& arr) {
			return num_crossings_list(t, arr, algorithms_C::ladder);
		},
		n, T, N
		);
	}
	// stack based
	else if (what == "stack_based") {
		linarr_C::profile_algo(
		[](const free_tree& t, const linear_arrangement& arr) {
			return num_crossings(t, arr, algorithms_C::stack_based);
		},
		n, T, N
		);
	}
	else if (what == "stack_based_list") {
		linarr_C::profile_algo_list(
		[](const free_tree& t, const vector<linear_arrangement>& arr) {
			return num_crossings_list(t, arr, algorithms_C::stack_based);
		},
		n, T, N
		);
	}
	else {
		cout << "Error:" << endl;
		cout << "Unknown/Unhandled '" << what << "'." << endl;
	}
}

} // -- namespace profiling
