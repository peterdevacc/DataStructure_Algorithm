// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_adjacency_list_directed_graph.h"
#include "ex_adjacency_list_generic_directed_graph.h"
#include "ex_adjacency_list_undirected_graph.h"
#include "ex_adjacency_list_generic_undirected_graph.h"
#include "ex_adjacency_matrix_directed_graph.h"
#include "ex_adjacency_matrix_generic_directed_graph.h"
#include "ex_adjacency_matrix_undirected_graph.h"
#include "ex_adjacency_matrix_generic_undirected_graph.h"
#include "ex_adjacency_multi_list_undirected_graph.h"
#include "ex_adjacency_multi_list_generic_undirected_graph.h"
#include "ex_orthogonal_list_directed_graph.h"
#include "ex_orthogonal_list_generic_directed_graph.h"

void Ex::test_graph() {
    AdjacencyList::ex_adjacency_list_directed_graph_test();
    AdjacencyList::ex_adjacency_list_generic_directed_graph_test();
    AdjacencyList::ex_adjacency_list_undirected_graph_test();
    AdjacencyList::ex_adjacency_list_generic_undirected_graph_test();
    AdjacencyMatrix::ex_adjacency_matrix_directed_graph_test();
    AdjacencyMatrix::ex_adjacency_matrix_generic_directed_graph_test();
    AdjacencyMatrix::ex_adjacency_matrix_undirected_graph_test();
    AdjacencyMatrix::ex_adjacency_matrix_generic_undirected_graph_test();
    AdjacencyMultiList::ex_adjacency_multi_list_generic_undirected_graph_test();
    AdjacencyMultiList::ex_adjacency_multi_list_undirected_graph_test();
    OrthogonalList::ex_orthogonal_list_directed_graph_test();
    OrthogonalList::ex_orthogonal_list_generic_directed_graph_test();
}
