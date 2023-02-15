// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ADJACENCY_MULTI_LIST_GENERIC_UNDIRECTED_GRAPH_H
#define EX_ADJACENCY_MULTI_LIST_GENERIC_UNDIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::AdjacencyMultiList {

    template<typename T>
    class GenericUndirectedGraph {
    public:
        explicit GenericUndirectedGraph(unsigned long vertexMaxNum)
                : vertexMaxNum(vertexMaxNum), vertexNum(0), edgeNum(0) {
            vertices = new GenericVertex<T>[vertexMaxNum];
        }

        ~GenericUndirectedGraph() {
            for (unsigned long i = 0; i < vertexMaxNum; ++i) {
                auto edges = vertices[i].firstEdge;
                while (edges != nullptr && edges->headVertexPosition == i) {
                    auto e = edges;
                    edges = edges->headRelatedNext;
                    if (e->headVertexPosition == i) {
                        auto t = vertices[e->tailVertexPosition].firstEdge;
                        if (t == e) {
                            vertices[e->tailVertexPosition].firstEdge = nullptr;
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

        void insert_vertex(long num, T data) {
            if (check_vertex(num) == -1) {
                if (remains.empty()) {
                    if (vertexNum < vertexMaxNum) {
                        vertices[vertexNum].num = num;
                        vertices[vertexNum].data = data;
                        vertexNum++;
                    }
                } else {
                    auto f = *remains.begin();
                    vertices[f].num = num;
                    vertices[f].data = data;
                    remains.erase(f);
                    vertexNum++;
                }
            }
        }

        void insert_edge(long num1, long num2, unsigned long weight = 1) {
            long v1 = -1;
            long v2 = -1;
            for (long i = 0; i < vertexMaxNum; ++i) {
                if (vertices[i].num == num1) {
                    v1 = i;
                }
                if (vertices[i].num == num2) {
                    v2 = i;
                }
                if (v1 != -1 && v2 != -1) {
                    break;
                }
            }

            if (v1 != -1 && v2 != -1 && weight > 0) {
                auto edge = new GenericEdge<T>;
                edge->headVertexPosition = v1;
                edge->tailVertexPosition = v2;
                edge->tailData = vertices[v2].data;
                edge->weight = weight;

                if (vertices[v1].firstEdge == nullptr) {
                    vertices[v1].firstEdge = edge;
                } else {
                    auto vertexRelated = vertices[v1].firstEdge;
                    auto save = vertexRelated;
                    auto ht = true;
                    while (vertexRelated != nullptr) {
                        if (vertexRelated->tailVertexPosition == v2 || vertexRelated->headVertexPosition == v2) {
                            delete edge;
                            return;
                        }
                        save = vertexRelated;
                        if (vertexRelated->headVertexPosition == v1) {
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

                if (vertices[v2].firstEdge == nullptr) {
                    vertices[v2].firstEdge = edge;
                } else {
                    auto vertexRelated = vertices[v2].firstEdge;
                    auto save = vertexRelated;
                    auto t = true;
                    while (vertexRelated != nullptr) {
                        save = vertexRelated;
                        if (vertexRelated->tailVertexPosition == v2) {
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

        void remove_vertex(long num) {
            auto index = check_vertex(num);
            if (index != -1) {
                auto edges = vertices[index].firstEdge;
                while (edges != nullptr) {
                    auto e = edges;
                    if (e->headVertexPosition == index) {
                        edges = edges->headRelatedNext;
                        auto t = vertices[e->tailVertexPosition].firstEdge;
                        if (t == e) {
                            vertices[e->tailVertexPosition].firstEdge = t->tailRelatedNext;
                        } else {
                            auto save = t;
                            auto tn = true;
                            while (t != nullptr) {
                                if (t == e) {
                                    if (tn) {
                                        save->tailRelatedNext = t->tailRelatedNext;
                                        break;
                                    } else {
                                        save->headRelatedNext = t->headRelatedNext;
                                        break;
                                    }
                                }
                                save = t;
                                if (t->headVertexPosition != e->tailVertexPosition) {
                                    t = t->tailRelatedNext;
                                    tn = true;
                                } else {
                                    t = t->headRelatedNext;
                                    tn = false;
                                }
                            }
                        }
                        delete e;
                        edgeNum--;
                    } else if (e->tailVertexPosition == index) {
                        edges = edges->tailRelatedNext;
                        auto h = vertices[e->headVertexPosition].firstEdge;
                        auto ht = h->headVertexPosition == e->headVertexPosition;
                        if (h == e) {
                            if (ht) {
                                vertices[e->headVertexPosition].firstEdge = h->headRelatedNext;
                            } else {
                                vertices[e->headVertexPosition].firstEdge = h->tailRelatedNext;
                            }
                        } else {
                            auto save = h;
                            while (h != nullptr) {
                                if (h == e) {
                                    if (ht) {
                                        save->headRelatedNext = e->headRelatedNext;
                                        break;
                                    } else {
                                        save->tailRelatedNext = e->tailRelatedNext;
                                        break;
                                    }
                                }
                                save = h;
                                if (h->tailVertexPosition != e->headVertexPosition) {
                                    h = h->headRelatedNext;
                                    ht = true;
                                } else {
                                    h = h->tailRelatedNext;
                                    ht = false;
                                }
                            }
                        }
                        delete e;
                        edgeNum--;
                    } else {
                        break;
                    }
                }
                vertices[index].num = std::optional<long>();
                vertices[index].data = std::optional<T>();
                vertices[index].firstEdge = nullptr;
                vertexNum--;

                remains.insert(index);
            }
        }

        void remove_edge(long num1, long num2) {
            long v1 = -1;
            long v2 = -1;
            for (long i = 0; i < vertexMaxNum; ++i) {
                if (vertices[i].num == num1) {
                    v1 = i;
                }
                if (vertices[i].num == num2) {
                    v2 = i;
                }
                if (v1 != -1 && v2 != -1) {
                    break;
                }
            }

            if (v1 != -1 && v2 != -1) {
                auto vertexRelated = vertices[v1].firstEdge;
                if (vertexRelated->headVertexPosition != v1) {
                    auto tmp = v1;
                    v1 = v2;
                    v2 = tmp;
                }
                auto findIt = false;
                if (vertexRelated->tailVertexPosition == v2) {
                    vertices[v1].firstEdge = vertexRelated->headRelatedNext;
                    findIt = true;
                } else {
                    auto save = vertexRelated;
                    while (vertexRelated != nullptr) {
                        if (vertexRelated->headVertexPosition == v2) {
                            findIt = true;
                            save->headRelatedNext = vertexRelated->tailRelatedNext;
                            break;
                        } else if (vertexRelated->tailVertexPosition == v2) {
                            findIt = true;
                            save->headRelatedNext = vertexRelated->headRelatedNext;
                            break;
                        }
                        save = vertexRelated;
                        if (vertexRelated->headVertexPosition == v1) {
                            vertexRelated = vertexRelated->headRelatedNext;
                        } else {
                            vertexRelated = vertexRelated->tailRelatedNext;
                        }
                    }

                }
                if (findIt) {
                    auto t = vertices[v2].firstEdge;
                    auto ht = t->headVertexPosition == v2;
                    if (t == vertexRelated) {
                        if (ht) {
                            vertices[v2].firstEdge = t->headRelatedNext;
                        } else {
                            vertices[v2].firstEdge = t->tailRelatedNext;
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
                            if (t->headVertexPosition == v2) {
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

        std::vector<GenericEdge < T>*>

        vertex_neighbors(long num) {
            std::vector<GenericEdge<T> *> neighbors{};
            auto index = check_vertex(num);
            if (index != -1) {
                auto edges = vertices[index].firstEdge;
                while (edges != nullptr) {
                    neighbors.push_back(edges);
                    if (edges->headVertexPosition == index) {
                        edges = edges->headRelatedNext;
                    } else {
                        edges = edges->tailRelatedNext;
                    }
                }
            }

            return neighbors;
        }

        auto is_vertex_exist(long num) {
            return check_vertex(num) != -1;
        }

        auto vertex_position(long num) {
            return check_vertex(num);
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
        long check_vertex(long num) {
            for (long i = 0; i < vertexMaxNum; ++i) {
                if (vertices[i].num == num) {
                    return i;
                }
            }
            return -1;
        }

        GenericVertex <T> *vertices;
        std::set<unsigned long> remains{};
        unsigned long vertexMaxNum;
        unsigned long vertexNum;
        unsigned long edgeNum;
    };

    void generic_undirected_graph_test();

}

#endif //EX_ADJACENCY_MULTI_LIST_GENERIC_UNDIRECTED_GRAPH_H
