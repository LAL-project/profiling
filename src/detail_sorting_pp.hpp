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

#pragma once

// C++ includes
#include <cstdint>
#include <string>
#include <set>

namespace profiling {
namespace detail_sorting {

class detail_sorting_pp {
public:

	detail_sorting_pp(uint64_t argc, char *argv[]) noexcept;
	~detail_sorting_pp() noexcept;

	[[nodiscard]] const std::string& get_algo() const noexcept
	{
		return m_algo;
	}
	[[nodiscard]] uint64_t get_n() const noexcept
	{
		return m_n;
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

	// algorithm to execute
	std::string m_algo = "none";

	// number of elements to sort
	uint64_t m_n = 0;
	bool m_has_n = false;

	// number of replicas
	uint64_t m_R = 0;
	bool m_has_R = false;

	const std::set<std::string> m_allowed_algorithms =
		std::set<std::string>({"insertion", "bit", "counting"});
	uint64_t m_argc;
	char **m_argv;
};

} // namespace detail_sorting
} // namespace profiling
