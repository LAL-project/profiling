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
#include <set>

// lal includes
#include <lal/basic_types.hpp>

namespace profiling {
namespace linarr_DMax {

class linarr_DMax_pp {
public:
	linarr_DMax_pp(uint64_t argc, char *argv[]) noexcept : m_argc(argc), m_argv(argv) { }
	~linarr_DMax_pp() noexcept { }

	const std::string& get_algo() const noexcept { return m_gen_algo; }
	const std::string& get_mode() const noexcept { return m_mode; }
	const lal::head_vector& get_head_vector() const noexcept { return m_hv; }
	uint64_t get_n() const noexcept { return m_n; }
	uint64_t get_T() const noexcept { return m_T; }
	uint64_t get_R() const noexcept { return m_R; }

	void print_usage() const noexcept;

	// returns 0 on success,
	// returns 1 on help,
	// returns 2 on error
	int parse_params() noexcept;

	// returns 0 if there are no errors.
	// returns 1 if there are errors.
	int check_errors() const noexcept;

private:
	const std::set<std::string> m_allowed_modes =
	std::set<std::string>({
		"automatic", "manual"
	}
	);

	const std::set<std::string> m_allowed_algorithms =
	std::set<std::string>({
		"projective", "planar", "bipartite", "1_eq_thistle"
	}
	);

	// algorithm to execute
	std::string m_gen_algo = "none";
	// mode of the profiler
	std::string m_mode = "none";

	// number of vertices
	uint64_t m_n = 0;
	bool m_has_n = false;

	// number of trees to generate
	uint64_t m_T = 0;
	bool m_has_T = false;

	// number of replicas (times to repeat the same execution)
	uint64_t m_R = 0;
	bool m_has_R = false;

	// head vector of the tree
	lal::head_vector m_hv;
	bool m_has_hv = false;

	uint64_t m_argc;
	char **m_argv;
};

} // -- namespace linarr_DMax
} // -- namespace profiling
