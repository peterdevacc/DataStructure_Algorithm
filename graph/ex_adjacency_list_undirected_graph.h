// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ADJACENCY_LIST_UNDIRECTED_GRAPH_H
#define EX_ADJACENCY_LIST_UNDIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::AdjacencyList {

    template<typename T>
    class UnDirectedGraph {
    public:
        explicit UnDirectedGraph(unsigned long vertexMaxNum) : vertexMaxNum(vertexMaxNum + 1), edgeNum(0) {
            vertices = new Vertex<T> *[this->vertexMaxNum];
            for (unsigned long i = 0; i < this->vertexMaxNum; ++i) {
                vertices[i] = nullptr;
            }
        }

        ~UnDirectedGraph() {
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
            if (verify_vertex_pair(num1, num2) && weight > 0) {
                bool existOne;
                bool existTwo;
                if (num1 == num2) {
                    existOne = insert_direction(num1, data1, num2, data2, weight);
                    existTwo = existOne;
                } else {
                    existOne = insert_direction(num1, data1, num2, data2, weight);
                    existTwo = insert_direction(num2, data2, num1, data1, weight);
                }

                if (!existOne || !existTwo) {
                    edgeNum++;
                }
            }
        }

        void remove_edge(unsigned long num1, unsigned long num2) {
            if (verify_vertex_pair(num1, num2) && edgeNum > 0) {
                bool resultOne;
                bool resultTwo;
                if (num1 == num2) {
                    resultOne = remove_direction(num1, num2);
                    resultTwo = resultOne;
                } else {
                    resultOne = remove_direction(num1, num2);
                    resultTwo = remove_direction(num2, num1);
                }

                if (resultOne && resultTwo) {
                    edgeNum--;
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
                std::vector<unsigned long> keys{};
                auto edges = vertices[num];
                while (edges != nullptr) {
                    if (edges->num != num) {
                        keys.push_back(edges->num);
                    }

                    auto e = edges;
                    edges = edges->next;
                    delete e;
                }
                vertices[num] = nullptr;

                for (auto key: keys) {
                    auto temp = vertices[key]->next;
                    Vertex<T> *save = vertices[key];
                    while (temp != nullptr) {
                        if (temp->num == num) {
                            auto e = temp;
                            save->next = temp->next;
                            delete e;
                            edgeNum--;

                            break;
                        }

                        save = temp;
                        temp = temp->next;
                    }
                }
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

        auto is_edge_exist(unsigned long num1, unsigned long num2) {
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

        bool insert_direction(
            unsigned long num1, T data1, unsigned long num2, T data2,
            unsigned long weight
        ) {
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

            return exist;
        }

        bool remove_direction(unsigned long num1, unsigned long num2) {
            bool result = false;
            if (edgeNum > 0 && verify_vertex_pair(num1, num2)) {

                auto edges = vertices[num1];
                if (edges != nullptr) {
                    auto save = edges;
                    while (edges != nullptr) {
                        if (edges->num == num2) {
                            save->next = edges->next;
                            delete edges;

                            result = true;
                            break;
                        }
                        save = edges;
                        edges = edges->next;
                    }
                }

            }

            return result;
        }

        Vertex<T> **vertices;
        unsigned long vertexMaxNum;
        unsigned long edgeNum;
    };

    void undirected_graph_test();

}

#endif //EX_ADJACENCY_LIST_UNDIRECTED_GRAPH_H
