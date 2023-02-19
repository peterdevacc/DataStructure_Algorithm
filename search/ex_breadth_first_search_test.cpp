// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/18.
//

#include "ex_breadth_first_search.h"

using namespace Ex::Search;

void breadth_first_search_directed_graph();
void breadth_first_search_undirected_graph();

void Ex::Search::breadth_first_search_test() {
    breadth_first_search_directed_graph();
    breadth_first_search_undirected_graph();
}

void breadth_first_search_directed_graph() {
    unsigned long maxVertexNum = 7;
    std::vector<std::pair<unsigned long, unsigned long>> edges{
        std::make_pair(0, 1),
        std::make_pair(0, 3),
        std::make_pair(0, 2),
        std::make_pair(1, 5),
        std::make_pair(1, 2),
        std::make_pair(6, 1),
        std::make_pair(6, 5),
        std::make_pair(2, 4),
        std::make_pair(4, 3),
    };
    auto directedGraph = generate_adjacency_list_graph<EdgeType::DIRECTED>(
        maxVertexNum, edges
    );

    auto testData = std::make_pair<unsigned long, std::vector<unsigned long>>(
        1,
        {1, 5, 2, 4, 3}
    );
    auto result = breadth_first_search<EdgeType::DIRECTED>(
        directedGraph, testData.first
    );
    verify_adjacency_list_graph_search_result<EdgeType::DIRECTED>(result, testData.second);

    testData = std::make_pair<unsigned long, std::vector<unsigned long>>(
        0,
        {0, 1, 3, 2, 5, 4}
    );
    result = breadth_first_search<EdgeType::DIRECTED>(
        directedGraph, testData.first
    );
    verify_adjacency_list_graph_search_result<EdgeType::DIRECTED>(result, testData.second);

}

void breadth_first_search_undirected_graph() {
    unsigned long maxVertexNum = 7;
    std::vector<std::pair<unsigned long, unsigned long>> edges{
        std::make_pair(0, 1),
        std::make_pair(0, 3),
        std::make_pair(0, 2),
        std::make_pair(1, 5),
        std::make_pair(1, 2),
        std::make_pair(6, 1),
        std::make_pair(6, 5),
        std::make_pair(2, 4),
        std::make_pair(4, 3),
    };
    auto directedGraph = generate_adjacency_list_graph<EdgeType::UNDIRECTED>(
        maxVertexNum, edges
    );

    auto testData = std::make_pair<unsigned long, std::vector<unsigned long>>(
        1,
        {1, 0, 5, 2, 6, 3, 4}
    );
    auto result = breadth_first_search<EdgeType::UNDIRECTED>(
        directedGraph, testData.first
    );
    verify_adjacency_list_graph_search_result<EdgeType::UNDIRECTED>(result, testData.second);

    testData = std::make_pair<unsigned long, std::vector<unsigned long>>(
        0,
        {0, 1, 3, 2, 5, 6, 4}
    );
    result = breadth_first_search<EdgeType::DIRECTED>(
        directedGraph, testData.first
    );
    verify_adjacency_list_graph_search_result<EdgeType::UNDIRECTED>(result, testData.second);

}
