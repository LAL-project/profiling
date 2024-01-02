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

// C++ includes
#include <iostream>

namespace profiling {

void generate_trees(int argc, char *argv[]);
void generate_arrangements(int argc, char *argv[]);
void linarr_crossings(int argc, char *argv[]);
void linarr_minimum_D(int argc, char *argv[]);
void linarr_maximum_D(int argc, char *argv[]);
void properties_centroid_tree(int argc, char *argv[]);
void properties_centre_tree(int argc, char *argv[]);
void utilities_tree_isomorphism(int argc, char *argv[]);
void conversion(int argc, char *argv[]);

} // -- namespace profiling

void usage() {
	std::cout << "Profiler of the Linear Arrangement Library" << '\n';
	std::cout << "==========================================" << '\n';
	std::cout << '\n';
	std::cout << "The first parameter indicates what is going to be profiled." << '\n';
	std::cout << "The following parameters depend on the option chosen in the first" << '\n';
	std::cout << "place." << '\n';
	std::cout << '\n';
	std::cout << "    generate_trees : Profile the algorithms for the generation of" << '\n';
	std::cout << "        trees." << '\n';
	std::cout << '\n';
	std::cout << "    generate_arrangements : Profile the algorithms for the generation of" << '\n';
	std::cout << "        arrangements." << '\n';
	std::cout << '\n';
	std::cout << "    linarr_crossings : Profile the algorithms for the calculation" << '\n';
	std::cout << "        of the number of crossings." << '\n';
	std::cout << '\n';
	std::cout << "    linarr_Dmin : Profile the algorithms for the calculation" << '\n';
	std::cout << "        of the minimum sum of edge lengths." << '\n';
	std::cout << '\n';
	std::cout << "    linarr_DMax : Profile the algorithms for the calculation" << '\n';
	std::cout << "        of the maximum sum of edge lengths." << '\n';
	std::cout << '\n';
	std::cout << "    properties_centroid_tree : Profile the algorithm for the computation" << '\n';
	std::cout << "        of the centroid of a tree." << '\n';
	std::cout << '\n';
	std::cout << "    properties_centre_tree : Profile the algorithm for the computation" << '\n';
	std::cout << "        of the centre of a tree." << '\n';
	std::cout << '\n';
	std::cout << "    utilities_isomorphism : Profile the algorithms for the tree" << '\n';
	std::cout << "        isomorphism test." << '\n';
	std::cout << '\n';
	std::cout << "    conversion : Profile the conversion of a directed" << '\n';
	std::cout << "        graph to an undirected graph." << '\n';
	std::cout << '\n';
}

int main(int argc, char *argv[]) {
	if (argc == 1) {
		usage();
		return 0;
	}

	const std::string first(argv[1]);
	if (first == "generate_trees") {
		profiling::generate_trees(argc, argv);
	}
	else if (first == "generate_arrangements") {
		profiling::generate_arrangements(argc, argv);
	}
	else if (first == "linarr_crossings") {
		profiling::linarr_crossings(argc, argv);
	}
	else if (first == "linarr_Dmin") {
		profiling::linarr_minimum_D(argc, argv);
	}
	else if (first == "linarr_DMax") {
		profiling::linarr_maximum_D(argc, argv);
	}
	else if (first == "properties_centroid_tree") {
		profiling::properties_centroid_tree(argc, argv);
	}
	else if (first == "properties_centre_tree") {
		profiling::properties_centre_tree(argc, argv);
	}
	else if (first == "utilities_isomorphism") {
		profiling::utilities_tree_isomorphism(argc, argv);
	}
	else if (first == "conversion") {
		profiling::conversion(argc, argv);
	}
	else {
		std::cout << "Unknown/Unhandled: '" << first << "'" << '\n';
	}
}
