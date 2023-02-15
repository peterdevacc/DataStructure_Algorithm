// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "core_graph.h"

void Ex::AdjacencyList::check_vertex(
    Ex::AdjacencyList::Vertex *vertex,
    unsigned long num,
    unsigned long weight
) {
    assert(vertex->num == num);
    assert(vertex->weight == weight);
}

void Ex::AdjacencyMatrix::check_vertex(
    std::pair<unsigned long, unsigned long> vertex,
    unsigned long data,
    unsigned long weight
) {
    assert(vertex.first == data);
    assert(vertex.second == weight);
}

void Ex::AdjacencyMultiList::undirected_check_edge_data(
    Edge *edge,
    unsigned long position,
    unsigned long weight
) {
    assert(edge->weight == weight);
    assert(edge->tailVertexPosition == position);
}

void Ex::AdjacencyMultiList::undirected_check_edge_field(
    Edge *edge,
    Edge *headRelatedNext,
    Edge *tailRelatedNext
) {
    assert(edge->headRelatedNext == headRelatedNext);
    assert(edge->tailRelatedNext == tailRelatedNext);
}

void Ex::OrthogonalList::directed_check_vertex_field(
    std::optional<Vertex> vertex,
    Edge *in,
    Edge *out
) {
    assert(vertex.value().firstIn == in);
    assert(vertex.value().firstOut == out);
}

void Ex::OrthogonalList::directed_check_edge_field(
    Edge *edge,
    Edge *nextHead,
    Edge *nextTail
) {
    assert(edge->headFieldNext == nextHead);
    assert(edge->tailFieldNext == nextTail);
}

void Ex::OrthogonalList::directed_check_edge_data(
    Edge *neighbor,
    unsigned long num,
    unsigned long weight
) {
    assert(neighbor->tail == num);
    assert(neighbor->weight == weight);
}
