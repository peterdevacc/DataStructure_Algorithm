//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ADJACENCY_LIST_DIRECTED_GRAPH_H
#define EX_ADJACENCY_LIST_DIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::AdjacencyList {

    class DirectedGraph {
    public:
        explicit DirectedGraph(unsigned long vertexMaxNum)
                : vertexMaxNum(vertexMaxNum), edgeNum(0) {
            vertices = new Vertex *[vertexMaxNum];
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
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

        void insert_edge(unsigned long num1, unsigned long num2, unsigned long weight = 1) {
            if (check_vertex_pair(num1, num2) && weight > 0) {
                insert_direction(num1, num2, weight);
                edgeNum++;
            }
        }

        void remove_edge(unsigned long num1, unsigned long num2) {
            if (check_vertex_pair(num1, num2) && edgeNum > 0) {
                remove_direction(num1, num2);
                edgeNum--;
            }
        }

        auto vertex_neighbors(unsigned long num) {
            std::vector<Vertex *> neighbors{};

            if (check_vertex(num)) {
                auto edgesOne = vertices[num];
                while (edgesOne != nullptr) {
                    neighbors.push_back(edgesOne);
                    edgesOne = edgesOne->next;
                }
            }

            return neighbors;
        }

        auto is_edge_exist(unsigned long num1, unsigned long num2) {
            if (check_vertex_pair(num1, num2) && edgeNum > 0) {
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

        bool insert_direction(unsigned long num1, unsigned long num2, unsigned long weight) {
            auto vertex = new Vertex;
            vertex->num = num2;
            vertex->weight = weight;
            auto exist = false;
            if (vertices[num1] == nullptr) {
                vertices[num1] = vertex;
            } else {
                auto edges = vertices[num1];
                while (edges->next != nullptr) {
                    if (edges->num == num2) {
                        exist = true;
                        delete vertex;
                        break;
                    }
                    edges = edges->next;
                }
                if (!exist) {
                    edges->next = vertex;
                }
            }

            return exist;
        }

        bool remove_direction(unsigned long num1, unsigned long num2) {
            auto edges = vertices[num1];
            auto exist = false;
            if (edges->num == num2) {
                vertices[num1] = edges->next;
                delete edges;
                exist = true;
            } else {
                auto save = edges;
                while (edges != nullptr) {
                    if (edges->num == num2) {
                        save->next = edges->next;
                        delete edges;
                        exist = true;
                        break;
                    }
                    save = edges;
                    edges = edges->next;
                }
            }

            return exist;
        }

        Vertex **vertices;
        unsigned long vertexMaxNum;
        unsigned long edgeNum;
    };

    void ex_adjacency_list_directed_graph_test();

}

#endif //EX_ADJACENCY_LIST_DIRECTED_GRAPH_H
