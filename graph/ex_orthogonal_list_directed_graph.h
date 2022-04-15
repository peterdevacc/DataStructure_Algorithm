//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ORTHOGONAL_LIST_DIRECTED_GRAPH_H
#define EX_ORTHOGONAL_LIST_DIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::OrthogonalList {

    class DirectedGraph {
    public:
        explicit DirectedGraph(unsigned long vertexMaxNum)
                : vertexMaxNum(vertexMaxNum), edgeNum(0) {
            vertices = new Vertex[vertexMaxNum];
        }

        ~DirectedGraph() {
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                auto edges = vertices[i].firstIn;
                while (edges != nullptr) {
                    auto e = edges;
                    edges = edges->headFieldNext;
                    delete e;
                }
            }
            delete[]vertices;
        }

        void insert_edge(unsigned long num1, unsigned long num2, unsigned long weight = 1) {
            if (check_vertex_pair(num1, num2) && weight > 0) {
                auto edge = new Edge;
                edge->head = num1;
                edge->tail = num2;
                edge->weight = weight;

                if (vertices[num1].firstIn == nullptr) {
                    vertices[num1].firstIn = edge;
                } else {
                    auto pos = vertices[num1].firstIn;
                    auto save = pos;
                    while (pos != nullptr) {
                        if (pos->tail == num2) {
                            delete edge;
                            return;
                        }
                        save = pos;
                        pos = pos->headFieldNext;
                    }
                    save->headFieldNext = edge;
                }

                if (vertices[num2].firstOut == nullptr) {
                    vertices[num2].firstOut = edge;
                } else {
                    auto pos = vertices[num2].firstOut;
                    auto save = pos;
                    while (pos != nullptr) {
                        save = pos;
                        pos = pos->tailFieldNext;
                    }
                    save->tailFieldNext = edge;
                }

                edgeNum++;
            }
        }

        void remove_edge(unsigned long num1, unsigned long num2) {
            if (check_vertex_pair(num1, num2) && edgeNum > 0) {
                if (vertices[num2].firstOut->head == num1) {
                    vertices[num2].firstOut = vertices[num2].firstOut->tailFieldNext;
                } else {
                    auto pos = vertices[num2].firstOut;
                    auto save = pos;
                    while (pos != nullptr) {
                        if (pos->head == num1) {
                            save->tailFieldNext = pos->tailFieldNext;
                        }
                        pos = pos->tailFieldNext;
                    }
                }

                if (vertices[num1].firstIn->tail == num2) {
                    auto dE = vertices[num1].firstIn;
                    vertices[num1].firstIn = vertices[num1].firstIn->headFieldNext;
                    delete dE;
                    edgeNum--;
                } else {
                    auto pos = vertices[num1].firstIn;
                    auto save = pos;
                    while (pos != nullptr) {
                        if (pos->tail == num2) {
                            save->headFieldNext = pos->headFieldNext;
                            delete pos;
                            edgeNum--;
                            return;
                        }
                        save = pos;
                        pos = pos->headFieldNext;
                    }
                }
            }
        }

        auto vertex_neighbors(unsigned long num) {
            std::vector<Edge *> neighbors{};
            if (check_vertex(num)) {
                auto edges = vertices[num].firstIn;
                while (edges != nullptr) {
                    neighbors.push_back(edges);
                    edges = edges->headFieldNext;
                }
            }

            return neighbors;
        }

        std::optional<Vertex> get_vertex(unsigned long num) {
            if (check_vertex(num)) {
                return vertices[num];
            }
            return std::optional<Vertex>();
        }

        auto get_vertexMaxNum() {
            return vertexMaxNum;
        }

        auto get_edgeNum() {
            return edgeNum;
        }

    private:
        bool check_vertex(unsigned long num) {
            return num >= 0 && num < vertexMaxNum;
        }

        bool check_vertex_pair(unsigned long num1, unsigned long num2) {
            return check_vertex(num1) && check_vertex(num2);
        }

        Vertex *vertices;
        unsigned long vertexMaxNum;
        unsigned long edgeNum;
    };

    void ex_orthogonal_list_directed_graph_test();

}

#endif //EX_ORTHOGONAL_LIST_DIRECTED_GRAPH_H
