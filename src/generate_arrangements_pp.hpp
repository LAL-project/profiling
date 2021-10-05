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

class generate_arrangements_pp {
public:
	generate_arrangements_pp(int argc, char *argv[]) noexcept;
	~generate_arrangements_pp() noexcept { }

	const std::string& get_gen_class() const noexcept { return m_gen_class; }
	uint64_t get_n() const noexcept { return m_n; }
	uint64_t get_T() const noexcept { return m_nT; }
	uint64_t get_N() const noexcept { return m_N; }
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
	// number of vertices
	uint64_t m_n = 0;
	bool m_has_n = false;

	// number of trees to generate
	uint64_t m_nT = 0;
	bool m_has_nT = false;

	// number of arrangements to generate
	uint64_t m_N = 0;
	bool m_has_N = false;

	// number of replicas (times to repeat the same execution)
	uint64_t m_R = 0;
	bool m_has_R = false;

	int m_argc;
	char **m_argv;

	// algorithm to execute
	std::string m_gen_class = "none";

	const std::set<std::string> m_allowed_gen_classes =
	std::set<std::string>({
	"all_arrangements", "all_projective_arrangements", "all_planar_arrangements",
	"rand_arrangements", "rand_projective_arrangements", "rand_planar_arrangements",
	}
	);
};

} // -- namespace generate
} // -- namespace profiling
