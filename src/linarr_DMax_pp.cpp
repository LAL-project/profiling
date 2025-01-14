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

#include "linarr_DMax_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>

namespace profiling {
namespace linarr_DMax {

void linarr_DMax_pp::print_usage() const noexcept
{
	// clang-format off
	std::cout << "Profiling -- Calculation of minimum D\n";
	std::cout << "=====================================\n";
	std::cout << '\n';
	std::cout << "This program's options are the following:\n";
	std::cout << "    Those marked with [*] are mandatory for all execution modes.\n";
	std::cout << "    Those marked with [i] are mandatory for execution mode i.\n";
	std::cout << "    Those marked with [?] are optional.\n";
	std::cout << '\n';
	std::cout << "    [*]   -mode m\n";
	std::cout << "          Indicate the mode in which to execute the profiler.\n";
	std::cout << "          [1] automatic\n";
	std::cout << "          [2] manual\n";
	std::cout << '\n';
	std::cout << "    [1]   -n n\n";
	std::cout << "          Indicate the number of vertices of the trees.\n";
	std::cout << '\n';
	std::cout << "    [1]   -T T\n";
	std::cout << "          Indicate the number of trees to generate.\n";
	std::cout << '\n';
	std::cout << "    [2]   -hv k p_1 ... p_k\n";
	std::cout << "          Head vector of the tree.\n";
	std::cout << '\n';
	std::cout << "    [*]   -R r\n";
	std::cout << "          Number of replicas to execute the algorithm.\n";
	std::cout << '\n';
	std::cout << "    [*]   -algorithm A\n";
	std::cout << "          Indicate the algorithm to profile:\n";
	std::cout << '\n';
	for (const std::string& algo : m_allowed_algorithms) {
	std::cout << "          " << algo << '\n';
	}
	std::cout << '\n';
	// clang-format on
}

int linarr_DMax_pp::parse_params() noexcept
{
	if (m_argc == 0) {
		print_usage();
		return 1;
	}

	for (uint64_t i = 0; i < m_argc; ++i) {
		const std::string param(m_argv[i]);

		if (param == "--help" or param == "-h") {
			print_usage();
			return 1;
		}
		else if (param == "-mode") {
			m_mode = std::string(m_argv[i + 1]);
			++i;
		}
		else if (param == "-n") {
			m_n = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_has_n = true;
			++i;
		}
		else if (param == "-T") {
			m_T = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_has_T = true;
			++i;
		}
		else if (param == "-hv") {
			const uint64_t k = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_hv = lal::head_vector(k);
			uint64_t j;
			for (j = i + 2; j < i + 2 + k; ++j) {
				m_hv[j - (i + 2)] = static_cast<uint64_t>(atoi(m_argv[j]));
			}
			m_has_hv = true;
			i = j - 1;
		}
		else if (param == "-R") {
			m_R = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_has_R = true;
			++i;
		}
		else if (param == "-algorithm") {
			m_gen_algo = std::string(m_argv[i + 1]);
			++i;
		}
		else {
			std::cerr << "Error: unrecognised option\n";
			std::cerr << "    " << param << '\n';
			return 2;
		}
	}
	return 0;
}

int linarr_DMax_pp::check_errors() const noexcept
{
	if (m_mode != "automatic" and m_mode != "manual") {
		std::cout << "Error: wrong mode '" << m_mode << "'.\n";
		return 1;
	}
	if (not m_has_R) {
		std::cout << "Error: missing parameter '-R'.\n";
		return 1;
	}
	if (m_mode == "automatic") {
		if (not m_has_n) {
			std::cout << "Error: missing parameter '-n'.\n";
			return 1;
		}
		if (not m_has_T) {
			std::cout << "Error: missing parameter '-T'.\n";
			return 1;
		}
	}
	else if (m_mode == "manual") {
		if (not m_has_hv) {
			std::cout << "Error: missing parameter '-hv'.\n";
			return 1;
		}
	}
	if (m_gen_algo == "none") {
		std::cout << "Error: missing parameter '-algorithm'.\n";
		return 1;
	}

	return 0;
}

} // namespace linarr_DMax
} // namespace profiling
