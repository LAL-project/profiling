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

// C++ includes
#include <iostream>
#include <random>

// lal includes
#include <lal/generate/tree_generator_type.hpp>
#include <lal/graphs/undirected_graph.hpp>
#include <lal/graphs/directed_graph.hpp>
#include <lal/graphs/free_tree.hpp>
#include <lal/graphs/rooted_tree.hpp>
#include <lal/detail/graphs/conversions.hpp>
#include <lal/iterators/E_iterator.hpp>

// common includes
#include "graphs_pp.hpp"
#include "time.hpp"

namespace profiling {
namespace graphs {

template <class graph_t>
static constexpr bool is_undirected_graph
	= std::is_same_v<lal::graphs::undirected_graph, graph_t>;
template <class graph_t>
static constexpr bool is_directed_graph
	= std::is_same_v<lal::graphs::directed_graph, graph_t>;
template <class graph_t>
static constexpr bool is_free_tree
	= std::is_same_v<lal::graphs::free_tree, graph_t>;
template <class graph_t>
static constexpr bool is_rooted_tree
	= std::is_same_v<lal::graphs::rooted_tree, graph_t>;
template <class graph_t>
static constexpr bool is_tree
	= is_free_tree<graph_t> or is_rooted_tree<graph_t>;

template <class graph_t>
void do_operation(const graphs_pp& parser, graph_t& g) noexcept {
	const std::string& operation = parser.get_operation();

	if (operation == "add/remove-edges") {
		const double prob_choose = 0.5;
		std::mt19937 gen(1234);
		std::bernoulli_distribution d(prob_choose);

		std::cout << "Picking edge list...\n";
		lal::edge_list el;
		el.reserve(g.get_num_edges()*prob_choose);
		for (lal::iterators::E_iterator it(g); not it.end(); it.next()) {
			// with a random probability, pick the edge
			if (d(gen)) {
				el.push_back(it.get_edge());
			}
		}

		std::cout << "Operating " << el.size() << " edges...\n";
		const uint64_t R = parser.get_replicas();

		const auto begin = profiling::now();
		for (uint64_t r = 0; r < R; ++r) {
			g.remove_edges(el);
			g.add_edges(el);
		}
		const auto end = profiling::now();
		const double total = profiling::elapsed_time(begin, end);

		std::cout << "Total execution time: " << profiling::time_to_str(total) << '\n';
		std::cout << "    Average (per replica): " << profiling::time_to_str(total/R) << '\n';
	}
	else if (operation == "add/remove-edges-bulk") {
		const double prob_choose = 0.5;
		std::mt19937 gen(1234);
		std::bernoulli_distribution d(prob_choose);

		std::cout << "Picking edge list...\n";
		lal::edge_list el;
		el.reserve(g.get_num_edges()*prob_choose);
		for (lal::iterators::E_iterator it(g); not it.end(); it.next()) {
			// with a random probability, pick the edge
			if (d(gen)) {
				el.push_back(it.get_edge());
			}
		}

		std::cout << "Operating " << el.size() << " edges...\n";
		const uint64_t R = parser.get_replicas();

		const auto begin = profiling::now();
		for (uint64_t r = 0; r < R; ++r) {
			for (const auto& [u,v] : el) {
				g.remove_edge_bulk(u, v);
			}
			g.finish_bulk_remove(false, false);
			for (const auto& [u,v] : el) {
				g.add_edge_bulk(u, v);
			}
			g.finish_bulk_add(false, false);
		}
		const auto end = profiling::now();
		const double total = profiling::elapsed_time(begin, end);

		std::cout << "Total execution time: " << profiling::time_to_str(total) << '\n';
		std::cout << "    Average (per replica): " << profiling::time_to_str(total/R) << '\n';
	}
}

template <class graph_t>
void do_profiling(const graphs_pp& parser) noexcept {
	const std::string& where = parser.get_graph_from();
	graph_t g;
	if (where == "edge-list") {
		g = lal::detail::from_edge_list_to_graph<graph_t>(parser.get_edge_list(), false, false);
	}
	else if (where == "head-vector") {
		g = lal::detail::from_head_vector_to_graph<graph_t>(parser.get_head_vector(), false, false);
	}
	else if (where == "random-tree") {
		if constexpr (is_tree<graph_t>) {
			std::cout << "Choosing tree...\n";

			lal::generate::tree_generator_type_t
			<
				lal::generate::random_t,
				lal::generate::labelled_t,
				graph_t
			>
			gen(parser.get_n(), 1234);

			g = gen.get_tree();
		}
	}

	do_operation(parser, g);
}

} // -- namespace linarr_C

void graph_operations(uint64_t argc, char *argv[]) {
	graphs::graphs_pp parser(argc, argv);
	{
		if (parser.parse_params() > 0) { return; }
		if (parser.check_errors() > 0) { return; }
	}

	const std::string& graph_class = parser.get_graph_class();
	if (graph_class == "undirected_graph") {
		graphs::do_profiling<lal::graphs::undirected_graph>(parser);
	}
	else if (graph_class == "directed_graph") {
		graphs::do_profiling<lal::graphs::directed_graph>(parser);
	}
	else if (graph_class == "free_tree") {
		graphs::do_profiling<lal::graphs::free_tree>(parser);
	}
	else if (graph_class == "rooted_tree") {
		graphs::do_profiling<lal::graphs::rooted_tree>(parser);
	}
}

} // -- namespace profiling
