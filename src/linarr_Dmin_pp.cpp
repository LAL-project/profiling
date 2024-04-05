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

#include "linarr_Dmin_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>

namespace profiling {
namespace linarr_Dmin {

linarr_Dmin_pp::linarr_Dmin_pp(int argc, char *argv[]) : m_argc(argc), m_argv(argv)
{ }
linarr_Dmin_pp::~linarr_Dmin_pp() { }

void linarr_Dmin_pp::print_usage() const {
	std::cout << "Profiling -- Calculation of minimum D" << '\n';
	std::cout << "=====================================" << '\n';
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
	std::cout << "    [*]   -algorithm A" << '\n';
	std::cout << "          Indicate the algorithm to profile:" << '\n';
	std::cout << '\n';
	for (const std::string& algo : m_allowed_algorithms) {
	std::cout << "          " << algo << '\n';
	}
	std::cout << '\n';
}

int linarr_Dmin_pp::parse_params() {
	if (m_argc == 0) {
		print_usage();
		return 1;
	}

	for (int i = 0; i < m_argc; ++i) {
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

int linarr_Dmin_pp::check_errors() const {
	if (not m_has_n) {
		std::cout << "Error: missing parameter '-n'." << '\n';
		return 1;
	}
	if (not m_has_T) {
		std::cout << "Error: missing parameter '-T'." << '\n';
		return 1;
	}
	if (m_gen_algo == "none") {
		std::cout << "Error: missing parameter '-algorithm'." << '\n';
		return 1;
	}

	return 0;
}

} // -- namespace linarr_Dmin
} // -- namespace profiling
