// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_adjacency_list_directed_graph.h"

using namespace Ex::AdjacencyList;

void adjacency_list_directed_graph_unweighted();
void adjacency_list_directed_graph_weighted();

void Ex::AdjacencyList::directed_graph_test() {
    adjacency_list_directed_graph_unweighted();
    adjacency_list_directed_graph_weighted();
}

void adjacency_list_directed_graph_unweighted() {
    DirectedGraph graph{8};
    assert(graph.get_vertexMaxNum() == 8);

    graph.insert_edge(1, 5);
    graph.insert_edge(3, 2);
    graph.insert_edge(1, 3);
    graph.insert_edge(2, 5);
    graph.insert_edge(0, 1);
    graph.insert_edge(6, 0);
    graph.insert_edge(6, 6);

    assert(graph.is_edge_exist(1, 5));
    assert(!graph.is_edge_exist(5, 1));
    assert(graph.is_edge_exist(3, 2));
    assert(!graph.is_edge_exist(2, 3));
    assert(graph.is_edge_exist(1, 3));
    assert(!graph.is_edge_exist(3, 1));
    assert(graph.is_edge_exist(2, 5));
    assert(!graph.is_edge_exist(5, 2));
    assert(graph.is_edge_exist(0, 1));
    assert(!graph.is_edge_exist(1, 0));
    assert(graph.is_edge_exist(6, 0));
    assert(graph.is_edge_exist(6, 6));
    assert(!graph.is_edge_exist(0, 6));
    assert(!graph.is_edge_exist(1, 7));
    assert(graph.get_edgeNum() == 7);

    auto neighbors = graph.vertex_neighbors(0);
    assert(neighbors.size() == 1);
    check_vertex(neighbors[0], 1);
    neighbors = graph.vertex_neighbors(1);
    assert(neighbors.size() == 2);
    check_vertex(neighbors[0], 5);
    check_vertex(neighbors[1], 3);
    neighbors = graph.vertex_neighbors(2);
    assert(neighbors.size() == 1);
    check_vertex(neighbors[0], 5);
    neighbors = graph.vertex_neighbors(3);
    assert(neighbors.size() == 1);
    check_vertex(neighbors[0], 2);
    neighbors = graph.vertex_neighbors(5);
    assert(neighbors.empty());
    neighbors = graph.vertex_neighbors(6);
    assert(neighbors.size() == 2);
    check_vertex(neighbors[0], 0);
    check_vertex(neighbors[1], 6);
    neighbors = graph.vertex_neighbors(7);
    assert(neighbors.empty());

    graph.remove_edge(1, 3);
    assert(!graph.is_edge_exist(1, 3));
    graph.remove_edge(6, 0);
    assert(!graph.is_edge_exist(6, 0));
    graph.remove_edge(1, 5);
    assert(!graph.is_edge_exist(1, 5));

    neighbors = graph.vertex_neighbors(1);
    assert(neighbors.empty());
    assert(graph.get_edgeNum() == 4);
}

void adjacency_list_directed_graph_weighted() {
    DirectedGraph graph{8};
    graph.insert_edge(1, 5, 2);
    graph.insert_edge(3, 2, 3);
    graph.insert_edge(1, 3, 1);
    graph.insert_edge(2, 5, 4);
    graph.insert_edge(0, 1, 1);
    graph.insert_edge(6, 0, 5);
    graph.insert_edge(6, 6, 1);

    auto neighbors = graph.vertex_neighbors(0);
    assert(neighbors.size() == 1);
    check_vertex(neighbors[0], 1, 1);
    neighbors = graph.vertex_neighbors(1);
    assert(neighbors.size() == 2);
    check_vertex(neighbors[0], 5, 2);
    check_vertex(neighbors[1], 3, 1);
    neighbors = graph.vertex_neighbors(2);
    assert(neighbors.size() == 1);
    check_vertex(neighbors[0], 5, 4);
    neighbors = graph.vertex_neighbors(3);
    assert(neighbors.size() == 1);
    check_vertex(neighbors[0], 2, 3);
    neighbors = graph.vertex_neighbors(5);
    assert(neighbors.empty());
    neighbors = graph.vertex_neighbors(6);
    assert(neighbors.size() == 2);
    check_vertex(neighbors[0], 0, 5);
    check_vertex(neighbors[1], 6, 1);
    neighbors = graph.vertex_neighbors(7);
    assert(neighbors.empty());
}
