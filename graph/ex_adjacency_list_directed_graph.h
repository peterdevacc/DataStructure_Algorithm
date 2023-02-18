// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ADJACENCY_LIST_DIRECTED_GRAPH_H
#define EX_ADJACENCY_LIST_DIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::AdjacencyList {

    template<typename T>
    class DirectedGraph {
    public:
        explicit DirectedGraph(unsigned long vertexMaxNum) : vertexMaxNum(vertexMaxNum + 1), edgeNum(0) {
            vertices = new Vertex<T> *[this->vertexMaxNum];
            for (unsigned long i = 0; i < this->vertexMaxNum; ++i) {
                vertices[i] = nullptr;
            }
        }

        ~DirectedGraph() {
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                auto edges = vertices[i];
                while (edges != nullptr) {
                    auto e = edges;
                    edges = edges->next;
                    delete e;
                }
            }
            delete[]vertices;
        }

        void insert_edge(
            unsigned long num1, T data1, unsigned long num2, T data2,
            unsigned long weight = 1
        ) {
            if (verify_vertex_pair(num1, num2)) {

                if (vertices[num1] == nullptr) {
                    auto vertex1 = new Vertex<T>;
                    vertex1->num = num1;
                    vertex1->data = data1;

                    vertices[num1] = vertex1;
                }

                bool exist = false;
                auto edges = vertices[num1]->next;
                Vertex<T> *save = vertices[num1];
                while (edges != nullptr) {
                    if (edges->num == num2) {
                        exist = true;
                        break;
                    }

                    save = edges;
                    edges = edges->next;
                }

                if (!exist) {
                    auto vertex2 = new Vertex<T>;
                    if (vertices[num2] != nullptr) {
                        vertex2->num = num2;
                        vertex2->weight = weight;
                        vertex2->data = vertices[num2]->data;
                    } else {
                        vertex2->num = num2;
                        vertex2->weight = weight;
                        vertex2->data = data2;
                    }

                    save->next = vertex2;
                }

                edgeNum++;
            }
        }

        void remove_edge(unsigned long num1, unsigned long num2) {
            if (edgeNum > 0 && verify_vertex_pair(num1, num2)) {

                auto edges = vertices[num1];
                if (edges != nullptr) {
                    auto save = edges;
                    while (edges != nullptr) {
                        if (edges->num == num2) {
                            save->next = edges->next;
                            delete edges;
                            edgeNum--;

                            break;
                        }
                        save = edges;
                        edges = edges->next;
                    }
                }

            }
        }

        void insert_vertex(unsigned long num, T data) {
            if (is_vertex_in_range(num)) {
                if (vertices[num] == nullptr) {
                    auto vertex = new Vertex<T>;
                    vertex->num = num;
                    vertex->data = data;

                    vertices[num] = vertex;
                }
            }
        }

        void remove_vertex(unsigned long num) {
            if (is_vertex_in_range(num)) {
                auto edges = vertices[num];
                while (edges != nullptr) {
                    if (edges->num != num) {
                        edgeNum--;
                    }

                    auto e = edges;
                    edges = edges->next;
                    delete e;
                }

                vertices[num] = nullptr;
            }
        }

        auto vertex_neighbors(unsigned long num) {
            std::vector<Vertex<T> *> neighbors{};

            if (is_vertex_in_range(num)) {
                auto edges = vertices[num];
                if (edges != nullptr) {
                    auto temp = edges->next;
                    while (temp != nullptr) {
                        neighbors.push_back(temp);
                        temp = temp->next;
                    }
                }

            }

            return neighbors;
        }

        bool is_vertex_exist(unsigned long num) {
            if (is_vertex_in_range(num) && vertices[num] != nullptr) {
                return true;
            }
            return false;
        }

        bool is_edge_exist(unsigned long num1, unsigned long num2) {
            if (verify_vertex_pair(num1, num2) && edgeNum > 0) {
                auto edgesOne = vertices[num1];
                while (edgesOne != nullptr) {
                    if (edgesOne->num == num2) {
                        return true;
                    }
                    edgesOne = edgesOne->next;
                }
            }

            return false;
        }

        auto get_vertexMaxNum() {
            return vertexMaxNum - 1;
        }

        auto get_edgeNum() {
            return edgeNum;
        }

    private:
        bool is_vertex_in_range(unsigned long num) {
            return num < vertexMaxNum;
        }

        bool verify_vertex_pair(unsigned long num1, unsigned long num2) {
            return is_vertex_in_range(num1) && is_vertex_in_range(num2);
        }

        Vertex<T> **vertices;
        unsigned long vertexMaxNum;
        unsigned long edgeNum;
    };

    void directed_graph_test();

}

#endif //EX_ADJACENCY_LIST_DIRECTED_GRAPH_H
