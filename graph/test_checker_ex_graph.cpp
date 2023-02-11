// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "core_graph.h"

void Ex::AdjacencyList::adjacencyListCheckVertex(
    Ex::AdjacencyList::Vertex *vertex,
    unsigned long num,
    unsigned long weight
) {
    assert(vertex->num == num);
    assert(vertex->weight == weight);
}

void Ex::AdjacencyMatrix::adjacencyMatrixCheckVertex(
    std::pair<unsigned long, unsigned long> vertex,
    unsigned long data,
    unsigned long weight
) {
    assert(vertex.first == data);
    assert(vertex.second == weight);
}

void Ex::AdjacencyMultiList::adjacencyMultiListUnDirectedCheckEdgeData(
    Edge *edge,
    unsigned long position,
    unsigned long weight
) {
    assert(edge->weight == weight);
    assert(edge->tailVertexPosition == position);
}

void Ex::AdjacencyMultiList::adjacencyMultiListUnDirectedCheckEdgeField(
    Edge *edge,
    Edge *headRelatedNext,
    Edge *tailRelatedNext
) {
    assert(edge->headRelatedNext == headRelatedNext);
    assert(edge->tailRelatedNext == tailRelatedNext);
}

void Ex::OrthogonalList::orthogonalListDirectedCheckVertexField(
    std::optional<Vertex> vertex,
    Edge *in,
    Edge *out
) {
    assert(vertex.value().firstIn == in);
    assert(vertex.value().firstOut == out);
}

void Ex::OrthogonalList::orthogonalListDirectedCheckEdgeField(
    Edge *edge,
    Edge *nextHead,
    Edge *nextTail
) {
    assert(edge->headFieldNext == nextHead);
    assert(edge->tailFieldNext == nextTail);
}

void Ex::OrthogonalList::orthogonalListDirectedCheckEdgeData(
    Edge *neighbor,
    unsigned long num,
    unsigned long weight
) {
    assert(neighbor->tail == num);
    assert(neighbor->weight == weight);
}
