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

// C++ includes
#include <iostream>
#include <random>

// lal includes
#include <lal/detail/sorting/insertion_sort.hpp>

// common includes
#include "time.hpp"
#include "detail_sorting_pp.hpp"

namespace profiling {
namespace detail_sorting {

void insertion_sort_int(const uint64_t n, const uint64_t R) noexcept
{
	std::vector<uint64_t> v(n);

	std::mt19937 g(1234);
	std::iota(v.begin(), v.end(), 0);

	double total_time = 0;
	for (uint64_t r = 0; r < R; ++r) {
		std::shuffle(v.begin(), v.end(), g);
		const auto begin = now();
		lal::detail::sorting::insertion_sort(v.begin(), v.end());
		const auto end = now();
		total_time += elapsed_time(begin, end);
	}

	std::cout << "Total execution time:   " << time_to_str(total_time) << '\n';
	std::cout << "Total time per replica: "
			  << time_to_str(total_time / static_cast<double>(R)) << '\n';
}

void insertion_sort_string(const uint64_t n, const uint64_t R) noexcept
{
	static constexpr std::string_view abc = "abcdefghijklmnopqrstuvwxyz";
	std::vector<std::string> v(n);

	std::mt19937 g(1234);

	std::for_each(
		v.begin(),
		v.end(),
		[&](std::string& s)
		{
			s.resize(100);
			for (char& c : s) {
				const std::size_t idx = g() % abc.size();
				c = abc[idx];
			}
		}
	);

	double total_time = 0;
	for (uint64_t r = 0; r < R; ++r) {
		std::shuffle(v.begin(), v.end(), g);
		const auto begin = now();
		lal::detail::sorting::insertion_sort(v.begin(), v.end());
		const auto end = now();
		total_time += elapsed_time(begin, end);
	}

	std::cout << "Total execution time:   " << time_to_str(total_time) << '\n';
	std::cout << "Total time per replica: "
			  << time_to_str(total_time / static_cast<double>(R)) << '\n';
}

} // namespace detail_sorting

void detail_sorting_algorithms(uint64_t argc, char *argv[]) noexcept
{
	detail_sorting::detail_sorting_pp parser(argc, argv);
	{
		if (parser.parse_params() > 0) {
			return;
		}
		if (parser.check_errors() > 0) {
			return;
		}
	}

	if (parser.get_algo() == "insertion") {
		detail_sorting::insertion_sort_int(parser.get_n(), parser.get_R());
		detail_sorting::insertion_sort_string(parser.get_n(), parser.get_R());
	}
}

} // namespace profiling
