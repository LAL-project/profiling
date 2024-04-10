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
 *    Lluís Alemany Puig (lalemany@cs.upc.edu)
 *
 ***********************************************************************/

// C++ includes
#include <iostream>
#include <string>

// lal includes
#include <lal/generate/tree_generator_type.hpp>
#include <lal/graphs/conversions.hpp>
#include <lal/linarr/D/DMax.hpp>
#include <lal/graphs/free_tree.hpp>
#include <lal/graphs/rooted_tree.hpp>

// common includes
#include "time.hpp"
#include "linarr_DMax_pp.hpp"

namespace profiling {
namespace linarr_DMax {

void output_execution_time
(double totalglobal_ms, double totallocal_ms, uint64_t n, uint64_t T)
noexcept
{
	std::cout << "Number of vertices (n)= " << n << '\n';
	std::cout << "Number of trees generated (T)= " << T << '\n';
	std::cout << "Total (global) execution time: " << profiling::time_to_str(totalglobal_ms) << '\n';
	std::cout << "Total (local) execution time: " << profiling::time_to_str(totallocal_ms) << '\n';
	std::cout << "    Average (ms/tree): " << profiling::time_to_str(totallocal_ms/T) << '\n';
}

template <class tree_t, typename function_t>
double exe_algo(const tree_t& t, const function_t& A, uint64_t R) noexcept
{
	const auto beginlocal = profiling::now();
	for (uint64_t r = 0; r < R; ++r) {
		const auto res = A(t);
	}
	const auto endlocal = profiling::now();
	return profiling::elapsed_time(beginlocal, endlocal);
}

template <class tree_t, typename function_t>
void profile_algo(const function_t& A, uint64_t n, uint64_t T, uint64_t R) noexcept
{
	lal::generate::tree_generator_type_t<
		lal::generate::random_t,
		lal::generate::unlabelled_t,
		tree_t
	> Gen(n, 1234);
	Gen.deactivate_all_postprocessing_actions();

	double totallocal = 0.0;
	const auto beginglobal = profiling::now();
	for (uint64_t t = 0; t < T; ++t) {
		const auto tree = Gen.get_tree();
		totallocal += exe_algo(tree, A, R);
	}
	const auto endglobal = profiling::now();
	const double totalglobal = profiling::elapsed_time(beginglobal, endglobal);

	output_execution_time(totalglobal, totallocal, n, T);
}

} // -- namespace linarr_DMax

void linarr_maximum_D(uint64_t argc, char *argv[]) {
	linarr_DMax::linarr_DMax_pp parser(argc, argv);
	{
	if (parser.parse_params() > 0) { return; }
	if (parser.check_errors() > 0) { return; }
	}

	static const auto projective =
	[](const lal::graphs::rooted_tree& t) {
		return lal::linarr::max_sum_edge_lengths_projective(t);
	};
	static const auto planar =
	[](const lal::graphs::free_tree& t) {
		return lal::linarr::max_sum_edge_lengths_planar(t);
	};
	static const auto bipartite =
	[](const lal::graphs::free_tree& t) {
		return lal::linarr::max_sum_edge_lengths_bipartite(t);
	};
	static const auto onethistle =
	[](const lal::graphs::free_tree& t) {
		return lal::linarr::max_sum_edge_lengths_1_eq_thistle(t);
	};

	const std::string& what = parser.get_algo();
	const uint64_t R = parser.get_R();

	if (parser.get_mode() == "automatic") {
		const uint64_t n = parser.get_n();
		const uint64_t T = parser.get_T();

		if (what == "projective") {
			linarr_DMax::profile_algo<lal::graphs::rooted_tree>
			(projective, n, T, R);
		}
		else if (what == "planar") {
			linarr_DMax::profile_algo<lal::graphs::free_tree>
			(planar, n, T, R);
		}
		else if (what == "bipartite") {
			linarr_DMax::profile_algo<lal::graphs::free_tree>
			(bipartite, n, T, R);
		}
		else if (what == "1_eq_thistle") {
			linarr_DMax::profile_algo<lal::graphs::free_tree>
			(onethistle, n, T, R);
		}
		else {
			std::cout << "Error:" << '\n';
			std::cout << "Unknown/Unhandled '" << what << "'.\n";
		}
	}
	else if (parser.get_mode() == "manual") {
		const lal::head_vector& hv = parser.get_head_vector();
		const lal::graphs::rooted_tree rT =
			lal::graphs::from_head_vector_to_rooted_tree(hv);
		const lal::graphs::free_tree fT = rT.to_free_tree();

		double totallocal = 0.0;
		const auto beginglobal = profiling::now();

		if (what == "projective") {
			totallocal += linarr_DMax::exe_algo(rT, projective, R);
		}
		else if (what == "planar") {
			totallocal += linarr_DMax::exe_algo(fT, planar, R);
		}
		else if (what == "bipartite") {
			totallocal += linarr_DMax::exe_algo(fT, bipartite, R);
		}
		else if (what == "1_eq_thistle") {
			totallocal += linarr_DMax::exe_algo(fT, onethistle, R);
		}
		else {
			std::cout << "Error:" << '\n';
			std::cout << "Unknown/Unhandled '" << what << "'.\n";
		}

		const auto endglobal = profiling::now();
		const double totalglobal = profiling::elapsed_time(beginglobal, endglobal);
		linarr_DMax::output_execution_time(totalglobal, totallocal, fT.get_num_nodes(), 1);
	}
}

} // -- namespace profiling
