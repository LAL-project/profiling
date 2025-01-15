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
 *    Lluís Alemany Puig (lluis.alemany.puig@upc.edu)
 *
 ***********************************************************************/

#pragma once

// C++ includes
#include <cstdint>
#include <string>
#include <set>

namespace profiling {
namespace generate {

class generate_arrangements_pp {
public:

	generate_arrangements_pp(uint64_t argc, char *argv[]) noexcept
		: m_argc(argc),
		  m_argv(argv)
	{ }
	~generate_arrangements_pp() noexcept { }

	[[nodiscard]] const std::string& get_gen_class() const noexcept
	{
		return m_gen_class;
	}
	[[nodiscard]] uint64_t get_n() const noexcept
	{
		return m_n;
	}
	[[nodiscard]] uint64_t get_T() const noexcept
	{
		return m_nT;
	}
	[[nodiscard]] uint64_t get_N() const noexcept
	{
		return m_N;
	}
	[[nodiscard]] uint64_t get_R() const noexcept
	{
		return m_R;
	}

	void print_usage() const noexcept;

	// returns 0 on success,
	// returns 1 on help,
	// returns 2 on error
	[[nodiscard]] int parse_params() noexcept;

	// returns 0 if there are no errors.
	// returns 1 if there are errors.
	[[nodiscard]] int check_errors() const noexcept;

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

	uint64_t m_argc;
	char **m_argv;

	// algorithm to execute
	std::string m_gen_class = "none";

	const std::set<std::string> m_allowed_gen_classes = std::set<std::string>({
		"all_arrangements",
		"all_projective_arrangements",
		"all_planar_arrangements",
		"rand_arrangements",
		"rand_projective_arrangements",
		"rand_planar_arrangements",
	});
};

} // namespace generate
} // namespace profiling
