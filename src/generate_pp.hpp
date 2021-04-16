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

#pragma once

// C++ includes
#include <string>
#include <set>

namespace profiling {
namespace generate {

class generate_pp {
public:
	generate_pp(int argc, char *argv[]);
	~generate_pp();

	const std::string& get_gen_class() const { return m_gen_class; }
	uint32_t get_n() const { return m_n; }
	uint32_t get_N() const { return m_N; }
	uint32_t get_R() const { return m_R; }

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
	std::string m_gen_class = "none";

	// number of vertices
	uint32_t m_n = 0;
	bool m_has_n = false;

	// number of trees to generate
	uint32_t m_N = 0;
	bool m_has_N = false;

	// number of replicas (times to repeat the same execution)
	uint32_t m_R = 0;
	bool m_has_R = false;

	const std::set<std::string> m_allowed_gen_classes =
	std::set<std::string>({
		"all_lab_free", "all_lab_rooted", "all_ulab_free", "all_ulab_rooted",
		"rand_lab_free", "rand_lab_rooted", "rand_ulab_free", "rand_ulab_rooted"
	}
	);
	int m_argc;
	char **m_argv;
};

} // -- namespace generate
} // -- namespace profiling
