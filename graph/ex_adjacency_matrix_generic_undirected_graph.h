// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ADJACENCY_MATRIX_GENERIC_UNDIRECTED_GRAPH_H
#define EX_ADJACENCY_MATRIX_GENERIC_UNDIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::AdjacencyMatrix {

    template<typename T>
    class GenericUnDirectedGraph {
    public:
        explicit GenericUnDirectedGraph(unsigned long vertexMaxNum)
                : vertexMaxNum(vertexMaxNum), vertexNum(0), edgeNum(0) {
            vertices = new GenericVertex<T> *[vertexMaxNum];
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                vertices[i] = new GenericVertex<T>[vertexMaxNum];
            }
        }

        ~GenericUnDirectedGraph() {
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                delete[]vertices[i];
            }
            delete[]vertices;
        }

        void insert_vertex(unsigned long num, T data) {
            if (num >= 1 && num < vertexMaxNum && !vertices[num]->num.has_value()) {
                vertices[num]->num = num;
                vertices[num]->data = data;
                vertexNum++;
            }
        }

        void insert_edge(unsigned long num1, unsigned long num2, unsigned long weight = 1) {
            if (check_vertex_pair(num1, num2) && weight > 0) {
                if (vertices[num1][num2].weight == 0) {
                    vertices[num1][num2].num = num2;
                    vertices[num1][num2].weight = weight;
                    vertices[num1][num2].data = vertices[num2]->data;
                    vertices[num2][num1].num = num1;
                    vertices[num2][num1].weight = weight;
                    vertices[num2][num1].data = vertices[num1]->data;
                    edgeNum++;
                }
            }
        }

        void remove_vertex(unsigned long num) {
            if (check_vertex(num)) {
                for (unsigned long i = 1; i < vertexMaxNum; ++i) {
                    if (vertices[i][num].weight != 0) {
                        vertices[i][num].weight = 0;
                        vertices[i][num].num = std::optional<long>();
                        vertices[i][num].data = std::optional<T>();
                        vertices[num][i].num = std::optional<long>();
                        vertices[num][i].weight = 0;
                        vertices[num][i].data = std::optional<T>();
                        edgeNum--;
                    }
                }
                vertices[num]->num = std::optional<long>();
                vertices[num]->weight = 0;
                vertices[num]->data = std::optional<T>();
                vertexNum--;
            }
        }

        void remove_edge(unsigned long num1, unsigned long num2) {
            if (check_vertex_pair(num1, num2) && edgeNum > 0) {
                if (vertices[num1][num2].weight != 0) {
                    vertices[num1][num2].num = std::optional<long>();
                    vertices[num1][num2].weight = 0;
                    vertices[num1][num2].data = std::optional<T>();
                    vertices[num2][num1].num = std::optional<long>();
                    vertices[num2][num1].weight = 0;
                    vertices[num2][num1].data = std::optional<T>();
                    edgeNum--;
                }
            }
        }

        auto vertex_neighbors(unsigned long num) {
            std::vector<GenericVertex < T>>
                    neighbors{};
            if (check_vertex(num)) {
                auto edges = vertices[num];
                for (unsigned long i = 1; i < vertexMaxNum; ++i) {
                    if (edges[i].weight != 0) {
                        neighbors.push_back(edges[i]);
                    }
                }
            }

            return neighbors;
        }

        auto is_vertex_exist(unsigned long num) {
            return check_vertex(num);
        }

        auto is_edge_exist(unsigned long num1, unsigned long num2) {
            if (check_vertex_pair(num1, num2) && edgeNum > 0) {
                return vertices[num1][num2].weight != 0;
            }

            return false;
        }

        auto get_vertexMaxNum() {
            return vertexMaxNum;
        }

        auto get_vertexNum() {
            return vertexNum;
        }

        auto get_edgeNum() {
            return edgeNum;
        }

    private:
        bool check_vertex(unsigned long num) {
            return num >= 1 && num < vertexMaxNum && vertices[num]->num.has_value();
        }

        bool check_vertex_pair(unsigned long num1, unsigned long num2) {
            return check_vertex(num1) && check_vertex(num2);
        }

        GenericVertex <T> **vertices;
        unsigned long vertexMaxNum;
        unsigned long vertexNum;
        unsigned long edgeNum;
    };

    void ex_adjacency_matrix_generic_undirected_graph_test();

}

#endif //EX_ADJACENCY_MATRIX_GENERIC_UNDIRECTED_GRAPH_H
