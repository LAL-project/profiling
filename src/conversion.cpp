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
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// lal includes
#include <lal/generate/rand_ulab_rooted_trees.hpp>
#include <lal/linarr/C.hpp>
#include <lal/graphs/free_tree.hpp>
#include <lal/graphs/rooted_tree.hpp>
using namespace lal;
using namespace graphs;
using namespace linarr;

// common includes
#include "dir_to_undir_pp.hpp"
#include "time.hpp"

namespace profiling {
namespace dir_to_undir {

void output_total_time(double total, size_t num_calls, uint32_t n, uint32_t T) {
	cout << "Number of vertices: " << n << endl;
	cout << "Total execution time: " << time_to_str(total) << endl;
	cout << "    Time per graph: " << time_to_str(total/T) << endl;
	cout << "    Time per call: " << time_to_str(total/(num_calls*T)) << endl;
}

void dgraph_to_ugraph(size_t num_calls, uint32_t n, uint32_t T) {
	double total_time = 0.0;

	generate::rand_ulab_rooted_trees Gen(n);
	for (uint32_t t = 0; t < T; ++t) {
		const auto T = Gen.get_tree();
		const auto dG = static_cast<directed_graph>(T);

		for (size_t i = 0; i < num_calls; ++i) {
			const auto begin = now();
			const auto uG = dG.to_undirected();
			const auto end = now();
			total_time += elapsed_time(begin, end);
		}
	}

	output_total_time(total_time, num_calls, n, T);
}

void rtree_to_ftree(size_t num_calls, uint32_t n, uint32_t T) {
	double total_time = 0.0;

	generate::rand_ulab_rooted_trees Gen(n);
	for (uint32_t t = 0; t < T; ++t) {
		const auto rT = Gen.get_tree();

		for (size_t i = 0; i < num_calls; ++i) {
			const auto begin = now();
			const auto fT = rT.to_undirected();
			const auto end = now();
			total_time += elapsed_time(begin, end);
		}
	}

	output_total_time(total_time, num_calls, n, T);
}

} // -- namespace dir_to_undir

void conversion(int argc, char *argv[]) {
	dir_to_undir::dir_to_undir parser(argc, argv);
	{
	if (parser.parse_params() > 0) { return; }
	if (parser.check_errors() > 0) { return; }
	}

	const string mode = parser.get_mode();
	const uint32_t n = parser.get_n();
	const uint32_t T = parser.get_T();
	const uint32_t C = parser.get_C();

	if (mode == "dgraph_to_ugraph") {
		dir_to_undir::dgraph_to_ugraph(C, n, T);
	}
	if (mode == "rtree_to_ftree") {
		dir_to_undir::rtree_to_ftree(C, n, T);
	}
}

} // -- namespace profiling
