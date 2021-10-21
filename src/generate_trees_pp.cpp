/***********************************************************************
 *
 * Research on Linear Arrangements project
 * Copyright (C) 2019 - 2021 Lluís Alemany Puig
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

#include "generate_trees_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>
#include <vector>

namespace profiling {
namespace generate {

generate_trees_pp::generate_trees_pp(
	int argc, char *argv[]
) noexcept
	: m_argc(argc), m_argv(argv)
{ }

void generate_trees_pp::print_usage() const noexcept {
	std::cout << "Profiling -- Generation of trees" << '\n';
	std::cout << "==================" << '\n';
	std::cout << '\n';
	std::cout << "This program's options are the following:" << '\n';
	std::cout << "    Those marked with [*] are mandatory for all execution modes." << '\n';
	std::cout << "    Those marked with [i] are mandatory for execution mode i." << '\n';
	std::cout << "    Those marked with [?] are optional." << '\n';
	std::cout << '\n';
	std::cout << "    [*]   -n n" << '\n';
	std::cout << "          Indicate the number of vertices of the trees." << '\n';
	std::cout << '\n';
	std::cout << "    [*]   -N N" << '\n';
	std::cout << "          Indicate the number of trees to generate." << '\n';
	std::cout << '\n';
	std::cout << "    [*]   -R R" << '\n';
	std::cout << "          Indicate the number of replicas (times to replicate an" << '\n';
	std::cout << "          execution)." << '\n';
	std::cout << '\n';
	std::cout << "    [*]   -class C" << '\n';
	std::cout << "          Indicate the class of generation to profile. The available" << '\n';
	std::cout << "          classes are the following:" << '\n';
	std::cout << '\n';
	for (const std::string& algo : m_allowed_gen_classes) {
	std::cout << "          " << algo << '\n';
	}
	std::cout << '\n';
}

int generate_trees_pp::parse_params() noexcept {
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
		else if (param == "-R") {
			m_R = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_has_R = true;
			++i;
		}
		else if (param == "-class") {
			m_gen_class = std::string(m_argv[i + 1]);
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

int generate_trees_pp::check_errors() const noexcept {
	if (not m_has_n) {
		std::cout << "Error: missing parameter '-n'." << '\n';
		return 1;
	}
	if (not m_has_N) {
		std::cout << "Error: missing parameter '-N'." << '\n';
		return 1;
	}
	if (not m_has_R) {
		std::cout << "Error: missing parameter '-R'." << '\n';
		return 1;
	}
	if (m_gen_class == "none") {
		std::cout << "Error: missing parameter '-class'." << '\n';
		return 1;
	}

	return 0;
}

} // -- namespace generate
} // -- namespace profiling
