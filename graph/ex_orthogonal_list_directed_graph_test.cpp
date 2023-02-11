// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_orthogonal_list_directed_graph.h"

using namespace Ex::OrthogonalList;

void orthogonal_list_directed_graph_unweighted();
void orthogonal_list_directed_graph_weighted();

void Ex::OrthogonalList::directed_graph_test() {
    orthogonal_list_directed_graph_unweighted();
    orthogonal_list_directed_graph_weighted();
}

void orthogonal_list_directed_graph_unweighted() {
    DirectedGraph graph{8};
    assert(graph.get_vertexMaxNum() == 8);

    graph.insert_edge(0, 1);
    graph.insert_edge(0, 2);
    graph.insert_edge(2, 0);
    graph.insert_edge(2, 3);
    graph.insert_edge(3, 0);
    graph.insert_edge(3, 1);
    graph.insert_edge(3, 2);
    assert(graph.get_edgeNum() == 7);

    auto n0 = graph.vertex_neighbors(0);
    auto n1 = graph.vertex_neighbors(1);
    auto n2 = graph.vertex_neighbors(2);
    auto n3 = graph.vertex_neighbors(3);

    assert(n0.size() == 2);
    directed_check_edge_data(n0[0], 1);
    directed_check_edge_data(n0[1], 2);
    directed_check_edge_field(n0[0], n0[1], n3[1]);
    directed_check_edge_field(n0[1], nullptr, n3[2]);

    assert(n1.empty());

    assert(n2.size() == 2);
    directed_check_edge_data(n2[0], 0);
    directed_check_edge_data(n2[1], 3);
    directed_check_edge_field(n2[0], n2[1], n3[0]);
    directed_check_edge_field(n2[1], nullptr, nullptr);

    assert(n3.size() == 3);
    directed_check_edge_data(n3[0], 0);
    directed_check_edge_data(n3[1], 1);
    directed_check_edge_data(n3[2], 2);
    directed_check_edge_field(n3[0], n3[1], nullptr);
    directed_check_edge_field(n3[1], n3[2], nullptr);
    directed_check_edge_field(n3[2], nullptr, nullptr);

    auto v0 = graph.get_vertex(0);
    directed_check_vertex_field(v0, n0[0], n2[0]);
    auto v1 = graph.get_vertex(1);
    directed_check_vertex_field(v1, nullptr, n0[0]);
    auto v2 = graph.get_vertex(2);
    directed_check_vertex_field(v2, n2[0], n0[1]);
    auto v3 = graph.get_vertex(3);
    directed_check_vertex_field(v3, n3[0], n2[1]);

    graph.remove_edge(3, 0);
    assert(graph.get_edgeNum() == 6);
    v3 = graph.get_vertex(3);
    directed_check_vertex_field(v3, n3[1], n2[1]);
    n2 = graph.vertex_neighbors(2);
    directed_check_edge_field(n2[0], n2[1], nullptr);

    graph.remove_edge(0, 1);
    assert(graph.get_edgeNum() == 5);
    v0 = graph.get_vertex(0);
    v1 = graph.get_vertex(1);
    n0 = graph.vertex_neighbors(0);
    n2 = graph.vertex_neighbors(2);
    n3 = graph.vertex_neighbors(3);
    directed_check_edge_data(n0[0], 2);
    directed_check_vertex_field(v0, n0[0], n2[0]);
    directed_check_vertex_field(v1, nullptr, n3[0]);
    directed_check_edge_field(n0[0], nullptr, n3[1]);
}

void orthogonal_list_directed_graph_weighted() {
    DirectedGraph graph{8};
    graph.insert_edge(0, 1, 2);
    graph.insert_edge(0, 2, 3);
    graph.insert_edge(2, 0, 3);
    graph.insert_edge(2, 3, 1);
    graph.insert_edge(3, 0, 1);
    graph.insert_edge(3, 1, 2);
    graph.insert_edge(3, 2, 1);

    auto n0 = graph.vertex_neighbors(0);
    auto n1 = graph.vertex_neighbors(1);
    auto n2 = graph.vertex_neighbors(2);
    auto n3 = graph.vertex_neighbors(3);

    assert(n0.size() == 2);
    directed_check_edge_data(n0[0], 1, 2);
    directed_check_edge_data(n0[1], 2, 3);

    assert(n1.empty());

    assert(n2.size() == 2);
    directed_check_edge_data(n2[0], 0, 3);
    directed_check_edge_data(n2[1], 3, 1);

    assert(n3.size() == 3);
    directed_check_edge_data(n3[0], 0, 1);
    directed_check_edge_data(n3[1], 1, 2);
    directed_check_edge_data(n3[2], 2, 1);
}
