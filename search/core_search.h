// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/18.
//

#ifndef CORE_SEARCH_H
#define CORE_SEARCH_H

#include <stack>
#include <vector>
#include <queue>
#include <utility>
#include <cassert>

namespace Ex {

    namespace Search {

        enum EdgeType {
            DIRECTED, UNDIRECTED
        };

        template<EdgeType type>
        std::vector<std::vector<unsigned long>> generate_adjacency_list_graph(
            unsigned long vertexMaxNum,
            std::vector<std::pair<unsigned long, unsigned long>> &edges
        ) {
            std::vector<std::vector<unsigned long>> data(
                vertexMaxNum,
                std::vector<unsigned long>{}
            );

            for (const auto &item: edges) {
                if constexpr (type == EdgeType::DIRECTED) {
                    data[item.first].push_back(item.second);
                } else if constexpr (type == EdgeType::UNDIRECTED) {
                    data[item.first].push_back(item.second);
                    data[item.second].push_back(item.first);
                }
            }

            return data;
        }

        template<EdgeType type>
        void verify_adjacency_list_graph_search_result(
            std::vector<unsigned long> &result, std::vector<unsigned long> &expected
        ){
            if constexpr (type == EdgeType::DIRECTED || type == EdgeType::UNDIRECTED) {
                assert(result.size() == expected.size());
                for (unsigned long i = 0; i < result.size(); ++i) {
                    assert(result[i] == expected[i]);
                }
            }
        }

    }

    void test_search();

}

#endif //CORE_SEARCH_H
