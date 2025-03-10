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

// C*+ includes
#include <iostream>

// lal includes
#include <lal/numeric/rational.hpp>
#include <lal/numeric/output.hpp>

// common includes
#include "time.hpp"

namespace profiling {

void numeric_rational(
	[[maybe_unused]] uint64_t argc, [[maybe_unused]] char *argv[]
) noexcept
{

	profiling::time_point begin, end;
	double total;

	// additions
	{
		std::cout << "------------------------\n";

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (uint64_t f = 1; f < 5000; ++f) {
				i = (i + f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Additions (rational + integral): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::integer f = 1; f < 5000; f += 1) {
				i = (i + f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Additions (rational + integer): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::rational f = 1; f < 5000; f += 1) {
				i = (i + f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Additions (rational + rational): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (uint64_t f = 1; f < 5000; ++f) {
				i += f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Additions (+= integral): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::integer f = 1; f < 5000; f += 1) {
				i += f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Additions (+= integer): " << profiling::time_to_str(total)
				  << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::rational f = 1; f < 5000; f += 1) {
				i += f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Additions (+= rational): "
				  << profiling::time_to_str(total) << '\n';
	}

	// substractions
	{
		std::cout << "------------------------\n";

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (uint64_t f = 1; f < 5000; ++f) {
				i = (i - f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Subtractions (rational - integral): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::integer f = 1; f < 5000; f += 1) {
				i = (i - f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Subtractions (rational - integer): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::rational f = 1; f < 5000; f += 1) {
				i = (i - f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Subtractions (rational - rational): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (uint64_t f = 1; f < 5000; ++f) {
				i -= f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Subtractions (-= integral): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::integer f = 1; f < 5000; f += 1) {
				i -= f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Subtractions (-= integer): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::rational f = 1; f < 5000; f += 1) {
				i -= f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Subtractions (-= rational): "
				  << profiling::time_to_str(total) << '\n';
	}

	// multiplications
	{
		std::cout << "------------------------\n";

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (uint64_t f = 1; f < 5000; ++f) {
				i = (i * f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Multiplications (rational * integral): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::integer f = 1; f < 5000; f += 1) {
				i = (i * f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Multiplications (rational * integer): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::rational f = 1; f < 5000; f += 1) {
				i = (i * f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Multiplications (rational * rational): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (uint64_t f = 1; f < 5000; ++f) {
				i *= f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Multiplications (*= integral): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::integer f = 1; f < 5000; f += 1) {
				i *= f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Multiplications (*= integer): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::rational f = 1; f < 5000; f += 1) {
				i *= f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Multiplications (*= rational): "
				  << profiling::time_to_str(total) << '\n';
	}

	// divisions
	{
		std::cout << "------------------------\n";

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = std::string(
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"999999999999999999999999999/9999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999998"
			);
			for (uint64_t f = 1; f < 50; ++f) {
				i = (i / f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Divisions (rational / integral): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::integer f = 1; f < 5000; f += 1) {
				i = (i / f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Divisions (rational / integer): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::rational f = 1; f < 5000; f += 1) {
				i = (i / f);
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Divisions (rational / rational): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = std::string(
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"999999999999999999999999999/9999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999999"
				"99999999999999999999999999999999999999999999999999999999999998"
			);
			for (uint64_t f = 1; f < 50; ++f) {
				i /= f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Divisions (/= integral): "
				  << profiling::time_to_str(total) << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::integer f = 1; f < 5000; f += 1) {
				i /= f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Divisions (/= integer): " << profiling::time_to_str(total)
				  << '\n';

		begin = profiling::now();
		for (int k = 0; k < 1000; ++k) {
			lal::numeric::rational i = 1;
			for (lal::numeric::rational f = 1; f < 5000; f += 1) {
				i /= f;
			}
		}
		end = profiling::now();
		total = profiling::elapsed_time(begin, end);
		std::cout << "Divisions (/= rational): "
				  << profiling::time_to_str(total) << '\n';
	}
}

} // namespace profiling
