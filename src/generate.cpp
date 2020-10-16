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
#include <iostream>
#include <string>
using namespace std;

// lal includes
#include <lal/generate.hpp>
using namespace lal;
using namespace graphs;
using namespace generate;

// common includes
#include "time.hpp"

void output_execution_time(double total_ms, uint32_t N) {
	cout << "Total execution time: " << profiling::time_to_str(total_ms) << endl;
	cout << "Average execution time: " << profiling::time_to_str(total_ms/N) << endl;
}

template<class T, class GEN>
void profile_all(uint32_t n, uint32_t N) {
	double total = 0.0;

	GEN Gen(n);
	for (uint32_t i = 0; i < N and Gen.has_next(); ++i) {
		const auto begin = profiling::now();
		Gen.next();
		const T tree = Gen.get_tree();
		const auto end = profiling::now();
		total += profiling::elapsed_time(begin, end);
	}

	output_execution_time(total, N);
}

template<class T, class GEN>
void profile_random(uint32_t n, uint32_t N) {
	double total = 0.0;

	GEN Gen(n);
	for (uint32_t i = 0; i < N; ++i) {
		const auto begin = profiling::now();
		const T tree = Gen.make_rand_tree();
		const auto end = profiling::now();
		total += profiling::elapsed_time(begin, end);
	}

	output_execution_time(total, N);
}

void profiling_generate(int argc, char *argv[]) {
	if (argc < 2) {
		return;
	}
	const string what(argv[2]);
	const uint32_t n = atoi(argv[3]);
	const uint32_t N = atoi(argv[4]);

	if (what == "all_lab_free") {
		profile_all<free_tree, all_lab_free_trees>(n, N);
	}
	else if (what == "all_lab_rooted") {
		profile_all<rooted_tree, all_lab_rooted_trees>(n, N);
	}
	else if (what == "all_ulab_free") {
		profile_all<free_tree, all_ulab_free_trees>(n, N);
	}
	else if (what == "all_ulab_rooted") {
		profile_all<rooted_tree, all_ulab_rooted_trees>(n, N);
	}
	else if (what == "rand_lab_free") {
		profile_random<free_tree, rand_lab_free_trees>(n, N);
	}
	else if (what == "rand_lab_rooted") {
		profile_random<rooted_tree, rand_lab_rooted_trees>(n, N);
	}
	else if (what == "rand_ulab_free") {
		profile_random<free_tree, rand_ulab_free_trees>(n, N);
	}
	else if (what == "rand_ulab_rooted") {
		profile_random<rooted_tree, rand_ulab_rooted_trees>(n, N);
	}
	else {
		cout << "Error:" << endl;
		cout << "Unknown/Unhandled '" << what << "'." << endl;
	}
}
