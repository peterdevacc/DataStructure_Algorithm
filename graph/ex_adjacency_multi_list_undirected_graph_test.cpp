// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_adjacency_multi_list_undirected_graph.h"

using namespace Ex::AdjacencyMultiList;

void adjacency_multi_list_undirected_graph_unweighted();
void adjacency_multi_list_undirected_graph_weighted();

void Ex::AdjacencyMultiList::undirected_graph_test() {
    adjacency_multi_list_undirected_graph_unweighted();
    adjacency_multi_list_undirected_graph_weighted();
}

void adjacency_multi_list_undirected_graph_unweighted() {
    UnDirectedGraph graph{8};
    assert(graph.get_vertexMaxNum() == 8);

    graph.insert_edge(0, 1);
    graph.insert_edge(0, 3);
    graph.insert_edge(2, 1);
    graph.insert_edge(2, 3);
    graph.insert_edge(4, 1);
    graph.insert_edge(2, 4);
    graph.insert_edge(4, 1);
    graph.insert_edge(2, 3);
    assert(graph.get_edgeNum() == 6);

    auto n0 = graph.vertex_neighbors(0);
    auto n1 = graph.vertex_neighbors(1);
    auto n2 = graph.vertex_neighbors(2);
    auto n3 = graph.vertex_neighbors(3);
    auto n4 = graph.vertex_neighbors(4);

    assert(n0.size() == 2);
    assert(n0[0] == n1[0]);
    assert(n0[1] == n3[0]);
    undirected_check_edge_data(n0[0], 1);
    undirected_check_edge_data(n0[1], 3);
    undirected_check_edge_field(n0[0], n0[1], n2[0]);
    undirected_check_edge_field(n0[1], nullptr, n2[1]);

    assert(n1.size() == 3);
    assert(n1[0] == n0[0]);
    assert(n1[1] == n2[0]);
    assert(n1[2] == n4[0]);
    undirected_check_edge_field(n1[0], n0[1], n2[0]);
    undirected_check_edge_field(n1[1], n2[1], n4[0]);
    undirected_check_edge_field(n1[2], n4[1], nullptr);

    assert(n2.size() == 3);
    assert(n2[0] == n1[1]);
    assert(n2[1] == n3[1]);
    assert(n2[2] == n4[1]);
    undirected_check_edge_data(n2[0], 1);
    undirected_check_edge_data(n2[1], 3);
    undirected_check_edge_data(n2[2], 4);
    undirected_check_edge_field(n2[0], n2[1], n4[0]);
    undirected_check_edge_field(n2[1], n2[2], nullptr);
    undirected_check_edge_field(n2[2], nullptr, nullptr);

    assert(n3.size() == 2);
    assert(n3[0] == n0[1]);
    assert(n3[1] == n2[1]);
    undirected_check_edge_field(n3[0], nullptr, n2[1]);
    undirected_check_edge_field(n3[1], n4[1], nullptr);

    assert(n4.size() == 2);
    assert(n4[0] == n1[2]);
    assert(n4[1] == n2[2]);
    undirected_check_edge_data(n4[0], 1);
    undirected_check_edge_field(n4[0], n2[2], nullptr);
    undirected_check_edge_field(n4[1], nullptr, nullptr);

    graph.remove_edge(1, 0);
    assert(graph.get_edgeNum() == 5);

    n0 = graph.vertex_neighbors(0);
    n1 = graph.vertex_neighbors(1);
    n2 = graph.vertex_neighbors(2);

    assert(n0.size() == 1);
    undirected_check_edge_data(n0[0], 3);
    undirected_check_edge_field(n0[0], nullptr, n2[1]);

    assert(n1.size() == 2);
    assert(n1[0] == n2[0]);

    graph.remove_edge(2, 4);
    assert(graph.get_edgeNum() == 4);

    n2 = graph.vertex_neighbors(2);
    n4 = graph.vertex_neighbors(4);

    assert(n2.size() == 2);
    undirected_check_edge_field(n2[1], nullptr, nullptr);

    assert(n4.size() == 1);
    undirected_check_edge_field(n4[0], nullptr, nullptr);
}

void adjacency_multi_list_undirected_graph_weighted() {
    UnDirectedGraph graph{8};

    graph.insert_edge(0, 1, 1);
    graph.insert_edge(0, 3, 1);
    graph.insert_edge(2, 1, 2);
    graph.insert_edge(2, 3, 2);
    graph.insert_edge(4, 1, 5);
    graph.insert_edge(2, 4, 3);

    auto n0 = graph.vertex_neighbors(0);
    auto n1 = graph.vertex_neighbors(1);
    auto n2 = graph.vertex_neighbors(2);
    auto n3 = graph.vertex_neighbors(3);
    auto n4 = graph.vertex_neighbors(4);

    undirected_check_edge_data(n0[0], 1, 1);
    undirected_check_edge_data(n0[1], 3, 1);

    undirected_check_edge_data(n2[0], 1, 2);
    undirected_check_edge_data(n2[1], 3, 2);
    undirected_check_edge_data(n2[2], 4, 3);

    undirected_check_edge_data(n4[0], 1, 5);
}
