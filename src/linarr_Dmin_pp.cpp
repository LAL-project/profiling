/***********************************************************************
 *
 * Research on Linear Arrangements project
 * Copyright (C) 2019,2020 Lluís Alemany Puig
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
#include <vector>
using namespace std;

namespace profiling {
namespace linarr_Dmin {

linarr_Dmin_pp::linarr_Dmin_pp(int argc, char *argv[]) : m_argc(argc), m_argv(argv)
{ }
linarr_Dmin_pp::~linarr_Dmin_pp() { }

void linarr_Dmin_pp::print_usage() const {
	cout << "Profiling -- Calculation of minimum D" << endl;
	cout << "=====================================" << endl;
	cout << endl;
	cout << "This program's options are the following:" << endl;
	cout << "    Those marked with [*] are mandatory for all execution modes." << endl;
	cout << "    Those marked with [i] are mandatory for execution mode i." << endl;
	cout << "    Those marked with [?] are optional." << endl;
	cout << endl;
	cout << "    [*]   -n n" << endl;
	cout << "          Indicate the number of vertices of the trees." << endl;
	cout << endl;
	cout << "    [*]   -T T" << endl;
	cout << "          Indicate the number of trees to generate." << endl;
	cout << endl;
	cout << "    [*]   -algorithm A" << endl;
	cout << "          Indicate the algorithm to profile:" << endl;
	cout << endl;
	for (const string& algo : m_allowed_algorithms) {
	cout << "          " << algo << endl;
	}
	cout << endl;
}

int linarr_Dmin_pp::parse_params() {
	if (m_argc == 2) {
		print_usage();
		return 1;
	}

	for (int i = 2; i < m_argc; ++i) {
		const string param(m_argv[i]);

		if (param == "--help" or param == "-h") {
			print_usage();
			return 1;
		}
		else if (param == "-n") {
			m_n = static_cast<uint32_t>(atoi(m_argv[i + 1]));
			m_has_n = true;
			++i;
		}
		else if (param == "-T") {
			m_T = static_cast<uint32_t>(atoi(m_argv[i + 1]));
			m_has_T = true;
			++i;
		}
		else if (param == "-algorithm") {
			m_gen_algo = string(m_argv[i + 1]);
			++i;
		}
		else {
			cerr << "Error: unrecognised option" << endl;
			cerr << "    " << string(m_argv[i]) << endl;
			return 2;
		}
	}
	return 0;
}

int linarr_Dmin_pp::check_errors() const {
	if (not m_has_n) {
		cout << "Error: missing parameter '-n'." << endl;
		return 1;
	}
	if (not m_has_T) {
		cout << "Error: missing parameter '-T'." << endl;
		return 1;
	}
	if (m_gen_algo == "none") {
		cout << "Error: missing parameter '-algorithm'." << endl;
		return 1;
	}

	return 0;
}

} // -- namespace linarr_Dmin
} // -- namespace profiling
