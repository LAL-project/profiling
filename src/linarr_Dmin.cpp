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
#include <lal/generate/rand_ulab_rooted_trees.hpp>
#include <lal/linarr/Dmin.hpp>
#include <lal/graphs/free_tree.hpp>
#include <lal/graphs/rooted_tree.hpp>
using namespace lal;
using namespace graphs;
using namespace linarr;

// common includes
#include "time.hpp"
#include "linarr_Dmin_pp.hpp"

namespace profiling {
namespace linarr_Dmin {

void output_execution_time(double total_ms, uint32_t n, uint32_t T) {
	cout << "Number of vertices (n)= " << n << endl;
	cout << "Number of trees generated (T)= " << T << endl;
	cout << "Total execution time: " << profiling::time_to_str(total_ms) << endl;
	cout << "    Average (ms/tree): " << profiling::time_to_str(total_ms/T) << endl;
}

template<class TREE, class GEN>
void profile_algo(
	const function<
		std::pair<uint32_t, linear_arrangement> (const TREE&)
	>& A,
	uint32_t n, uint32_t T
)
{
	double total = 0.0;

	GEN Gen(n);

	for (uint32_t t = 0; t < T; ++t) {
		const auto tree = Gen.get_tree();

		const auto begin = profiling::now();
		auto res = A(tree);
		const auto end = profiling::now();
		total += profiling::elapsed_time(begin, end);

		res.first += 3;
		res.first += 4;
	}

	output_execution_time(total, n, T);
}

} // -- namespace linarr_Dmin

void linarr_minimum_D(int argc, char *argv[]) {
	linarr_Dmin::linarr_Dmin_pp parser(argc, argv);
	{
	if (parser.parse_params() > 0) { return; }
	if (parser.check_errors() > 0) { return; }
	}

	const string what = parser.get_algo();
	const uint32_t n = parser.get_n();
	const uint32_t T = parser.get_T();

	if (what == "unconstrained_YS") {
		linarr_Dmin::profile_algo
		<free_tree, generate::rand_ulab_free_trees>
		(
		[](const free_tree& t) {
			return linarr::Dmin(t, linarr::algorithms_Dmin::Unconstrained_YS);
		},
		n, T
		);
	}
	if (what == "unconstrained_FC") {
		linarr_Dmin::profile_algo
		<free_tree, generate::rand_ulab_free_trees>
		(
		[](const free_tree& t) {
			return linarr::Dmin(t, linarr::algorithms_Dmin::Unconstrained_FC);
		},
		n, T
		);
	}
	else if (what == "projective") {
		linarr_Dmin::profile_algo
		<rooted_tree, generate::rand_ulab_rooted_trees>
		(
		[](const rooted_tree& t) {
			return linarr::Dmin(t, linarr::algorithms_Dmin::Projective);
		},
		n, T
		);
	}
	else if (what == "planar") {
		linarr_Dmin::profile_algo
		<free_tree, generate::rand_ulab_free_trees>
		(
		[](const free_tree& t) {
			return linarr::Dmin(t, linarr::algorithms_Dmin::Unconstrained_FC);
		},
		n, T
		);
	}
	else {
		cout << "Error:" << endl;
		cout << "Unknown/Unhandled '" << what << "'." << endl;
	}
}

} // -- namespace profiling
