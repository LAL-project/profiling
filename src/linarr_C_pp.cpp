/***********************************************************************
 *
 * Profiling programs for LAL
 * Copyright (C) 2019 - 2023 Lluís Alemany Puig
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

#include "linarr_C_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>
#include <vector>

namespace profiling {
namespace linarr_C {

linarr_C_pp::linarr_C_pp(
	int argc, char *argv[]
) : m_argc(argc), m_argv(argv)
{ }
linarr_C_pp::~linarr_C_pp() { }

void linarr_C_pp::print_usage() const {
	std::cout << "Profiling -- Calculation of the number of crossings" << '\n';
	std::cout << "===================================================" << '\n';
	std::cout << '\n';
	std::cout << "This program's options are the following:" << '\n';
	std::cout << "    Those marked with [*] are mandatory for all execution modes." << '\n';
	std::cout << "    Those marked with [i] are mandatory for execution mode i." << '\n';
	std::cout << "    Those marked with [?] are optional." << '\n';
	std::cout << '\n';
	std::cout << "    [*]   -n n" << '\n';
	std::cout << "          Indicate the number of vertices of the trees." << '\n';
	std::cout << '\n';
	std::cout << "    [*]   -T T" << '\n';
	std::cout << "          Indicate the number of trees to generate." << '\n';
	std::cout << '\n';
	std::cout << "    [*]   -N N" << '\n';
	std::cout << "          Indicate the number of arrangements to generate (u.a.r.)." << '\n';
	std::cout << '\n';
	std::cout << "    [*]   -algorithm A" << '\n';
	std::cout << "          Indicate the algorithm to profile:" << '\n';
	std::cout << '\n';
	for (const std::string& algo : m_allowed_algorithms) {
	std::cout << "          " << algo << '\n';
	}
	std::cout << '\n';
}

int linarr_C_pp::parse_params() {
	if (m_argc == 2) {
		print_usage();
		return 1;
	}

	for (int i = 2; i < m_argc; ++i) {
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
		else if (param == "-N") {
			m_N = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_has_N = true;
			++i;
		}
		else if (param == "-T") {
			m_T = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_has_T = true;
			++i;
		}
		else if (param == "-algorithm") {
			m_gen_algo = std::string(m_argv[i + 1]);
			++i;
		}
		else {
			std::cerr << "Error: unrecognised option" << '\n';
			std::cerr << "    " << std::string(m_argv[i]) << '\n';
			return 2;
		}
	}
	return 0;
}

int linarr_C_pp::check_errors() const {
	if (not m_has_n) {
		std::cout << "Error: missing parameter '-n'." << '\n';
		return 1;
	}
	if (not m_has_N) {
		std::cout << "Error: missing parameter '-N'." << '\n';
		return 1;
	}
	if (not m_has_T) {
		std::cout << "Error: missing parameter '-R'." << '\n';
		return 1;
	}
	if (m_gen_algo == "none") {
		std::cout << "Error: missing parameter '-algorithm'." << '\n';
		return 1;
	}

	return 0;
}

} // -- namespace linarr_C
} // -- namespace profiling
