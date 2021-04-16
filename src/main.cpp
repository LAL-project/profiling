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

// C++ includes
#include <iostream>
using namespace std;

namespace profiling {

void generate_trees(int argc, char *argv[]);
void linarr_crossings(int argc, char *argv[]);
void linarr_minimum_D(int argc, char *argv[]);
void properties_centroid_tree(int argc, char *argv[]);
void utilities_tree_isomorphism(int argc, char *argv[]);
void conversion(int argc, char *argv[]);

} // -- namespace profiling

void usage() {
	cout << "Profiler of the Linear Arrangement Library" << endl;
	cout << "==========================================" << endl;
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
	cout << "    properties_centroid_tree : Profile the algorithm for the computation" << endl;
	cout << "        of the centroid of a tree." << endl;
	cout << endl;
	cout << "    utilities_isomorphism : Profile the algorithms for the tree" << endl;
	cout << "        isomorphism test." << endl;
	cout << endl;
	cout << "    conversion : Profile the conversion of a directed" << endl;
	cout << "        graph to an undirected graph." << endl;
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
	else if (first == "properties_centroid_tree") {
		profiling::properties_centroid_tree(argc, argv);
	}
	else if (first == "utilities_isomorphism") {
		profiling::utilities_tree_isomorphism(argc, argv);
	}
	else if (first == "conversion") {
		profiling::conversion(argc, argv);
	}
	else {
		cout << "Unknown/Unhandled: '" << first << "'" << endl;
	}
}
