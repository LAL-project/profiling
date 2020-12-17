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

#pragma once

// C++ includes
#include <string>
#include <set>

namespace profiling {
namespace dir_to_undir {

class dir_to_undir {
	public:
		dir_to_undir(int argc, char *argv[]);
		~dir_to_undir();
		
		const std::string& get_mode() const { return m_mode; }
		constexpr uint32_t get_n() const { return m_n; }
		constexpr uint32_t get_T() const { return m_T; }

		void print_usage() const;

		// returns 0 on success,
		// returns 1 on help,
		// returns 2 on error
		int parse_params();

		// returns 0 if there are no errors.
		// returns 1 if there are errors.
		int check_errors() const;

	private:
		// algorithm to execute
		std::string m_mode = "none";

		// number of vertices
		uint32_t m_n = 0;
		bool m_has_n = false;

		// number of replicas (times to repeat the same execution)
		uint32_t m_T = 0;
		bool m_has_T = false;
		
		const std::set<std::string> m_allowed_modes =
		std::set<std::string>({
			"dgraph_to_ugraph", "rtree_to_ftree"
		}
		);
		int m_argc;
		char **m_argv;
};

} // -- namespace dir_to_undir
} // -- namespace profiling
