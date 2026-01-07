/***********************************************************************
 *
 * Profiling programs for LAL
 * Copyright (C) 2019 - 2026 Lluís Alemany Puig
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

// C++ includes
#include <iostream>
#include <cstdint>

namespace profiling {

void graph_operations(uint64_t argc, char *argv[]) noexcept;
void generate_trees(uint64_t argc, char *argv[]) noexcept;
void generate_arrangements(uint64_t argc, char *argv[]) noexcept;
void linarr_crossings(uint64_t argc, char *argv[]) noexcept;
void linarr_minimum_D(uint64_t argc, char *argv[]) noexcept;
void linarr_maximum_D(uint64_t argc, char *argv[]) noexcept;
void numeric_integer(uint64_t argc, char *argv[]) noexcept;
void numeric_rational(uint64_t argc, char *argv[]) noexcept;
void properties_variance_C_graph(uint64_t argc, char *argv[]) noexcept;
void properties_centroid_tree(uint64_t argc, char *argv[]) noexcept;
void properties_centre_tree(uint64_t argc, char *argv[]) noexcept;
void utilities_tree_isomorphism(uint64_t argc, char *argv[]) noexcept;
void detail_sorting_algorithms(uint64_t argc, char *argv[]) noexcept;
void conversion(uint64_t argc, char *argv[]) noexcept;

} // namespace profiling

void usage() noexcept
{
	// clang-format off
	std::cout << "Profiler of the Linear Arrangement Library\n";
	std::cout << "==========================================\n";
	std::cout << '\n';
	std::cout << "The first parameter indicates what is going to be profiled.\n";
	std::cout << "The following parameters depend on the option chosen in the first place.\n";
	std::cout << '\n';
	std::cout << "    graph_operations : Profile operations on graphs.\n";
	std::cout << '\n';
	std::cout << "    generate_trees : Profile the algorithms for the generation of trees.\n";
	std::cout << '\n';
	std::cout << "    generate_arrangements : Profile the algorithms for the generation\n";
	std::cout << "    of arrangements.\n";
	std::cout << '\n';
	std::cout << "    linarr_crossings : Profile the algorithms for the calculation\n";
	std::cout << "        of the number of crossings.\n";
	std::cout << '\n';
	std::cout << "    linarr_Dmin : Profile the algorithms for the calculation\n";
	std::cout << "        of the minimum sum of edge lengths.\n";
	std::cout << '\n';
	std::cout << "    linarr_DMax : Profile the algorithms for the calculation\n";
	std::cout << "        of the maximum sum of edge lengths.\n";
	std::cout << '\n';
	std::cout << "    numeric_integer : Profile the operations with integer numbers.\n";
	std::cout << '\n';
	std::cout << "    numeric_rational : Profile the operations with rational numbers.\n";
	std::cout << '\n';
	std::cout << "    properties_variance_C_graph : Profile the algorithm for the computation\n";
	std::cout << "        of the variance of C on graphs.\n";
	std::cout << '\n';
	std::cout << "    properties_centroid_tree : Profile the algorithm for the computation\n";
	std::cout << "        of the centroid of a tree.\n";
	std::cout << '\n';
	std::cout << "    properties_centre_tree : Profile the algorithm for the computation\n";
	std::cout << "        of the centre of a tree.\n";
	std::cout << '\n';
	std::cout << "    utilities_isomorphism : Profile the algorithms for the tree\n";
	std::cout << "        isomorphism test.\n";
	std::cout << '\n';
	std::cout << "    detail_sorting : Profile sorting algorithms.\n";
	std::cout << '\n';
	std::cout << "    conversion : Profile the conversion of a directed\n";
	std::cout << "        graph to an undirected graph.\n";
	std::cout << '\n';
	// clang-format on
}

int main(int argc, char *argv[]) noexcept
{
	if (argc == 1) {
		usage();
		return 0;
	}

	const uint64_t _argc = static_cast<uint64_t>(argc);

	const std::string first(argv[1]);
	if (first == "graph_operations") {
		profiling::graph_operations(_argc - 2, &argv[2]);
	}
	else if (first == "generate_trees") {
		profiling::generate_trees(_argc - 2, &argv[2]);
	}
	else if (first == "generate_arrangements") {
		profiling::generate_arrangements(_argc - 2, &argv[2]);
	}
	else if (first == "linarr_crossings") {
		profiling::linarr_crossings(_argc - 2, &argv[2]);
	}
	else if (first == "linarr_Dmin") {
		profiling::linarr_minimum_D(_argc - 2, &argv[2]);
	}
	else if (first == "linarr_DMax") {
		profiling::linarr_maximum_D(_argc - 2, &argv[2]);
	}
	else if (first == "numeric_integer") {
		profiling::numeric_integer(_argc - 2, &argv[2]);
	}
	else if (first == "numeric_rational") {
		profiling::numeric_rational(_argc - 2, &argv[2]);
	}
	else if (first == "properties_variance_C_graph") {
		profiling::properties_variance_C_graph(_argc - 2, &argv[2]);
	}
	else if (first == "properties_centroid_tree") {
		profiling::properties_centroid_tree(_argc - 2, &argv[2]);
	}
	else if (first == "properties_centre_tree") {
		profiling::properties_centre_tree(_argc - 2, &argv[2]);
	}
	else if (first == "utilities_isomorphism") {
		profiling::utilities_tree_isomorphism(_argc - 2, &argv[2]);
	}
	else if (first == "detail_sorting") {
		profiling::detail_sorting_algorithms(_argc - 2, &argv[2]);
	}
	else if (first == "conversion") {
		profiling::conversion(_argc - 2, &argv[2]);
	}
	else {
		std::cout << "Unknown/Unhandled: '" << first << "'\n";
	}
}
