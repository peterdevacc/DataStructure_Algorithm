//
// Created by Peter on 2022/4/15.
//

#include "ex_adjacency_matrix_generic_directed_graph.h"

using namespace Ex::AdjacencyMatrix;

void ex_adjacency_matrix_generic_directed_graph_unweighted();

void ex_adjacency_matrix_generic_directed_graph_weighted();

void Ex::AdjacencyMatrix::ex_adjacency_matrix_generic_directed_graph_test() {
    ex_adjacency_matrix_generic_directed_graph_unweighted();
    ex_adjacency_matrix_generic_directed_graph_weighted();
}

void ex_adjacency_matrix_generic_directed_graph_unweighted() {
    GenericDirectedGraph<std::string> graph{8};
    assert(graph.get_vertexMaxNum() == 8);

    graph.insert_vertex(1, "A");
    graph.insert_vertex(1, "A");
    graph.insert_vertex(3, "C");
    graph.insert_vertex(2, "B");
    graph.insert_vertex(5, "E");
    graph.insert_vertex(6, "F");
    graph.insert_vertex(7, "G");

    assert(graph.is_vertex_exist(1));
    assert(graph.is_vertex_exist(2));
    assert(graph.is_vertex_exist(3));
    assert(graph.is_vertex_exist(5));
    assert(graph.is_vertex_exist(6));
    assert(graph.is_vertex_exist(7));
    assert(graph.get_vertexNum() == 6);

    graph.insert_edge(1, 6);
    graph.insert_edge(1, 6);
    graph.insert_edge(1, 5);
    graph.insert_edge(3, 6);
    graph.insert_edge(6, 5);
    graph.insert_edge(2, 7);
    graph.insert_edge(7, 7);

    assert(graph.is_edge_exist(1, 6));
    assert(!graph.is_edge_exist(6, 1));
    assert(graph.is_edge_exist(1, 5));
    assert(!graph.is_edge_exist(5, 1));
    assert(graph.is_edge_exist(3, 6));
    assert(!graph.is_edge_exist(6, 3));
    assert(graph.is_edge_exist(6, 5));
    assert(!graph.is_edge_exist(5, 6));
    assert(graph.is_edge_exist(2, 7));
    assert(!graph.is_edge_exist(7, 2));
    assert(graph.is_edge_exist(7, 7));
    assert(graph.get_edgeNum() == 6);

    auto neighbors = graph.vertex_neighbors(1);
    assert(neighbors.size() == 2);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 5, "E");
    adjacencyMatrixCheckVertex<std::string>(neighbors[1], 6, "F");
    neighbors = graph.vertex_neighbors(2);
    assert(neighbors.size() == 1);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 7, "G");
    neighbors = graph.vertex_neighbors(3);
    assert(neighbors.size() == 1);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 6, "F");
    neighbors = graph.vertex_neighbors(5);
    assert(neighbors.empty());
    neighbors = graph.vertex_neighbors(6);
    assert(neighbors.size() == 1);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 5, "E");
    neighbors = graph.vertex_neighbors(7);
    assert(neighbors.size() == 1);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 7, "G");

    graph.remove_vertex(1);
    assert(!graph.is_vertex_exist(1));
    assert(!graph.is_edge_exist(1, 5));
    assert(!graph.is_edge_exist(1, 6));
    assert(graph.get_vertexNum() == 5);
    assert(graph.get_edgeNum() == 4);

    graph.remove_edge(3, 6);
    assert(!graph.is_edge_exist(3, 6));
    assert(graph.get_edgeNum() == 3);
}

void ex_adjacency_matrix_generic_directed_graph_weighted() {
    GenericDirectedGraph<std::string> graph{8};
    graph.insert_vertex(1, "A");
    graph.insert_vertex(1, "A");
    graph.insert_vertex(3, "C");
    graph.insert_vertex(2, "B");
    graph.insert_vertex(5, "E");
    graph.insert_vertex(6, "F");
    graph.insert_vertex(7, "G");

    graph.insert_edge(1, 6, 4);
    graph.insert_edge(1, 6, 4);
    graph.insert_edge(1, 5, 2);
    graph.insert_edge(3, 6, 1);
    graph.insert_edge(6, 5, 2);
    graph.insert_edge(2, 7, 5);
    graph.insert_edge(7, 7, 1);

    auto neighbors = graph.vertex_neighbors(1);
    assert(neighbors.size() == 2);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 5, "E", 2);
    adjacencyMatrixCheckVertex<std::string>(neighbors[1], 6, "F", 4);
    neighbors = graph.vertex_neighbors(2);
    assert(neighbors.size() == 1);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 7, "G", 5);
    neighbors = graph.vertex_neighbors(3);
    assert(neighbors.size() == 1);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 6, "F", 1);
    neighbors = graph.vertex_neighbors(5);
    assert(neighbors.empty());
    neighbors = graph.vertex_neighbors(6);
    assert(neighbors.size() == 1);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 5, "E", 2);
    neighbors = graph.vertex_neighbors(7);
    assert(neighbors.size() == 1);
    adjacencyMatrixCheckVertex<std::string>(neighbors[0], 7, "G", 1);
}
