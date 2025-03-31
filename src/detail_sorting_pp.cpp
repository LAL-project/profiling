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

#include "detail_sorting_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>

namespace profiling {
namespace detail_sorting {

detail_sorting_pp::detail_sorting_pp(uint64_t argc, char *argv[]) noexcept
	: m_argc(argc),
	  m_argv(argv)
{ }
detail_sorting_pp::~detail_sorting_pp() noexcept { }

void detail_sorting_pp::print_usage() const noexcept
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
	std::cout << "    [*]   -n n\n";
	std::cout << "          Indicate the number elements to sort.\n";
	std::cout << '\n';
	std::cout << "    [*]   -R r\n";
	std::cout << "          Indicate the number times to run the algorithm.\n";
	std::cout << '\n';
	std::cout << "    [*]   -algorithm A\n";
	std::cout << "          Indicate the algorithm to profile:\n";
	std::cout << "              insertion\n";
	std::cout << '\n';
	for (const std::string& algo : m_allowed_algorithms) {
	std::cout << "          " << algo << '\n';
	}
	std::cout << '\n';
	// clang-format on
}

int detail_sorting_pp::parse_params() noexcept
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
		else if (param == "-R") {
			m_R = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_has_R = true;
			++i;
		}
		else if (param == "-algorithm") {
			m_algo = std::string(m_argv[i + 1]);
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

int detail_sorting_pp::check_errors() const noexcept
{
	if (not m_has_n) {
		std::cout << "Error: missing parameter '-n'.\n";
		return 1;
	}
	if (not m_has_R) {
		std::cout << "Error: missing parameter '-R'.\n";
		return 1;
	}
	if (m_algo == "none") {
		std::cout << "Error: missing parameter '-algorithm'.\n";
		return 1;
	}

	return 0;
}

} // namespace detail_sorting
} // namespace profiling
