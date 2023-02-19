// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/18.
//

#include "ex_depth_first_search.h"

using namespace Ex::Search;

void depth_first_search_directed_graph();
void depth_first_search_undirected_graph();

void Ex::Search::depth_first_search_test() {
    depth_first_search_directed_graph();
    depth_first_search_undirected_graph();
}

void depth_first_search_directed_graph() {
    unsigned long maxVertexNum = 7;
    std::vector<std::pair<unsigned long, unsigned long>> edges{
        std::make_pair(0, 1),
        std::make_pair(0, 4),
        std::make_pair(0, 2),
        std::make_pair(1, 5),
        std::make_pair(1, 2),
        std::make_pair(6, 1),
        std::make_pair(6, 3),
        std::make_pair(2, 4),
        std::make_pair(4, 3),
        std::make_pair(5, 0),
    };
    auto directedGraph = generate_adjacency_list_graph<EdgeType::DIRECTED>(
        maxVertexNum, edges
    );

    auto testData = std::make_pair<unsigned long, std::vector<unsigned long>>(
        1,
        {1, 5, 0, 4, 3, 2}
    );
    auto result = depth_first_search<EdgeType::DIRECTED>(
        directedGraph, testData.first
    );

    verify_adjacency_list_graph_search_result<EdgeType::DIRECTED>(result, testData.second);

    testData = std::make_pair<unsigned long, std::vector<unsigned long>>(
        6,
        {6, 1, 5, 0, 4, 3, 2}
    );
    result = depth_first_search<EdgeType::DIRECTED>(
        directedGraph, testData.first
    );
    verify_adjacency_list_graph_search_result<EdgeType::DIRECTED>(result, testData.second);

}

void depth_first_search_undirected_graph() {
    unsigned long maxVertexNum = 7;
    std::vector<std::pair<unsigned long, unsigned long>> edges{
        std::make_pair(0, 1),
        std::make_pair(0, 4),
        std::make_pair(0, 2),
        std::make_pair(1, 5),
        std::make_pair(1, 2),
        std::make_pair(6, 1),
        std::make_pair(6, 3),
        std::make_pair(2, 4),
        std::make_pair(4, 3),
        std::make_pair(5, 0),
    };
    auto directedGraph = generate_adjacency_list_graph<EdgeType::UNDIRECTED>(
        maxVertexNum, edges
    );

    auto testData = std::make_pair<unsigned long, std::vector<unsigned long>>(
        1,
        {1, 0, 4, 2, 3, 6, 5}
    );
    auto result = depth_first_search<EdgeType::UNDIRECTED>(
        directedGraph, testData.first
    );
    verify_adjacency_list_graph_search_result<EdgeType::UNDIRECTED>(result, testData.second);

    testData = std::make_pair<unsigned long, std::vector<unsigned long>>(
        6,
        {6, 1, 0, 4, 2, 3, 5}
    );
    result = depth_first_search<EdgeType::DIRECTED>(
        directedGraph, testData.first
    );
    verify_adjacency_list_graph_search_result<EdgeType::UNDIRECTED>(result, testData.second);

}
