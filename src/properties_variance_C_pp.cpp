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

#include "properties_variance_C_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>

namespace profiling {
namespace properties_variance_C {

properties_variance_C_pp::properties_variance_C_pp(uint64_t argc, char *argv[])
	noexcept
	: m_argc(argc),
	  m_argv(argv)
{ }

void properties_variance_C_pp::print_usage() const noexcept
{
	std::cout << "Profiling -- Calculation of the variance of C of a tree/graph"
			  << '\n';
	std::cout << "============================================================="
			  << '\n';
	std::cout << '\n';
	std::cout << "This program's options are the following:" << '\n';
	std::cout
		<< "    Those marked with [*] are mandatory for all execution modes."
		<< '\n';
	std::cout << "    Those marked with [i] are mandatory for execution mode i."
			  << '\n';
	std::cout << "    Those marked with [?] are optional." << '\n';
	std::cout << '\n';
	std::cout << "    [*]   -nK n" << '\n';
	std::cout
		<< "          Indicate the number of vertices of the complete graph.\n";
	std::cout << '\n';
	std::cout << "    [*]   -nKK n1 n2" << '\n';
	std::cout
		<< "          Indicate the number of vertices of the complete bipartite graph.\n";
	std::cout << '\n';
	std::cout << "    [?]   -R number of replicas" << '\n';
	std::cout << '\n';
	std::cout << "    [?]   -reuse Reuse memory? true/false" << '\n';
	std::cout << '\n';
}

int properties_variance_C_pp::parse_params() noexcept
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
		else if (param == "-R") {
			m_R = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			++i;
		}
		else if (param == "-reuse") {
			const std::string next_param(m_argv[i + 1]);
			if (next_param == "true") {
				m_reuse = true;
			}
			else if (next_param == "false") {
				m_reuse = false;
			}
			++i;
		}
		else if (param == "-nK") {
			m_n_K = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_has_n_K = true;
			++i;
		}
		else if (param == "-nKK") {
			m_n_KK_1 = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_n_KK_2 = static_cast<uint64_t>(atoi(m_argv[i + 2]));
			m_has_n_KK = true;
			i += 2;
		}
		else {
			std::cerr << "Error: unrecognised option" << '\n';
			std::cerr << "    " << std::string(m_argv[i]) << '\n';
			return 2;
		}
	}
	return 0;
}

int properties_variance_C_pp::check_errors() const noexcept
{
	if (not m_has_n_K and not m_has_n_KK) {
		std::cout << "Error: missing parameter.\n";
		std::cout << "    Use either -nK or -nKK.\n";
		return 1;
	}
	if (m_has_n_K and m_has_n_KK) {
		std::cout << "Error: too many parameters.\n";
		std::cout << "    Use only one of -nK or -nKK.\n";
		return 1;
	}
	return 0;
}

} // namespace properties_variance_C
} // namespace profiling
