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

#pragma once

// C++ includes
#include <string>

// lal includes
#include <lal/basic_types.hpp>

namespace profiling {
namespace graphs {

class graphs_pp {
public:
	graphs_pp(uint64_t argc, char *argv[]) noexcept : m_argc(argc), m_argv(argv)
	{ }
	~graphs_pp() { }

	const lal::edge_list& get_edge_list() const noexcept { return m_list; }
	const lal::head_vector& get_head_vector() const noexcept { return m_hv; }
	const std::string& get_graph_class() const noexcept { return m_graph_class; }
	const std::string& get_operation() const noexcept { return m_operation; }
	const std::string& get_graph_from() const noexcept { return m_graph_from; }
	uint64_t get_n() const noexcept { return m_n; }
	uint64_t get_replicas() const noexcept { return m_R; }

	void print_usage() const noexcept;

	// returns 0 on success,
	// returns 1 on help,
	// returns 2 on error
	int parse_params() noexcept;

	// returns 0 if there are no errors.
	// returns 1 if there are errors.
	int check_errors() const noexcept;

private:
	std::string m_operation = "none";
	std::string m_graph_class = "none";
	std::string m_graph_from = "none";

	// number of vertices
	uint64_t m_n = 0;
	bool m_has_n = false;

	// number of replicas (times to repeat the same execution)
	uint64_t m_R = 0;
	bool m_has_R = false;

	// edge list of the graph
	lal::edge_list m_list;
	bool m_has_list = false;

	// head vector of the graph
	lal::head_vector m_hv;
	bool m_has_hv = false;

	uint64_t m_argc;
	char **m_argv;
};

} // -- namespace graphs
} // -- namespace profiling
