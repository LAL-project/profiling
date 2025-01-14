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
#include <lal/graphs/undirected_graph.hpp>
#include <lal/properties/C_rla.hpp>

// common includes
#include "properties_variance_C_pp.hpp"
#include "time.hpp"

namespace profiling {
namespace properties_variance_C {

void output_execution_time(
	const double totalglobal_ms,
	const double totallocal_ms,
	const uint64_t n,
	const uint64_t R
) noexcept
{
	std::cout << "Number of vertices (n)= " << n << '\n';
	std::cout << "Number of replicas (R)= " << R << '\n';
	std::cout << "Total (global) execution time: "
			  << profiling::time_to_str(totalglobal_ms) << '\n';
	std::cout << "Total (local) execution time: "
			  << profiling::time_to_str(totallocal_ms) << '\n';
	std::cout << "    Average (ms/replica): "
			  << profiling::time_to_str(totallocal_ms / static_cast<double>(R))
			  << '\n';
}

} // namespace properties_variance_C

void properties_variance_C_graph(uint64_t argc, char *argv[]) noexcept
{
	properties_variance_C::properties_variance_C_pp parser(argc, argv);
	if (parser.parse_params() > 0) {
		return;
	}
	if (parser.check_errors() > 0) {
		return;
	}

	const bool reuse = parser.get_reuse();

	const std::size_t T = parser.get_R();

	if (parser.get_nK() > 0) {
		const uint64_t n = parser.get_nK();

		lal::graphs::undirected_graph g(n);
		for (lal::node u = 0; u < n; ++u) {
			for (lal::node v = u + 1; v < n; ++v) {
				g.add_edge(u, v);
			}
		}

		double totallocal = 0;
		const auto beginglobal = profiling::now();
		for (uint64_t t = 0; t < T; ++t) {
			const auto beginlocal = profiling::now();
			auto res = lal::properties::var_num_crossings(g, reuse);
			const auto endlocal = profiling::now();
			totallocal += profiling::elapsed_time(beginlocal, endlocal);

			if (res > 5) {
				res += 4;
			}
		}
		const auto endglobal = profiling::now();
		const double totalglobal =
			profiling::elapsed_time(beginglobal, endglobal);

		properties_variance_C::output_execution_time(
			totalglobal, totallocal, n, T
		);
	}
	if (parser.get_nKK_1() > 0) {
		const uint64_t n1 = parser.get_nKK_1();
		const uint64_t n2 = parser.get_nKK_2();

		lal::graphs::undirected_graph g(n1 + n2);
		for (lal::node u = 0; u < n1; ++u) {
			for (lal::node v = 0; v < n2; ++v) {
				g.add_edge(u, v);
			}
		}

		double totallocal = 0;
		const auto beginglobal = profiling::now();
		for (uint64_t t = 0; t < T; ++t) {
			const auto beginlocal = profiling::now();
			auto res = lal::properties::var_num_crossings(g, reuse);
			const auto endlocal = profiling::now();
			totallocal += profiling::elapsed_time(beginlocal, endlocal);

			if (res > 5) {
				res += 4;
			}
		}
		const auto endglobal = profiling::now();
		const double totalglobal =
			profiling::elapsed_time(beginglobal, endglobal);

		properties_variance_C::output_execution_time(
			totalglobal, totallocal, n1 + n2, T
		);
	}
}

} // namespace profiling
