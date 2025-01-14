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

// lal includes
#include <lal/generate/tree_generator_type.hpp>
#include <lal/graphs/free_tree.hpp>
#include <lal/properties/tree_centroid.hpp>
#include <lal/properties/tree_centre.hpp>

// common includes
#include "time.hpp"
#include "properties_centroid_centre_pp.hpp"

namespace profiling {
namespace properties_centroid_centre {

void output_execution_time(
	const double totalglobal_ms,
	const double totallocal_ms,
	const uint64_t n,
	const uint64_t T
) noexcept
{
	std::cout << "Number of vertices (n)= " << n << '\n';
	std::cout << "Number of trees generated (T)= " << T << '\n';
	std::cout << "Total (global) execution time: "
			  << profiling::time_to_str(totalglobal_ms) << '\n';
	std::cout << "Total (local) execution time: "
			  << profiling::time_to_str(totallocal_ms) << '\n';
	std::cout << "    Average (ms/tree): "
			  << profiling::time_to_str(totallocal_ms / static_cast<double>(T))
			  << '\n';
}

} // namespace properties_centroid_centre

void properties_centroid_tree(uint64_t argc, char *argv[]) noexcept
{
	properties_centroid_centre::properties_centroid_centre_pp parser(
		argc, argv
	);
	{
		if (parser.parse_params() > 0) {
			return;
		}
		if (parser.check_errors() > 0) {
			return;
		}
	}

	const uint64_t n = parser.get_n();
	const uint64_t T = parser.get_T();

	double totallocal = 0.0;

	lal::generate::tree_generator_type_t<
		lal::generate::random_t,
		lal::generate::unlabelled_t,
		lal::graphs::free_tree>
		Gen(n, 1234);

	const auto beginglobal = profiling::now();
	for (uint64_t t = 0; t < T; ++t) {
		const auto tree = Gen.get_tree();

		const auto beginlocal = profiling::now();
		auto res = lal::properties::tree_centroid(tree);
		const auto endlocal = profiling::now();
		totallocal += profiling::elapsed_time(beginlocal, endlocal);

		res.first += 3;
		res.first += 4;
	}
	const auto endglobal = profiling::now();
	const double totalglobal = profiling::elapsed_time(beginglobal, endglobal);

	properties_centroid_centre::output_execution_time(
		totalglobal, totallocal, n, T
	);
}

void properties_centre_tree(uint64_t argc, char *argv[]) noexcept
{
	properties_centroid_centre::properties_centroid_centre_pp parser(
		argc, argv
	);
	{
		if (parser.parse_params() > 0) {
			return;
		}
		if (parser.check_errors() > 0) {
			return;
		}
	}

	const uint64_t n = parser.get_n();
	const uint64_t T = parser.get_T();

	double totallocal = 0.0;

	lal::generate::tree_generator_type_t<
		lal::generate::random_t,
		lal::generate::unlabelled_t,
		lal::graphs::free_tree>
		Gen(n, 1234);

	const auto beginglobal = profiling::now();
	for (uint64_t t = 0; t < T; ++t) {
		const auto tree = Gen.get_tree();

		const auto beginlocal = profiling::now();
		auto res = lal::properties::tree_centre(tree);
		const auto endlocal = profiling::now();
		totallocal += profiling::elapsed_time(beginlocal, endlocal);

		res.first += 3;
		res.first += 4;
	}
	const auto endglobal = profiling::now();
	const double totalglobal = profiling::elapsed_time(beginglobal, endglobal);

	properties_centroid_centre::output_execution_time(
		totalglobal, totallocal, n, T
	);
}

} // namespace profiling
