// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_orthogonal_list_directed_graph.h"

using namespace Ex::OrthogonalList;

void ex_orthogonal_list_directed_graph_unweighted();

void ex_orthogonal_list_directed_graph_weighted();

void Ex::OrthogonalList::ex_orthogonal_list_directed_graph_test() {
    ex_orthogonal_list_directed_graph_unweighted();
    ex_orthogonal_list_directed_graph_weighted();
}

void ex_orthogonal_list_directed_graph_unweighted() {
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
    orthogonalListDirectedCheckEdgeData(n0[0], 1);
    orthogonalListDirectedCheckEdgeData(n0[1], 2);
    orthogonalListDirectedCheckEdgeField(n0[0], n0[1], n3[1]);
    orthogonalListDirectedCheckEdgeField(n0[1], nullptr, n3[2]);

    assert(n1.empty());

    assert(n2.size() == 2);
    orthogonalListDirectedCheckEdgeData(n2[0], 0);
    orthogonalListDirectedCheckEdgeData(n2[1], 3);
    orthogonalListDirectedCheckEdgeField(n2[0], n2[1], n3[0]);
    orthogonalListDirectedCheckEdgeField(n2[1], nullptr, nullptr);

    assert(n3.size() == 3);
    orthogonalListDirectedCheckEdgeData(n3[0], 0);
    orthogonalListDirectedCheckEdgeData(n3[1], 1);
    orthogonalListDirectedCheckEdgeData(n3[2], 2);
    orthogonalListDirectedCheckEdgeField(n3[0], n3[1], nullptr);
    orthogonalListDirectedCheckEdgeField(n3[1], n3[2], nullptr);
    orthogonalListDirectedCheckEdgeField(n3[2], nullptr, nullptr);

    auto v0 = graph.get_vertex(0);
    orthogonalListDirectedCheckVertexField(v0, n0[0], n2[0]);
    auto v1 = graph.get_vertex(1);
    orthogonalListDirectedCheckVertexField(v1, nullptr, n0[0]);
    auto v2 = graph.get_vertex(2);
    orthogonalListDirectedCheckVertexField(v2, n2[0], n0[1]);
    auto v3 = graph.get_vertex(3);
    orthogonalListDirectedCheckVertexField(v3, n3[0], n2[1]);

    graph.remove_edge(3, 0);
    assert(graph.get_edgeNum() == 6);
    v3 = graph.get_vertex(3);
    orthogonalListDirectedCheckVertexField(v3, n3[1], n2[1]);
    n2 = graph.vertex_neighbors(2);
    orthogonalListDirectedCheckEdgeField(n2[0], n2[1], nullptr);

    graph.remove_edge(0, 1);
    assert(graph.get_edgeNum() == 5);
    v0 = graph.get_vertex(0);
    v1 = graph.get_vertex(1);
    n0 = graph.vertex_neighbors(0);
    n2 = graph.vertex_neighbors(2);
    n3 = graph.vertex_neighbors(3);
    orthogonalListDirectedCheckEdgeData(n0[0], 2);
    orthogonalListDirectedCheckVertexField(v0, n0[0], n2[0]);
    orthogonalListDirectedCheckVertexField(v1, nullptr, n3[0]);
    orthogonalListDirectedCheckEdgeField(n0[0], nullptr, n3[1]);
}

void ex_orthogonal_list_directed_graph_weighted() {
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
    orthogonalListDirectedCheckEdgeData(n0[0], 1, 2);
    orthogonalListDirectedCheckEdgeData(n0[1], 2, 3);

    assert(n1.empty());

    assert(n2.size() == 2);
    orthogonalListDirectedCheckEdgeData(n2[0], 0, 3);
    orthogonalListDirectedCheckEdgeData(n2[1], 3, 1);

    assert(n3.size() == 3);
    orthogonalListDirectedCheckEdgeData(n3[0], 0, 1);
    orthogonalListDirectedCheckEdgeData(n3[1], 1, 2);
    orthogonalListDirectedCheckEdgeData(n3[2], 2, 1);
}
