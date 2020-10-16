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
#include <chrono>
#include <string>

namespace profiling {

typedef std::chrono::high_resolution_clock::time_point time_point;

inline std::string __time_to_str(uint64_t t, const std::string& unit) {
	if (unit == "ms") {
		const uint64_t ms = t%1000;
		const std::string base = std::to_string(ms) + " ms";
		if (t < 1000) { return base; }
		return __time_to_str(t/1000, "s") + " " + base;
	}

	if (unit == "s") {
		const uint64_t s = t%60;
		const std::string base = std::to_string(s) + " s";
		if (t < 60) { return base; }
		return __time_to_str(t/60, "min") + " " + base;
	}

	if (unit == "min") {
		const uint64_t min = t%60;
		const std::string base = std::to_string(min) + " min";
		if (t < 60) { return base; }
		return __time_to_str(t/60, "h") + " " + base;
	}

	if (unit == "h") {
		const uint64_t h = t%24;
		const std::string base = std::to_string(h) + " h";
		if (t < 24) { return base; }
		return __time_to_str(t/24, "d") + " " + base;
	}

	return std::to_string(t) + " d";
}

inline std::string time_to_str(double ms) {
	if (ms < 1000.0) {
		return std::to_string(ms) + " ms";
	}
	return __time_to_str(static_cast<uint64_t>(ms), "ms");
}

// Returns the current time
inline time_point now() {
	return std::chrono::high_resolution_clock::now();
}

// Returns the elapsed time between 'begin' and 'end' in milliseconds
inline double elapsed_time(const time_point& begin, const time_point& end) {
	return std::chrono::duration<double, std::chrono::milliseconds::period>( end - begin ).count();
}

} // -- namespace res_linarr
