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
#include <lal/generate/tree_generator_type.hpp>
#include <lal/graphs/free_tree.hpp>
#include <lal/properties/tree_centroid.hpp>
using namespace lal;
using namespace graphs;

// common includes
#include "time.hpp"
#include "properties_centroid_pp.hpp"

namespace profiling {
namespace properties_centroid {

void output_execution_time(
	double totalglobal_ms, double totallocal_ms, uint32_t n, uint32_t T
)
{
	cout << "Number of vertices (n)= " << n << endl;
	cout << "Number of trees generated (T)= " << T << endl;
	cout << "Total (global) execution time: " << profiling::time_to_str(totalglobal_ms) << endl;
	cout << "Total (local) execution time: " << profiling::time_to_str(totallocal_ms) << endl;
	cout << "    Average (ms/tree): " << profiling::time_to_str(totallocal_ms/T) << endl;
}

} // -- namespace properties_centroid

void properties_centroid_tree(int argc, char *argv[]) {
	properties_centroid::properties_centroid_pp parser(argc, argv);
	{
	if (parser.parse_params() > 0) { return; }
	if (parser.check_errors() > 0) { return; }
	}

	const uint32_t n = parser.get_n();
	const uint32_t T = parser.get_T();

	double totallocal = 0.0;

	generate::tree_generator_type_t<
		generate::random_t,
		generate::unlabelled_t,
		free_tree
	> Gen(n, 1234);

	const auto beginglobal = profiling::now();
	for (uint32_t t = 0; t < T; ++t) {
		const auto tree = Gen.get_tree();

		const auto beginglobal = profiling::now();
		auto res = properties::get_centroid(tree);
		const auto endglobal = profiling::now();
		totallocal += profiling::elapsed_time(beginglobal, endglobal);

		res.first += 3;
		res.first += 4;
	}
	const auto endglobal = profiling::now();
	const double totalglobal = profiling::elapsed_time(beginglobal, endglobal);

	properties_centroid::output_execution_time(totalglobal, totallocal, n, T);
}

} // -- namespace profiling
