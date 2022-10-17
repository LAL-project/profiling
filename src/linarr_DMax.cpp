/***********************************************************************
 *
 * Profiling programs for LAL
 * Copyright (C) 2019 - 2022 Lluís Alemany Puig
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
 *    Lluís Alemany Puig (lalemany@cs.upc.edu)
 *
 ***********************************************************************/

// C++ includes
#include <functional>
#include <iostream>
#include <random>
#include <string>

// lal includes
#include <lal/generate/tree_generator_type.hpp>
#include <lal/linarr/DMax.hpp>
#include <lal/graphs/free_tree.hpp>
#include <lal/graphs/rooted_tree.hpp>

// common includes
#include "time.hpp"
#include "linarr_DMax_pp.hpp"

namespace profiling {
namespace linarr_DMax {

void output_execution_time(
	double totalglobal_ms, double totallocal_ms, uint64_t n, uint64_t T
)
{
	std::cout << "Number of vertices (n)= " << n << '\n';
	std::cout << "Number of trees generated (T)= " << T << '\n';
	std::cout << "Total (global) execution time: " << profiling::time_to_str(totalglobal_ms) << '\n';
	std::cout << "Total (local) execution time: " << profiling::time_to_str(totallocal_ms) << '\n';
	std::cout << "    Average (ms/tree): " << profiling::time_to_str(totallocal_ms/T) << '\n';
}

template<class TREE>
void profile_algo(
	const std::function<
		std::pair<uint64_t, lal::linear_arrangement> (const TREE&)
	>& A,
	uint64_t n, uint64_t T
)
{
	double totallocal = 0.0;

	lal::generate::tree_generator_type_t<
		lal::generate::random_t,
		lal::generate::unlabelled_t,
		TREE
	> Gen(n, 1234);
	Gen.deactivate_all_postprocessing_actions();

	const auto beginglobal = profiling::now();
	for (uint64_t t = 0; t < T; ++t) {
		const auto tree = Gen.get_tree();

		const auto beginglobal = profiling::now();
		auto res = A(tree);
		const auto endglobal = profiling::now();
		totallocal += profiling::elapsed_time(beginglobal, endglobal);

		res.first += 3;
		res.first += 4;
	}
	const auto endglobal = profiling::now();
	const double totalglobal = profiling::elapsed_time(beginglobal, endglobal);

	output_execution_time(totalglobal, totallocal, n, T);
}

} // -- namespace linarr_DMax

void linarr_maximum_D(int argc, char *argv[]) {
	linarr_DMax::linarr_DMax_pp parser(argc, argv);
	{
	if (parser.parse_params() > 0) { return; }
	if (parser.check_errors() > 0) { return; }
	}

	const std::string what = parser.get_algo();
	const uint64_t n = parser.get_n();
	const uint64_t T = parser.get_T();

	if (what == "projective") {
		linarr_DMax::profile_algo<lal::graphs::rooted_tree>
		(
		[](const lal::graphs::rooted_tree& t) {
			return lal::linarr::max_sum_edge_lengths_projective(t);
		},
		n, T
		);
	}
	else if (what == "planar") {
		linarr_DMax::profile_algo<lal::graphs::free_tree>
		(
		[](const lal::graphs::free_tree& t) {
			return lal::linarr::max_sum_edge_lengths_planar(t);
		},
		n, T
		);
	}
	else {
		std::cout << "Error:" << '\n';
		std::cout << "Unknown/Unhandled '" << what << "'." << '\n';
	}
}

} // -- namespace profiling
