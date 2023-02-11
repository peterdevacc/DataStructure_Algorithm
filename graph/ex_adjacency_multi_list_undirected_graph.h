// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ADJACENCY_MULTI_LIST_UNDIRECTED_GRAPH_H
#define EX_ADJACENCY_MULTI_LIST_UNDIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::AdjacencyMultiList {

    class UnDirectedGraph {
    public:
        explicit UnDirectedGraph(unsigned long vertexMaxNum) : vertexMaxNum(vertexMaxNum), edgeNum(0) {
            vertices = new Vertex[vertexMaxNum];
        }

        ~UnDirectedGraph() {
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                auto edges = vertices[i].firstEdge;
                while (edges != nullptr && edges->headVertexPosition == i) {
                    auto e = edges;
                    edges = edges->headRelatedNext;
                    if (e->headVertexPosition == i) {
                        auto t = vertices[e->tailVertexPosition.value()].firstEdge;
                        if (t == e) {
                            vertices[e->tailVertexPosition.value()].firstEdge = nullptr;
                        } else if (t != nullptr && t->headVertexPosition == e->tailVertexPosition) {
                            auto save = t;
                            while (t != nullptr) {
                                if (t->tailVertexPosition == e->tailVertexPosition) {
                                    save->headRelatedNext = t->tailRelatedNext;
                                    break;
                                }
                                save = t;
                                t = t->headRelatedNext;
                            }
                        }
                        delete e;
                    }
                }
            }
            delete[]vertices;
        }

        void insert_edge(unsigned long num1, unsigned long num2, unsigned long weight = 1) {
            if (check_vertex_pair(num1, num2) && weight > 0) {
                auto edge = new Edge;
                edge->headVertexPosition = num1;
                edge->tailVertexPosition = num2;
                edge->weight = weight;

                if (vertices[num1].firstEdge == nullptr) {
                    vertices[num1].firstEdge = edge;
                } else {
                    auto vertexRelated = vertices[num1].firstEdge;
                    auto save = vertexRelated;
                    auto ht = true;
                    while (vertexRelated != nullptr) {
                        if (vertexRelated->tailVertexPosition == num2 || vertexRelated->headVertexPosition == num2) {
                            delete edge;
                            return;
                        }
                        save = vertexRelated;
                        if (vertexRelated->headVertexPosition == num1) {
                            vertexRelated = vertexRelated->headRelatedNext;
                            ht = true;
                        } else {
                            vertexRelated = vertexRelated->tailRelatedNext;
                            ht = false;
                        }
                    }
                    if (ht) {
                        save->headRelatedNext = edge;
                    } else {
                        save->tailRelatedNext = edge;
                    }
                }

                if (num1 == num2) {
                    edgeNum++;
                    return;
                }

                if (vertices[num2].firstEdge == nullptr) {
                    vertices[num2].firstEdge = edge;
                } else {
                    auto vertexRelated = vertices[num2].firstEdge;
                    auto save = vertexRelated;
                    auto t = true;
                    while (vertexRelated != nullptr) {
                        save = vertexRelated;
                        if (vertexRelated->tailVertexPosition == num2) {
                            vertexRelated = vertexRelated->tailRelatedNext;
                            t = true;
                        } else {
                            vertexRelated = vertexRelated->headRelatedNext;
                            t = false;
                        }
                    }
                    if (t) {
                        save->tailRelatedNext = edge;
                    } else {
                        save->headRelatedNext = edge;
                    }
                }

                edgeNum++;
            }
        }

        void remove_edge(unsigned long num1, unsigned long num2) {
            if (check_vertex_pair(num1, num2)) {
                auto vertexRelated = vertices[num1].firstEdge;
                if (vertexRelated->headVertexPosition != num1) {
                    auto tmp = num1;
                    num1 = num2;
                    num2 = tmp;
                }
                auto findIt = false;
                if (vertexRelated->tailVertexPosition == num2) {
                    vertices[num1].firstEdge = vertexRelated->headRelatedNext;
                    findIt = true;
                } else {
                    auto save = vertexRelated;
                    while (vertexRelated != nullptr) {
                        if (vertexRelated->headVertexPosition == num2) {
                            findIt = true;
                            save->headRelatedNext = vertexRelated->tailRelatedNext;
                            break;
                        } else if (vertexRelated->tailVertexPosition == num2) {
                            findIt = true;
                            save->headRelatedNext = vertexRelated->headRelatedNext;
                            break;
                        }
                        save = vertexRelated;
                        if (vertexRelated->headVertexPosition == num1) {
                            vertexRelated = vertexRelated->headRelatedNext;
                        } else {
                            vertexRelated = vertexRelated->tailRelatedNext;
                        }
                    }

                }
                if (findIt) {
                    auto t = vertices[num2].firstEdge;
                    auto ht = t->headVertexPosition == num2;
                    if (t == vertexRelated) {
                        if (ht) {
                            vertices[num2].firstEdge = t->headRelatedNext;
                        } else {
                            vertices[num2].firstEdge = t->tailRelatedNext;
                        }
                    } else {
                        auto save = t;
                        while (t != nullptr) {
                            if (t == vertexRelated) {
                                if (ht) {
                                    save->headRelatedNext = t->headRelatedNext;
                                    break;
                                } else {
                                    save->tailRelatedNext = t->tailRelatedNext;
                                    break;
                                }
                            }
                            save = t;
                            if (t->headVertexPosition == num2) {
                                t = t->headRelatedNext;
                                ht = true;
                            } else {
                                t = t->tailRelatedNext;
                                ht = false;
                            }
                        }
                    }
                    delete vertexRelated;
                    edgeNum--;
                    return;
                }
            }
        }

        auto vertex_neighbors(long num) {
            std::vector<Edge *> neighbors{};
            if (check_vertex(num)) {
                auto edges = vertices[num].firstEdge;
                while (edges != nullptr) {
                    neighbors.push_back(edges);
                    if (edges->headVertexPosition == num) {
                        edges = edges->headRelatedNext;
                    } else {
                        edges = edges->tailRelatedNext;
                    }
                }
            }
            return neighbors;
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

        Vertex *vertices;
        unsigned long vertexMaxNum;
        unsigned long edgeNum;
    };

    void undirected_graph_test();

}

#endif //EX_ADJACENCY_MULTI_LIST_UNDIRECTED_GRAPH_H
