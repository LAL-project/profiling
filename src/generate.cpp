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
#include "generate_pp.hpp"

namespace profiling {
namespace generate {

void output_execution_time(double total_ms, uint32_t n, uint32_t N, uint32_t R) {
	cout << "n= " << n << endl;
	cout << "N= " << N << endl;
	cout << "R= " << R << endl;
	cout << "Total execution time: " << profiling::time_to_str(total_ms) << endl;
	cout << "    Average (ms/replica): " << profiling::time_to_str(total_ms/R) << endl;
	cout << "    Average (ms/get_tree): " << profiling::time_to_str(total_ms/(R*N)) << endl;
}

template<class T, class GEN>
void profile_exhaustive(uint32_t n, uint32_t N, uint32_t R) {
	double total = 0.0;

	GEN Gen;
	for (uint32_t r = 0; r < R; ++r) {
		Gen.init(n);
		for (uint32_t i = 0; i < N and Gen.has_next(); ++i) {
			const auto begin = profiling::now();
			Gen.next();
			const T tree = Gen.get_tree();
			const auto end = profiling::now();
			total += profiling::elapsed_time(begin, end);
		}
	}

	output_execution_time(total, n, N, R);
}

template<class T, class GEN>
void profile_random(uint32_t n, uint32_t N, uint32_t R) {
	double total = 0.0;

	GEN Gen;
	for (uint32_t r = 0; r < R; ++r) {
		Gen.init(n);
		for (uint32_t i = 0; i < N; ++i) {
			const auto begin = profiling::now();
			const T tree = Gen.make_rand_tree();
			const auto end = profiling::now();
			total += profiling::elapsed_time(begin, end);
		}
	}

	output_execution_time(total, n, N, R);
}

} // -- namespace generate

void generate_trees(int argc, char *argv[]) {
	generate::generate_pp parser(argc, argv);
	{
	if (parser.parse_params() > 0) { return; }
	if (parser.check_errors() > 0) { return; }
	}

	const string& what = parser.get_gen_class();
	const uint32_t n = parser.get_n();
	const uint32_t N = parser.get_N();
	const uint32_t R = parser.get_R();

	if (what == "all_lab_free") {
		generate::profile_exhaustive<free_tree, all_lab_free_trees>(n, N, R);
	}
	else if (what == "all_lab_rooted") {
		generate::profile_exhaustive<rooted_tree, all_lab_rooted_trees>(n, N, R);
	}
	else if (what == "all_ulab_free") {
		generate::profile_exhaustive<free_tree, all_ulab_free_trees>(n, N, R);
	}
	else if (what == "all_ulab_rooted") {
		generate::profile_exhaustive<rooted_tree, all_ulab_rooted_trees>(n, N, R);
	}
	else if (what == "rand_lab_free") {
		generate::profile_random<free_tree, rand_lab_free_trees>(n, N, R);
	}
	else if (what == "rand_lab_rooted") {
		generate::profile_random<rooted_tree, rand_lab_rooted_trees>(n, N, R);
	}
	else if (what == "rand_ulab_free") {
		generate::profile_random<free_tree, rand_ulab_free_trees>(n, N, R);
	}
	else if (what == "rand_ulab_rooted") {
		generate::profile_random<rooted_tree, rand_ulab_rooted_trees>(n, N, R);
	}
	else {
		cout << "Error:" << endl;
		cout << "Unknown/Unhandled '" << what << "'." << endl;
	}
}

} // -- namespace profiling
