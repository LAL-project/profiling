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
namespace properties_variance_C {

class properties_variance_C_pp {
public:

	properties_variance_C_pp(uint64_t argc, char *argv[]) noexcept;
	~properties_variance_C_pp() noexcept = default;

	[[nodiscard]] uint64_t get_R() const noexcept
	{
		return m_R;
	}
	[[nodiscard]] uint64_t get_nK() const noexcept
	{
		return m_n_K;
	}
	[[nodiscard]] uint64_t get_nKK_1() const noexcept
	{
		return m_n_KK_1;
	}
	[[nodiscard]] uint64_t get_nKK_2() const noexcept
	{
		return m_n_KK_2;
	}
	[[nodiscard]] bool get_reuse() const noexcept
	{
		return m_reuse;
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

	// reuse memory
	bool m_reuse = false;

	// Replicas
	uint64_t m_R = 1000;

	// size of the complete graph
	uint64_t m_n_K = 0;
	bool m_has_n_K = false;

	// size of the complete bipartite graph
	uint64_t m_n_KK_1 = 0;
	uint64_t m_n_KK_2 = 0;
	bool m_has_n_KK = false;

	uint64_t m_argc;
	char **m_argv;
};

} // namespace properties_variance_C
} // namespace profiling
