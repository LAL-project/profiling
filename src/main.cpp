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

// C++ includes
#include <iostream>
using namespace std;

namespace profiling {

// profiling functions
void generate_trees(int argc, char *argv[]);
void linarr_crossings(int argc, char *argv[]);
void linarr_minimum_D(int argc, char *argv[]);

} // -- namespace profiling

void usage() {
	cout << "Profiler of the Linear Arrangement Library" << endl;
	cout << endl;
	cout << "The first parameter indicates what is going to be profiled." << endl;
	cout << "The following parameters depend on the option chosen in the first" << endl;
	cout << "place." << endl;
	cout << endl;
	cout << "    generate_trees : Profile the algorithms for the generation of" << endl;
	cout << "        trees." << endl;
	cout << endl;
	cout << "    linarr_crossings : Profile the algorithms for the calculation" << endl;
	cout << "        of the number of crossings." << endl;
	cout << endl;
	cout << "    linarr_Dmin : Profile the algorithms for the calculation" << endl;
	cout << "        of the minimum sum of edge lengths." << endl;
	cout << endl;
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		usage();
		return 0;
	}

	const string first(argv[1]);
	if (first == "generate_trees") {
		profiling::generate_trees(argc, argv);
	}
	else if (first == "linarr_crossings") {
		profiling::linarr_crossings(argc, argv);
	}
	else if (first == "linarr_Dmin") {
		profiling::linarr_minimum_D(argc, argv);
	}
	else {
		cout << "Unknown/Unhandled: '" << first << "'" << endl;
	}
}
