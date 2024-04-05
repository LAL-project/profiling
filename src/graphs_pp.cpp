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

#include "graphs_pp.hpp"

// C++ includes
#include <cstdlib>
#include <iostream>

namespace profiling {
namespace graphs {

void graphs_pp::print_usage() const noexcept {
	std::cout << "Profiling -- Calculation of minimum D" << '\n';
	std::cout << "=====================================" << '\n';
	std::cout << '\n';
	std::cout << '\n';
	std::cout << "    -hv k p_1 ... p_k" << '\n';
	std::cout << "        Head vector of the graph." << '\n';
	std::cout << '\n';
	std::cout << "    -el k u_1 v_1 ... u_k v_k" << '\n';
	std::cout << "        Edge list of the graph." << '\n';
	std::cout << '\n';
	std::cout << "    -n n" << '\n';
	std::cout << "        Indicate the number of vertices of the trees." << '\n';
	std::cout << '\n';
	std::cout << "    -T T" << '\n';
	std::cout << "        Indicate the number of trees to generate." << '\n';
	std::cout << '\n';
	std::cout << "    -R r" << '\n';
	std::cout << "        Number of replicas to execute the algorithm." << '\n';
	std::cout << '\n';
	std::cout << "    -graph-from" << '\n';
	std::cout << "        Where to get the graph from." << '\n';
	std::cout << "            head-vector (requires '-hv')" << '\n';
	std::cout << "            edge-list (requires '-el')" << '\n';
	std::cout << "            random-tree (labelled trees only)" << '\n';
	std::cout << '\n';
	std::cout << "    -operation o" << '\n';
	std::cout << "        Operation to perform. Possible values:" << '\n';
	std::cout << "            - add/remove-edges : first removes and then adds\n";
	std::cout << "                a random set of edges.\n";
	std::cout << '\n';
	std::cout << "    -graph-class g" << '\n';
	std::cout << "        Graph class to use. Possible values:" << '\n';
	std::cout << "            undirected_graph" << '\n';
	std::cout << "            directed_graph" << '\n';
	std::cout << "            free_tree" << '\n';
	std::cout << "            rooted_tree" << '\n';
	std::cout << '\n';
}

int graphs_pp::parse_params() noexcept {
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
		else if (param == "-R") {
			m_R = static_cast<uint64_t>(atoi(m_argv[i + 1]));
			m_has_R = true;
			++i;
		}
		else if (param == "-hv") {
			const int k = static_cast<int>(atoi(m_argv[i + 1]));
			m_hv = lal::head_vector(k);
			int j;
			for (j = i + 2; j < i + 2 + k; ++j) {
				m_hv[j - (i + 2)] = static_cast<uint64_t>(atoi(m_argv[j]));
			}
			m_has_hv = true;
			i = j - 1;
		}
		else if (param == "-el") {
			const int k = static_cast<int>(atoi(m_argv[i + 1]));
			std::cout << "k= " << k << '\n';
			m_list = lal::edge_list(k);
			int j;
			for (j = 0; j < k; ++j) {
				m_list[j].first = static_cast<uint64_t>(atoi(m_argv[j + i + 2]));
				m_list[j].second = static_cast<uint64_t>(atoi(m_argv[j + i + 2 + 1]));
				std::cout << m_list[j].first << ' ' << m_list[j].second << '\n';
			}
			m_has_list = true;
			i = i + 1 + 2*k;
		}
		else if (param == "-operation") {
			m_operation = std::string(m_argv[i + 1]);
			++i;
		}
		else if (param == "-graph-class") {
			m_graph_class = std::string(m_argv[i + 1]);
			++i;
		}
		else if (param == "-graph-from") {
			m_graph_from = std::string(m_argv[i + 1]);
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

int graphs_pp::check_errors() const noexcept {
	if (not m_has_R) {
		std::cerr << "Error: missing parameter '-R'." << '\n';
		return 1;
	}

	if (m_operation == "none") {
		std::cerr << "Error: missing parameter '-operation'." << '\n';
		return 1;
	}

	if (m_graph_class == "none") {
		std::cerr << "Error: missing parameter '-graph-class'." << '\n';
		return 1;
	}
	if (m_graph_class != "undirected_graph" and
		m_graph_class != "directed_graph" and
		m_graph_class != "free_tree" and
		m_graph_class != "rooted_tree"
	)
	{
		std::cerr << "Error: wrong value for parameter '-graph-class'." << '\n';
		return 1;
	}

	if (m_graph_from == "none") {
		std::cerr << "Error: missing parameter '-graph-from'." << '\n';
		return 1;
	}
	if (m_graph_from != "head-vector" and
		m_graph_from != "edge-list" and
		m_graph_from != "random-tree"
	)
	{
		std::cerr << "Error: wrong value for parameter '-graph-from'." << '\n';
		return 1;
	}

	if (m_operation == "none") {
		std::cerr << "Error: missing parameter '-operation'." << '\n';
		return 1;
	}
	if (m_operation != "add/remove-edges") {
		std::cerr << "Error: wrong value for parameter '-graph-class'." << '\n';
		return 1;
	}

	return 0;
}

} // -- namespace graphs
} // -- namespace profiling
