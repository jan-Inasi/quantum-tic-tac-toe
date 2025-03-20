#include "find_connection.hpp"

template<typename Graph>
std::vector<typename Graph::edge_descriptor> find_connection(const Graph& graph,
    const size_t a, const size_t b) {
    auto indexmap = boost::get(boost::vertex_index, graph);
    auto colormap = boost::make_vector_property_map<boost::default_color_type>(indexmap);

    std::vector<typename Graph::edge_descriptor> edges;
    bool found_connection = false;
    FindConnectionVisitor<Graph> vis(edges, found_connection, a, b);
    boost::depth_first_search(graph, vis, colormap, a);

    if(!found_connection) {
        edges.clear();
    }
    return edges;
}


template<typename Graph>
FindConnectionVisitor<Graph>::FindConnectionVisitor(Edges& edg, bool& found_connection, const size_t sta, const size_t goa) :
    connection_is_found(found_connection), start(sta), goal(goa), edges(edg) { }

template<typename Graph>
void FindConnectionVisitor<Graph>::tree_edge(const EdgeDesc& e, const Graph& g) {
    if(connection_is_found)
        return;

    auto source = boost::source(e, g);
    auto target = boost::target(e, g);

    while(this->edges.size() > 0 && this->backTarget(g) != source) {
        this->edges.pop_back();
    }

    if(this->source(g) != source) {
        return;
    }

    if(target == this->goal) {
        this->connection_is_found = true;
        this->edges.push_back(e);
        return;
    }

    this->edges.push_back(e);
}

template<typename Graph>
size_t FindConnectionVisitor<Graph>::source(const Graph& g) const {
    if(this->edges.size() == 0)
        return this->start;
    return this->backTarget(g);
}

template<typename Graph>
size_t FindConnectionVisitor<Graph>::backSource(const Graph& g) const {
    return boost::source(this->edges.back(), g);
}

template<typename Graph>
size_t FindConnectionVisitor<Graph>::backTarget(const Graph& g) const {
    return boost::target(this->edges.back(), g);
}

template std::vector<GraphTTT::edge_descriptor> find_connection(const GraphTTT& graph, const size_t a, const size_t b);