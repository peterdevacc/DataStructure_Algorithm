// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_orthogonal_list_generic_directed_graph.h"

using namespace Ex::OrthogonalList;

void orthogonal_list_generic_directed_graph_unweighted();
void orthogonal_list_generic_directed_graph_weighted();

template<typename T>
void orthogonal_list_generic_directed_graph_neighbor_test(GenericDirectedGraph<T> &graph);

template<typename T>
void orthogonal_list_generic_directed_graph_remove_vertex_test(GenericDirectedGraph<T> &graph);

void orthogonal_list_generic_directed_graph_remove_edge_test_remove_edge_test();

void Ex::OrthogonalList::generic_directed_graph_test() {
    orthogonal_list_generic_directed_graph_unweighted();
    orthogonal_list_generic_directed_graph_weighted();
}

void orthogonal_list_generic_directed_graph_unweighted() {
    GenericDirectedGraph<std::string> graph{};
    graph.insert_vertex(0, "A");
    graph.insert_vertex(1, "B");
    graph.insert_vertex(2, "C");
    graph.insert_vertex(3, "D");
    assert(graph.get_vertexNum() == 4);

    graph.insert_edge(0, 1);
    graph.insert_edge(0, 2);
    graph.insert_edge(2, 0);
    graph.insert_edge(2, 3);
    graph.insert_edge(3, 0);
    graph.insert_edge(3, 1);
    graph.insert_edge(3, 2);
    assert(graph.get_edgeNum() == 7);

    orthogonal_list_generic_directed_graph_neighbor_test(graph);
    orthogonal_list_generic_directed_graph_remove_vertex_test(graph);
    orthogonal_list_generic_directed_graph_remove_edge_test_remove_edge_test();
}

void orthogonal_list_generic_directed_graph_weighted() {
    GenericDirectedGraph<std::string> graph{};
    graph.insert_vertex(0, "A");
    graph.insert_vertex(1, "B");
    graph.insert_vertex(2, "C");
    graph.insert_vertex(3, "D");

    graph.insert_edge(0, 1, 3);
    graph.insert_edge(0, 2, 2);
    graph.insert_edge(2, 0, 2);
    graph.insert_edge(2, 3, 1);
    graph.insert_edge(3, 0, 4);
    graph.insert_edge(3, 1, 5);
    graph.insert_edge(3, 2, 2);

    auto n0 = graph.vertex_neighbors(0);
    assert(n0.size() == 2);
    directed_check_edge_data<std::string>(n0[0], 1, "B", 3);
    directed_check_edge_data<std::string>(n0[1], 2, "C", 2);

    auto n1 = graph.vertex_neighbors(1);
    assert(n1.empty());

    auto n2 = graph.vertex_neighbors(2);
    assert(n2.size() == 2);
    directed_check_edge_data<std::string>(n2[0], 0, "A", 2);
    directed_check_edge_data<std::string>(n2[1], 3, "D", 1);

    auto n3 = graph.vertex_neighbors(3);
    assert(n3.size() == 3);
    directed_check_edge_data<std::string>(n3[0], 0, "A", 4);
    directed_check_edge_data<std::string>(n3[1], 1, "B", 5);
    directed_check_edge_data<std::string>(n3[2], 2, "C", 2);
}

template<typename T>
void orthogonal_list_generic_directed_graph_neighbor_test(GenericDirectedGraph<T> &graph) {
    auto n0 = graph.vertex_neighbors(0);
    assert(n0.size() == 2);
    directed_check_edge_data<std::string>(n0[0], 1, "B");
    directed_check_edge_data<std::string>(n0[1], 2, "C");

    auto n1 = graph.vertex_neighbors(1);
    assert(n1.empty());

    auto n2 = graph.vertex_neighbors(2);
    assert(n2.size() == 2);
    directed_check_edge_data<std::string>(n2[0], 0, "A");
    directed_check_edge_data<std::string>(n2[1], 3, "D");

    auto n3 = graph.vertex_neighbors(3);
    assert(n3.size() == 3);
    directed_check_edge_data<std::string>(n3[0], 0, "A");
    directed_check_edge_data<std::string>(n3[1], 1, "B");
    directed_check_edge_data<std::string>(n3[2], 2, "C");

    auto v0 = graph.get_vertex(0);
    directed_check_vertex_field(v0, n0[0], n2[0]);
    auto v1 = graph.get_vertex(1);
    directed_check_vertex_field<std::string>(v1, nullptr, n0[0]);
    auto v2 = graph.get_vertex(2);
    directed_check_vertex_field(v2, n2[0], n0[1]);
    auto v3 = graph.get_vertex(3);
    directed_check_vertex_field(v3, n3[0], n2[1]);

    assert(graph.get_vertex(0)->firstOut == n2[0]);
    directed_check_edge_field<std::string>(n0[0], nullptr, n0[1], nullptr, n3[1]);
    directed_check_edge_field<std::string>(n0[1], n0[0], nullptr, nullptr, n3[2]);

    assert(graph.get_vertex(1)->firstOut == n0[0]);

    assert(graph.get_vertex(2)->firstOut == n0[1]);
    directed_check_edge_field<std::string>(n2[0], nullptr, n2[1], nullptr, n3[0]);
    directed_check_edge_field<std::string>(n2[1], n2[0], nullptr, nullptr, nullptr);

    assert(graph.get_vertex(3)->firstOut == n2[1]);
    directed_check_edge_field<std::string>(n3[0], nullptr, n3[1], n2[0], nullptr);
    directed_check_edge_field<std::string>(n3[1], n3[0], n3[2], n0[0], nullptr);
    directed_check_edge_field<std::string>(n3[2], n3[1], nullptr, n0[1], nullptr);
}

template<typename T>
void orthogonal_list_generic_directed_graph_remove_vertex_test(GenericDirectedGraph<T> &graph) {
    graph.remove_vertex(2);

    assert(graph.get_vertexNum() == 3);
    assert(graph.get_vertex(1)->next->num == 3);
    auto n0 = graph.vertex_neighbors(0);
    auto n3 = graph.vertex_neighbors(3);

    assert(n0.size() == 1);
    directed_check_edge_field<std::string>(n0[0], nullptr, nullptr, nullptr, n3[1]);
    assert(graph.get_vertex(0)->firstOut == n3[0]);

    assert(n3.size() == 2);
    directed_check_edge_field<std::string>(n3[0], nullptr, n3[1], nullptr, nullptr);
    directed_check_edge_field<std::string>(n3[1], n3[0], nullptr, n0[0], nullptr);
    assert(graph.get_vertex(3)->firstOut == nullptr);
}

void orthogonal_list_generic_directed_graph_remove_edge_test_remove_edge_test() {
    GenericDirectedGraph<std::string> graph{};
    graph.insert_vertex(0, "A");
    graph.insert_vertex(1, "B");
    graph.insert_vertex(2, "C");
    graph.insert_vertex(3, "D");

    graph.insert_edge(0, 1);
    graph.insert_edge(0, 2);
    graph.insert_edge(2, 0);
    graph.insert_edge(2, 3);
    graph.insert_edge(3, 0);
    graph.insert_edge(3, 1);
    graph.insert_edge(3, 2);

    graph.remove_edge(2, 0);

    assert(graph.get_edgeNum() == 6);

    auto n0 = graph.vertex_neighbors(0);
    auto n2 = graph.vertex_neighbors(2);
    assert(n2.size() == 1);
    auto n3 = graph.vertex_neighbors(3);

    assert(graph.get_vertex(0)->firstOut == n3[0]);
    assert(graph.get_vertex(2)->firstIn == n2[0]);
    directed_check_edge_field<std::string>(n2[0], nullptr, nullptr, nullptr, nullptr);
    directed_check_edge_field<std::string>(n3[0], nullptr, n3[1], nullptr, nullptr);
}
