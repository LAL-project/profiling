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

#include "properties_centroid_centre_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>

namespace profiling {
namespace properties_centroid_centre {

properties_centroid_centre_pp::properties_centroid_centre_pp(
	uint64_t argc, char *argv[]
) noexcept
	: m_argc(argc), m_argv(argv)
{ }

void properties_centroid_centre_pp::print_usage() const noexcept {
	std::cout << "Profiling -- Calculation of the centroid of a tree" << '\n';
	std::cout << "==================================================" << '\n';
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
	std::cout << '\n';
}

int properties_centroid_centre_pp::parse_params() noexcept {
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
		else {
			std::cerr << "Error: unrecognised option" << '\n';
			std::cerr << "    " << std::string(m_argv[i]) << '\n';
			return 2;
		}
	}
	return 0;
}

int properties_centroid_centre_pp::check_errors() const noexcept {
	if (not m_has_n) {
		std::cout << "Error: missing parameter '-n'." << '\n';
		return 1;
	}
	if (not m_has_T) {
		std::cout << "Error: missing parameter '-R'." << '\n';
		return 1;
	}
	return 0;
}

} // -- namespace properties_centroid
} // -- namespace profiling
