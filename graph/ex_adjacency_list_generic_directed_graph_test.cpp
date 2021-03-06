//
// Created by Peter on 2022/4/15.
//

#include "ex_adjacency_list_generic_directed_graph.h"

using namespace Ex::AdjacencyList;

void ex_adjacency_list_generic_directed_graph_unweighted();

void ex_adjacency_list_generic_directed_graph_weighted();

void Ex::AdjacencyList::ex_adjacency_list_generic_directed_graph_test() {
    ex_adjacency_list_generic_directed_graph_unweighted();
    ex_adjacency_list_generic_directed_graph_weighted();
}

void ex_adjacency_list_generic_directed_graph_unweighted() {
    GenericDirectedGraph<std::string> graph{};
    graph.insert_vertex(1, "A");
    graph.insert_vertex(3, "C");
    graph.insert_vertex(2, "B");
    graph.insert_vertex(5, "E");
    graph.insert_vertex(8, "H");
    graph.insert_vertex(22, "V");

    assert(graph.is_vertex_exist(1));
    assert(graph.is_vertex_exist(2));
    assert(graph.is_vertex_exist(3));
    assert(graph.is_vertex_exist(5));
    assert(graph.is_vertex_exist(8));
    assert(graph.is_vertex_exist(22));
    assert(graph.get_vertexNum() == 6);

    graph.insert_edge(1, 22);
    graph.insert_edge(1, 22);
    graph.insert_edge(3, 1);
    graph.insert_edge(5, 5);
    graph.insert_edge(2, 22);
    graph.insert_edge(1, 8);
    assert(graph.is_edge_exist(1, 22));
    assert(graph.is_edge_exist(3, 1));
    assert(!graph.is_edge_exist(1, 3));
    assert(graph.is_edge_exist(5, 5));
    assert(graph.is_edge_exist(2, 22));
    assert(!graph.is_edge_exist(22, 2));
    assert(graph.is_edge_exist(1, 8));
    assert(!graph.is_edge_exist(8, 1));
    assert(graph.get_edgeNum() == 5);

    auto neighbors = graph.vertex_neighbors(1);
    assert(neighbors.size() == 2);
    adjacencyListCheckVertex<std::string>(neighbors[0], 22, "V");
    adjacencyListCheckVertex<std::string>(neighbors[1], 8, "H");
    neighbors = graph.vertex_neighbors(2);
    assert(neighbors.size() == 1);
    adjacencyListCheckVertex<std::string>(neighbors[0], 22, "V");
    neighbors = graph.vertex_neighbors(3);
    assert(neighbors.size() == 1);
    adjacencyListCheckVertex<std::string>(neighbors[0], 1, "A");
    neighbors = graph.vertex_neighbors(5);
    assert(neighbors.size() == 1);
    adjacencyListCheckVertex<std::string>(neighbors[0], 5, "E");
    neighbors = graph.vertex_neighbors(8);
    assert(neighbors.empty());
    neighbors = graph.vertex_neighbors(22);
    assert(neighbors.empty());

    graph.remove_vertex(1);
    assert(graph.get_vertexNum() == 5);
    assert(graph.get_edgeNum() == 2);

    graph.remove_edge(2, 22);
    assert(graph.get_edgeNum() == 1);
    assert(!graph.is_edge_exist(2, 22));
}

void ex_adjacency_list_generic_directed_graph_weighted() {
    GenericDirectedGraph<std::string> graph{};
    graph.insert_vertex(1, "A");
    graph.insert_vertex(3, "C");
    graph.insert_vertex(2, "B");
    graph.insert_vertex(5, "E");
    graph.insert_vertex(8, "H");
    graph.insert_vertex(22, "V");

    graph.insert_edge(1, 22, 8);
    graph.insert_edge(1, 22, 8);
    graph.insert_edge(3, 1, 1);
    graph.insert_edge(5, 5, 1);
    graph.insert_edge(2, 22, 5);
    graph.insert_edge(1, 8, 3);

    auto neighbors = graph.vertex_neighbors(1);
    assert(neighbors.size() == 2);
    adjacencyListCheckVertex<std::string>(neighbors[0], 22, "V", 8);
    adjacencyListCheckVertex<std::string>(neighbors[1], 8, "H", 3);
    neighbors = graph.vertex_neighbors(2);
    assert(neighbors.size() == 1);
    adjacencyListCheckVertex<std::string>(neighbors[0], 22, "V", 5);
    neighbors = graph.vertex_neighbors(3);
    assert(neighbors.size() == 1);
    adjacencyListCheckVertex<std::string>(neighbors[0], 1, "A", 1);
    neighbors = graph.vertex_neighbors(5);
    assert(neighbors.size() == 1);
    adjacencyListCheckVertex<std::string>(neighbors[0], 5, "E", 1);
    neighbors = graph.vertex_neighbors(8);
    assert(neighbors.empty());
    neighbors = graph.vertex_neighbors(22);
    assert(neighbors.empty());
}
