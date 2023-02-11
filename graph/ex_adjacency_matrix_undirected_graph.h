// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ADJACENCY_MATRIX_UNDIRECTED_GRAPH_H
#define EX_ADJACENCY_MATRIX_UNDIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::AdjacencyMatrix {

    class UnDirectedGraph {
    public:
        explicit UnDirectedGraph(unsigned long vertexMaxNum)
                : vertexMaxNum(vertexMaxNum), edgeNum(0) {
            vertices = new unsigned long *[vertexMaxNum];
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                vertices[i] = new unsigned long[vertexMaxNum];
                for (unsigned long j = 0; j < vertexMaxNum; ++j) {
                    vertices[i][j] = 0;
                }
            }
        }

        ~UnDirectedGraph() {
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                delete[]vertices[i];
            }
            delete[]vertices;
        }

        void insert_edge(unsigned long num1, unsigned long num2, unsigned long weight = 1) {
            if (check_vertex_pair(num1, num2)) {
                if (vertices[num1][num2] == 0) {
                    vertices[num1][num2] = weight;
                    vertices[num2][num1] = weight;
                    edgeNum++;
                }
            }
        }

        void remove_edge(unsigned long num1, unsigned long num2) {
            if (check_vertex_pair(num1, num2) && edgeNum > 0) {
                if (vertices[num1][num2] != 0) {
                    vertices[num1][num2] = 0;
                    vertices[num2][num1] = 0;
                    edgeNum--;
                }
            }
        }

        auto vertex_neighbors(unsigned long num) {
            std::vector<std::pair<unsigned long, unsigned long>> neighbors{};
            if (check_vertex(num)) {
                auto edges = vertices[num];
                for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                    if (edges[i] != 0) {
                        neighbors.push_back(std::make_pair<>(i, edges[i]));
                    }
                }
            }

            return neighbors;
        }

        auto is_edge_exist(unsigned long num1, unsigned long num2) {
            if (check_vertex_pair(num1, num2) && edgeNum > 0) {
                return vertices[num1][num2] != 0;
            }

            return false;
        }

        auto get_vertexMaxNum() {
            return vertexMaxNum;
        }

        auto get_edgeNum() {
            return edgeNum;
        }

    private:
        bool check_vertex(unsigned long num) {
            return num < vertexMaxNum;
        }

        bool check_vertex_pair(unsigned long num1, unsigned long num2) {
            return check_vertex(num1) && check_vertex(num2);
        }

        unsigned long **vertices;
        unsigned long vertexMaxNum;
        unsigned long edgeNum;
    };

    void ex_adjacency_matrix_undirected_graph_test();

}

#endif //EX_ADJACENCY_MATRIX_UNDIRECTED_GRAPH_H
