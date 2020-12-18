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

#include "dir_to_undir_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

namespace profiling {
namespace dir_to_undir {

dir_to_undir::dir_to_undir(int argc, char *argv[])
	: m_argc(argc), m_argv(argv)
{ }
dir_to_undir::~dir_to_undir() { }

void dir_to_undir::print_usage() const {
	cout << "Profiling -- Conversion of directed to undirected" << endl;
	cout << "=================================================" << endl;
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
	cout << "    [?]   -C C" << endl;
	cout << "          Indicate the number of calls to the conversion method." << endl;
	cout << "          Default: 1" << endl;
	cout << endl;
	cout << "    [*]   -mode M" << endl;
	cout << "          Indicate the mode of execution." << endl;
	cout << endl;
	for (const string& algo : m_allowed_modes) {
	cout << "          " << algo << endl;
	}
	cout << endl;
}

int dir_to_undir::parse_params() {
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
		else if (param == "-C") {
			m_C = static_cast<uint32_t>(atoi(m_argv[i + 1]));
			++i;
		}
		else if (param == "-mode") {
			m_mode = string(m_argv[i + 1]);
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

int dir_to_undir::check_errors() const {
	if (not m_has_n) {
		cout << "Error: missing parameter '-n'." << endl;
		return 1;
	}
	if (not m_has_T) {
		cout << "Error: missing parameter '-R'." << endl;
		return 1;
	}
	if (m_mode == "none") {
		cout << "Error: missing parameter '-mode'." << endl;
		return 1;
	}

	return 0;
}

} // -- namespace dir_to_undir
} // -- namespace profiling
