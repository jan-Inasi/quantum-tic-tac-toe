#ifndef COLLAPSE_CYCLE_HPP
#define COLLAPSE_CYCLE_HPP

#include "graph_ttt.hpp"
#include <boost/graph/breadth_first_search.hpp>


/**
 * @brief visitor for finding the values of verteces after cycle colapse
 * 
 */
class ColapseVisitor : public boost::default_bfs_visitor {
public:
    typedef std::vector<std::pair<int, VertexTTT>> ColapseList;

    /**
     * @brief Construct a new Colapse Visitor object
     * 
     * @param lst cycle definition
     */
    ColapseVisitor(ColapseList& lst) :
        colapse_list(lst) { }

    template<typename Edge, typename Graph>
    void tree_edge(Edge e, const Graph& g) {
        boost::source(e, g);
        auto t = boost::target(e, g);
        this->colapse_list.push_back({t, g[e]});
    }

private:
    ColapseList& colapse_list;
};

#endif