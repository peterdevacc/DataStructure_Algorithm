// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ADJACENCY_MATRIX_DIRECTED_GRAPH_H
#define EX_ADJACENCY_MATRIX_DIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::AdjacencyMatrix {

    template<typename T>
    class DirectedGraph {
    public:
        explicit DirectedGraph(unsigned long vertexMaxNum): vertexMaxNum(vertexMaxNum + 1), vertexNum(0), edgeNum(0) {
            vertices = new Vertex<T> *[this->vertexMaxNum];
            for (unsigned long i = 0; i < this->vertexMaxNum; ++i) {
                vertices[i] = new Vertex<T>[this->vertexMaxNum];
            }
        }

        ~DirectedGraph() {
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                delete[]vertices[i];
            }
            delete[]vertices;
        }

        void insert_edge(
            unsigned long num1, T data1, unsigned long num2, T data2,
            unsigned long weight = 1
        ) {
            if (num1 >= 1 && num1 < vertexMaxNum && num2 >= 1 && num2 < vertexMaxNum) {
                if (vertices[num1]->num == 0) {
                    vertices[num1]->num = num1;
                    vertices[num1]->data = data1;
                    vertexNum++;
                }

                if (vertices[num2]->num == 0) {
                    vertices[num2]->num = num2;
                    vertices[num2]->data = data2;
                    vertexNum++;
                }

                if (vertices[num1][num2].weight == 0) {
                    vertices[num1][num2].num = num2;
                    vertices[num1][num2].data = data2;
                    vertices[num1][num2].weight = weight;
                    edgeNum++;
                }
            }
        }

        void insert_edge(unsigned long num1, unsigned long num2, unsigned long weight = 1) {
            if (verify_vertex_pair(num1, num2)) {
                if (vertices[num1][num2].weight == 0) {
                    vertices[num1][num2].num = num2;
                    vertices[num1][num2].data = vertices[num2]->data;
                    vertices[num1][num2].weight = weight;
                    edgeNum++;
                }
            }
        }

        void remove_edge(unsigned long num1, unsigned long num2) {
            if (edgeNum > 0 && verify_vertex_pair(num1, num2)) {
                if (vertices[num1][num2].weight != 0) {
                    vertices[num1][num2].num = 0;
                    vertices[num1][num2].data = std::optional<T>();
                    vertices[num1][num2].weight = 0;
                    edgeNum--;
                }
            }
        }

        void insert_vertex(unsigned long num, T data) {
            if (num >= 1 && num < vertexMaxNum && vertices[num]->num == 0) {
                vertices[num]->num = num;
                vertices[num]->data = data;
                vertexNum++;
            }
        }

        void remove_vertex(unsigned long num) {
            if (verify_vertex(num)) {
                for (unsigned long i = 1; i < vertexMaxNum; ++i) {
                    if (vertices[i][num].weight != 0) {
                        vertices[i][num].num = 0;
                        vertices[i][num].data = std::optional<T>();
                        vertices[i][num].weight = 0;
                        edgeNum--;
                    }
                    if (vertices[num][i].weight != 0) {
                        vertices[num][i].num = 0;
                        vertices[num][i].data = std::optional<T>();
                        vertices[num][i].weight = 0;
                        edgeNum--;
                    }
                }

                vertices[num]->num = 0;
                vertices[num]->data = std::optional<T>();
                vertices[num]->weight = 0;
                vertexNum--;
            }
        }

        auto vertex_neighbors(unsigned long num) {
            std::vector<Vertex<T>> neighbors{};
            if (verify_vertex(num)) {
                auto edges = vertices[num];
                for (unsigned long i = 1; i < vertexMaxNum; ++i) {
                    if (edges[i].weight != 0) {
                        neighbors.push_back(edges[i]);
                    }
                }
            }

            return neighbors;
        }

        bool is_vertex_exist(unsigned long num) {
            return verify_vertex(num);
        }

        auto is_edge_exist(unsigned long num1, unsigned long num2) {
            if (verify_vertex_pair(num1, num2) && edgeNum > 0) {
                return vertices[num1][num2].weight != 0;
            }

            return false;
        }

        auto get_vertexMaxNum() {
            return vertexMaxNum - 1;
        }

        auto get_vertexNum() {
            return vertexNum;
        }

        auto get_edgeNum() {
            return edgeNum;
        }

    private:
        bool verify_vertex(unsigned long num) {
            return num >= 1 && num < vertexMaxNum && vertices[num]->num != 0;
        }

        bool verify_vertex_pair(unsigned long num1, unsigned long num2) {
            return verify_vertex(num1) && verify_vertex(num2);
        }

        Vertex<T> **vertices;
        unsigned long vertexMaxNum;
        unsigned long vertexNum;
        unsigned long edgeNum;
    };

    void directed_graph_test();

}

#endif //EX_ADJACENCY_MATRIX_DIRECTED_GRAPH_H
