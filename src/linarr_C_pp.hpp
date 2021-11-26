/***********************************************************************
 *
 * Profiling programs for LAL
 * Copyright (C) 2019 - 2021 Lluís Alemany Puig
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
#include <set>

namespace profiling {
namespace linarr_C {

class linarr_C_pp {
public:
	linarr_C_pp(int argc, char *argv[]);
	~linarr_C_pp();

	const std::string& get_algo() const { return m_gen_algo; }
	constexpr uint64_t get_n() const { return m_n; }
	constexpr uint64_t get_N() const { return m_N; }
	constexpr uint64_t get_T() const { return m_T; }

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
	std::string m_gen_algo = "none";

	// number of vertices
	uint64_t m_n = 0;
	bool m_has_n = false;

	// number of trees to generate
	uint64_t m_N = 0;
	bool m_has_N = false;

	// number of replicas (times to repeat the same execution)
	uint64_t m_T = 0;
	bool m_has_T = false;

	const std::set<std::string> m_allowed_algorithms =
	std::set<std::string>({
		"brute_force", "brute_force_list",
		"dynamic_programming", "dynamic_programming_list",
		"ladder", "ladder_list",
		"stack_based", "stack_based_list"
	}
	);
	int m_argc;
	char **m_argv;
};

} // -- namespace linarr_C
} // -- namespace profiling
