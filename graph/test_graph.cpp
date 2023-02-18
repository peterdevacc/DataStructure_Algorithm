// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_adjacency_list_directed_graph.h"
#include "ex_adjacency_list_undirected_graph.h"
#include "ex_adjacency_matrix_directed_graph.h"
#include "ex_adjacency_matrix_undirected_graph.h"
#include "ex_adjacency_multi_list_undirected_graph.h"
#include "ex_orthogonal_list_directed_graph.h"

void Ex::test_graph() {
    AdjacencyList::directed_graph_test();
    AdjacencyList::undirected_graph_test();
    AdjacencyMatrix::directed_graph_test();
    AdjacencyMatrix::undirected_graph_test();
    AdjacencyMultiList::undirected_graph_test();
    OrthogonalList::directed_graph_test();
}
