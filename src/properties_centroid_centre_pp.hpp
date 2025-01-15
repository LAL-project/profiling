/***********************************************************************
 *
 * Profiling programs for LAL
 * Copyright (C) 2019 - 2025 Lluís Alemany Puig
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

namespace profiling {
namespace properties_centroid_centre {

class properties_centroid_centre_pp {
public:

	properties_centroid_centre_pp(uint64_t argc, char *argv[]) noexcept;
	~properties_centroid_centre_pp() noexcept = default;

	[[nodiscard]] constexpr uint64_t get_n() const noexcept
	{
		return m_n;
	}
	[[nodiscard]] constexpr uint64_t get_T() const noexcept
	{
		return m_T;
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
	uint64_t m_T = 0;
	bool m_has_T = false;

	uint64_t m_argc;
	char **m_argv;
};

} // namespace properties_centroid_centre
} // namespace profiling
