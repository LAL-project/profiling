/***********************************************************************
 *
 * Profiling programs for LAL
 * Copyright (C) 2019 - 2025 Lluís Alemany Puig
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

#include "dir_to_undir_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>

namespace profiling {
namespace dir_to_undir {

#define out std::cout

void dir_to_undir::print_usage() const noexcept
{
	// clang-format off
	std::cout << "Profiling -- Conversion of directed to undirected \n";
	std::cout << "================================================= \n";
	std::cout << '\n';
	std::cout << "This program's options are the following:\n";
	std::cout << "    Those marked with [*] are mandatory for all execution modes.\n";
	std::cout << "    Those marked with [i] are mandatory for execution mode i.\n";
	std::cout << "    Those marked with [?] are optional.\n";
	std::cout << '\n';
	std::cout << "    [*]   -n n\n";
	std::cout << "          Indicate the number of vertices of the trees.\n";
	std::cout << '\n';
	std::cout << "    [*]   -T T\n";
	std::cout << "          Indicate the number of trees to generate.\n";
	std::cout << '\n';
	std::cout << "    [?]   -C C\n";
	std::cout << "          Indicate the number of calls to the conversion method.\n";
	std::cout << "          Default: 1\n";
	std::cout << '\n';
	std::cout << "    [*]   -mode M\n";
	std::cout << "          Indicate the mode of execution.\n";
	std::cout << '\n';
	for (const std::string& algo : m_allowed_modes) {
	std::cout << "          " << algo << '\n';
	}
	std::cout << '\n';
	// clang-format on
}

int dir_to_undir::parse_params() noexcept
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
		else if (param == "-C") {
			m_C = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			++i;
		}
		else if (param == "-mode") {
			m_mode = std::string(m_argv[i + 1]);
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

int dir_to_undir::check_errors() const noexcept
{
	if (not m_has_n) {
		std::cout << "Error: missing parameter '-n'.\n";
		return 1;
	}
	if (not m_has_T) {
		std::cout << "Error: missing parameter '-R'.\n";
		return 1;
	}
	if (m_mode == "none") {
		std::cout << "Error: missing parameter '-mode'.\n";
		return 1;
	}

	return 0;
}

} // namespace dir_to_undir
} // namespace profiling
