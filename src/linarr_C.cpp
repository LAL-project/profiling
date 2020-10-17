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

namespace profile_linarr_C {

void output_execution_time(double total_ms, uint32_t n, uint32_t T, uint32_t N) {
	cout << "Number of vertices (n)= " << n << endl;
	cout << "Number of trees generated (T)= " << T << endl;
	cout << "Number of arrangements generated (N)= " << N << endl;
	cout << "Total execution time: " << profiling::time_to_str(total_ms) << endl;
	cout << "    Average (ms/tree): " << profiling::time_to_str(total_ms/T) << endl;
	cout << "    Average (ms/tree*pi): " << profiling::time_to_str(total_ms/(T*N)) << endl;
}

void profile_algo(
	const function<uint32_t (const free_tree&, const linear_arrangement&)>& A,
	uint32_t n, uint32_t T, uint32_t N, bool seed = true
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

	for (uint32_t t = 0; t < T; ++t) {
		const free_tree tree = Gen.make_rand_tree();

		for (uint32_t i = 0; i < N; ++i) {
			// make the random arrangement
			shuffle(arr.begin(), arr.end(), rand_gen);
			const auto begin = profiling::now();
			const auto res = A(tree, arr);
			const auto end = profiling::now();
			total += profiling::elapsed_time(begin, end);
		}
	}

	output_execution_time(total, n, T, N);
}

} // -- namespace profile_linarr_C

void profiling_linarr_C(int argc, char *argv[]) {
	if (argc < 2) {
		return;
	}
	const string what(argv[2]);
	const uint32_t n = atoi(argv[3]);
	const uint32_t T = atoi(argv[4]);
	const uint32_t N = atoi(argv[5]);

	if (what == "brute_force") {
		profile_linarr_C::profile_algo(
		[](const free_tree& t, const linear_arrangement& arr) -> uint32_t {
			return n_crossings(t, arr, algorithms_C::brute_force);
		},
		n, T, N
		);
	}
	else if (what == "dynamic_programming") {
		profile_linarr_C::profile_algo(
		[](const free_tree& t, const linear_arrangement& arr) -> uint32_t {
			return n_crossings(t, arr, algorithms_C::dynamic_programming);
		},
		n, T, N
		);
	}
	else if (what == "ladder") {
		profile_linarr_C::profile_algo(
		[](const free_tree& t, const linear_arrangement& arr) -> uint32_t {
			return n_crossings(t, arr, algorithms_C::ladder);
		},
		n, T, N
		);
	}
	else if (what == "stack_based") {
		profile_linarr_C::profile_algo(
		[](const free_tree& t, const linear_arrangement& arr) -> uint32_t {
			return n_crossings(t, arr, algorithms_C::stack_based);
		},
		n, T, N
		);
	}
	else {
		cout << "Error:" << endl;
		cout << "Unknown/Unhandled '" << what << "'." << endl;
	}
}
