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

void ex_adjacency_multi_list_undirected_graph_remove_vertex_test() {
    GenericUndirectedGraph<std::string> graph{8};
    graph.insert_vertex(2, "C");
    graph.insert_vertex(0, "A");
    graph.insert_vertex(1, "B");
    graph.insert_vertex(3, "D");
    graph.insert_vertex(4, "E");
    graph.insert_edge(0, 1);
    graph.insert_edge(0, 3);
    graph.insert_edge(2, 1);
    graph.insert_edge(2, 3);
    graph.insert_edge(4, 1);
    graph.insert_edge(2, 4);

    graph.remove_vertex(2);
    assert(!graph.is_vertex_exist(2));
    assert(graph.get_vertexNum() == 4);
    assert(graph.get_edgeNum() == 3);

    auto n0 = graph.vertex_neighbors(0);
    auto n1 = graph.vertex_neighbors(1);
    auto n2 = graph.vertex_neighbors(2);
    auto n3 = graph.vertex_neighbors(3);
    auto n4 = graph.vertex_neighbors(4);

    assert(n1[1] == n4[0]);

    assert(n1.size() == 2);
    undirected_check_edge_field<std::string>(n1[0], n0[1], n4[0]);
    undirected_check_edge_field<std::string>(n1[1], nullptr, nullptr);

    assert(n2.empty());

    assert(n3.size() == 1);
    undirected_check_edge_field<std::string>(n3[0], nullptr, nullptr);

    assert(n4.size() == 1);
    undirected_check_edge_field<std::string>(n4[0], nullptr, nullptr);

    graph.remove_vertex(1);
    assert(graph.get_vertexNum() == 3);
    assert(graph.get_edgeNum() == 1);

    n0 = graph.vertex_neighbors(0);
    n1 = graph.vertex_neighbors(1);
    n3 = graph.vertex_neighbors(3);
    n4 = graph.vertex_neighbors(4);

    assert(n0.size() == 1);
    assert(n1.empty());
    assert(n3.size() == 1);
    assert(n4.empty());

    assert(n0[0] == n3[0]);
    undirected_check_edge_data<std::string>(n0[0], "D", 3);

    graph.insert_vertex(25, "Z");
    assert(graph.is_vertex_exist(25));
    assert(graph.vertex_position(25) == 0);
    graph.insert_vertex(24, "Y");
    assert(graph.vertex_position(24) == 2);
}

void adjacency_multi_list_undirected_graph_unweighted() {
    GenericUndirectedGraph<std::string> graph{8};
    assert(graph.get_vertexMaxNum() == 8);

    graph.insert_vertex(2, "C");
    graph.insert_vertex(0, "A");
    graph.insert_vertex(1, "B");
    graph.insert_vertex(3, "D");
    graph.insert_vertex(4, "E");

    assert(graph.is_vertex_exist(0));
    assert(graph.is_vertex_exist(1));
    assert(graph.is_vertex_exist(2));
    assert(graph.is_vertex_exist(3));
    assert(graph.is_vertex_exist(4));
    assert(graph.vertex_position(0) == 1);
    assert(graph.vertex_position(1) == 2);
    assert(graph.vertex_position(2) == 0);
    assert(graph.vertex_position(3) == 3);
    assert(graph.vertex_position(4) == 4);
    assert(graph.get_vertexNum() == 5);

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
    undirected_check_edge_data<std::string>(n0[0], "B", 2);
    undirected_check_edge_data<std::string>(n0[1], "D", 3);
    undirected_check_edge_field(n0[0], n0[1], n2[0]);
    undirected_check_edge_field<std::string>(n0[1], nullptr, n2[1]);

    assert(n1.size() == 3);
    assert(n1[0] == n0[0]);
    assert(n1[1] == n2[0]);
    assert(n1[2] == n4[0]);
    undirected_check_edge_field(n1[0], n0[1], n2[0]);
    undirected_check_edge_field(n1[1], n2[1], n4[0]);
    undirected_check_edge_field<std::string>(n1[2], n4[1], nullptr);

    assert(n2.size() == 3);
    assert(n2[0] == n1[1]);
    assert(n2[1] == n3[1]);
    assert(n2[2] == n4[1]);
    undirected_check_edge_data<std::string>(n2[0], "B", 2);
    undirected_check_edge_data<std::string>(n2[1], "D", 3);
    undirected_check_edge_data<std::string>(n2[2], "E", 4);
    undirected_check_edge_field(n2[0], n2[1], n4[0]);
    undirected_check_edge_field<std::string>(n2[1], n2[2], nullptr);
    undirected_check_edge_field<std::string>(n2[2], nullptr, nullptr);

    assert(n3.size() == 2);
    assert(n3[0] == n0[1]);
    assert(n3[1] == n2[1]);
    undirected_check_edge_field<std::string>(n3[0], nullptr, n2[1]);
    undirected_check_edge_field<std::string>(n3[1], n4[1], nullptr);

    assert(n4.size() == 2);
    assert(n4[0] == n1[2]);
    assert(n4[1] == n2[2]);
    undirected_check_edge_data<std::string>(n4[0], "B", 2);
    undirected_check_edge_field<std::string>(n4[0], n2[2], nullptr);
    undirected_check_edge_field<std::string>(n4[1], nullptr, nullptr);

    ex_adjacency_multi_list_undirected_graph_remove_vertex_test();

    graph.remove_edge(1, 0);
    assert(graph.get_edgeNum() == 5);

    n0 = graph.vertex_neighbors(0);
    n1 = graph.vertex_neighbors(1);
    n2 = graph.vertex_neighbors(2);

    assert(n0.size() == 1);
    undirected_check_edge_data<std::string>(n0[0], "D", 3);
    undirected_check_edge_field<std::string>(n0[0], nullptr, n2[1]);

    assert(n1.size() == 2);
    assert(n1[0] == n2[0]);

    graph.remove_edge(2, 4);
    assert(graph.get_edgeNum() == 4);

    n2 = graph.vertex_neighbors(2);
    n4 = graph.vertex_neighbors(4);

    assert(n2.size() == 2);
    undirected_check_edge_field<std::string>(n2[1], nullptr, nullptr);

    assert(n4.size() == 1);
    undirected_check_edge_field<std::string>(n4[0], nullptr, nullptr);
}

void adjacency_multi_list_undirected_graph_weighted() {
    GenericUndirectedGraph<std::string> graph{8};
    graph.insert_vertex(2, "C");
    graph.insert_vertex(0, "A");
    graph.insert_vertex(1, "B");
    graph.insert_vertex(3, "D");
    graph.insert_vertex(4, "E");

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

    undirected_check_edge_data<std::string>(n0[0], "B", 2, 1);
    undirected_check_edge_data<std::string>(n0[1], "D", 3, 1);

    undirected_check_edge_data<std::string>(n2[0], "B", 2, 2);
    undirected_check_edge_data<std::string>(n2[1], "D", 3, 2);
    undirected_check_edge_data<std::string>(n2[2], "E", 4, 3);

    undirected_check_edge_data<std::string>(n4[0], "B", 2, 5);
}
