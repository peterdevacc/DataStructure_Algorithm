// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/18.
//

#ifndef EX_DEPTH_FIRST_SEARCH_H
#define EX_DEPTH_FIRST_SEARCH_H

#include "core_search.h"

namespace Ex::Search {

    template<EdgeType type>
    std::vector<unsigned long> depth_first_search(
        std::vector<std::vector<unsigned long>> &graph,
        unsigned long startVertex
    ) {
        std::vector<unsigned long> result{};

        std::vector<bool> visited(graph.size(), false);
        std::stack<unsigned long> vertexStack{};

        if constexpr (type == EdgeType::DIRECTED || type == EdgeType::UNDIRECTED) {
            vertexStack.push(startVertex);

            while (!vertexStack.empty()) {
                auto top = vertexStack.top();
                vertexStack.pop();

                if (!visited[top]) {
                    visited[top] = true;
                    result.push_back(top);
                }

                std::for_each(graph[top].rbegin(), graph[top].rend(), [&](const auto neighbor){
                    if (!visited[neighbor]) {
                        vertexStack.push(neighbor);
                    }
                });

            }

        }

        return result;
    }

    void depth_first_search_test();

}

#endif //EX_DEPTH_FIRST_SEARCH_H
