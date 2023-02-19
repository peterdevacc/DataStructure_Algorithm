// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/18.
//

#ifndef EX_BREADTH_FIRST_SEARCH_H
#define EX_BREADTH_FIRST_SEARCH_H

#include "core_search.h"

namespace Ex::Search {

    template<EdgeType type>
    std::vector<unsigned long> breadth_first_search(
        std::vector<std::vector<unsigned long>> &graph,
        unsigned long startVertex
    ) {
        std::vector<unsigned long> result{};

        std::vector<bool> visited(graph.size(), false);
        std::queue<unsigned long> vertexQueue{};

        if constexpr (type == EdgeType::DIRECTED || type == EdgeType::UNDIRECTED) {
            vertexQueue.push(startVertex);
            result.push_back(startVertex);
            visited[startVertex] = true;

            while (!vertexQueue.empty()) {
                auto vertex = vertexQueue.front();
                vertexQueue.pop();

                for (auto neighbor: graph[vertex]) {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        result.push_back(neighbor);
                        vertexQueue.push(neighbor);
                    }
                }

            }
        }

        return result;
    }

    void breadth_first_search_test();

}

#endif //EX_BREADTH_FIRST_SEARCH_H
