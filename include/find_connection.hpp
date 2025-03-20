#ifndef FIND_CONNECTION_HPP
#define FIND_CONNECTION_HPP

#include "graph_ttt.hpp"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <iostream>
#include <utility>
#include <vector>

/**
 * @brief this function finds a connection in graph between two given vertex (if exists)
 * 
 * @tparam Graph type of the graph 
 * @param graph a graph to perform search on
 * @param a begin vertex descriptor 
 * @param b end vertex descriptor
 * @return std::vector<typename Graph::edge_descriptor> found connection
 */
template<typename Graph>
std::vector<typename Graph::edge_descriptor> find_connection(const Graph& graph, const size_t a, const size_t b);

/**
 * @brief visitor for finding connection between two vertex
 * 
 * @tparam Graph type of the graph
 */
template<typename Graph>
class FindConnectionVisitor : public boost::default_dfs_visitor {
public:
    using EdgeDesc = typename Graph::edge_descriptor;
    using Edges = std::vector<EdgeDesc>;

    /**
     * @brief Construct a new Find Connection Visitor object
     * 
     * @param edges vector on which the connection will be stored
     * @param found_connection tells whether graph has connection
     * @param start begin vertex descriptor
     * @param goal end vertex descriptor
     */
    FindConnectionVisitor(Edges& edges, bool& found_connection, const size_t start, const size_t goal);

    void tree_edge(const EdgeDesc& e, const Graph& g);

    size_t source(const Graph& g) const;

    /**
     * @brief returns the source of the current edge
     * 
     * @param g searched graph
     * @return size_t vertex descriptor
     */
    size_t backSource(const Graph& g) const;

    /**
     * @brief returns the target of the current edge
     * 
     * @param g searched graph
     * @return size_t vertex descriptor
     */
    size_t backTarget(const Graph& g) const;

    bool& connection_is_found;
    size_t start, goal;
    Edges& edges;
};

#endif