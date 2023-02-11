// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ORTHOGONAL_LIST_GENERIC_DIRECTED_GRAPH_H
#define EX_ORTHOGONAL_LIST_GENERIC_DIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::OrthogonalList {

    template<typename T>
    class GenericDirectedGraph {
    public:
        GenericDirectedGraph() : vertices(nullptr), vertexNum(0), edgeNum(0) {}

        ~GenericDirectedGraph() {
            while (vertices != nullptr) {
                auto v = vertices;
                auto edges = v->firstIn;
                while (edges != nullptr) {
                    auto e = edges;
                    edges = edges->headFieldNext;
                    delete e;
                }
                vertices = vertices->next;
                delete v;
            }
        }

        void insert_vertex(long num, T data) {
            auto vertex = new GenericVertex<T>;
            vertex->num = num;
            vertex->data = data;

            if (vertices == nullptr) {
                vertices = vertex;
            } else {
                auto pos = vertices;
                auto save = pos;
                while (pos != nullptr) {
                    if (pos->num == num) {
                        delete vertex;
                        return;
                    }
                    save = pos;
                    pos = pos->next;
                }
                save->next = vertex;
            }

            vertexNum++;
        }

        void insert_edge(long num1, long num2, unsigned long weight = 1) {
            auto vp = check_vertex_pair(num1, num2);
            GenericVertex<T> *v1 = vp.first;
            GenericVertex<T> *v2 = vp.second;

            if (v1 != nullptr && v2 != nullptr) {
                auto edge = new GenericEdge<T>;
                edge->headNum = num1;
                edge->tailNum = num2;
                edge->weight = weight;
                edge->tailData = v2->data;

                if (v1->firstIn == nullptr) {
                    v1->firstIn = edge;
                } else {
                    auto pos = v1->firstIn;
                    auto save = pos;
                    while (pos != nullptr) {
                        if (pos->tailNum == num2) {
                            delete edge;
                            return;
                        }
                        save = pos;
                        pos = pos->headFieldNext;
                    }
                    save->headFieldNext = edge;
                    edge->headFieldPrevious = save;
                }

                if (v2->firstOut == nullptr) {
                    v2->firstOut = edge;
                } else {
                    auto pos = v2->firstOut;
                    auto save = pos;
                    while (pos != nullptr) {
                        save = pos;
                        pos = pos->tailFieldNext;
                    }
                    save->tailFieldNext = edge;
                    edge->tailFieldPrevious = save;
                }

                edgeNum++;
            }
        }

        void remove_vertex(long num) {
            auto pos = vertices;
            auto save = pos;
            while (pos != nullptr) {
                if (pos->num == num) {
                    auto in = pos->firstIn;
                    while (in != nullptr) {
                        auto dIn = in;
                        if (dIn->tailFieldPrevious != nullptr) {
                            dIn->tailFieldPrevious->tailFieldNext = dIn->tailFieldNext;
                            if (dIn->tailFieldNext != nullptr) {
                                dIn->tailFieldNext->tailFieldPrevious = dIn->tailFieldPrevious;
                            }
                        } else {
                            auto t = get_vertex(dIn->tailNum.value());
                            if (t->firstOut == dIn) {
                                t->firstOut = dIn->tailFieldNext;
                                if (t->firstOut != nullptr) {
                                    t->firstOut->tailFieldPrevious = nullptr;
                                }
                            }
                        }

                        in = in->headFieldNext;
                        delete dIn;
                        edgeNum--;
                    }

                    auto out = pos->firstOut;
                    while (out != nullptr) {
                        auto dOut = out;
                        if (dOut->headFieldPrevious != nullptr) {
                            dOut->headFieldPrevious->headFieldNext = dOut->headFieldNext;
                            if (dOut->headFieldNext != nullptr) {
                                dOut->headFieldNext->headFieldPrevious = dOut->headFieldPrevious;
                            }
                        } else {
                            auto h = get_vertex(dOut->headNum.value());
                            if (h->firstIn == dOut) {
                                h->firstIn = dOut->headFieldNext;
                                if (h->firstIn != nullptr) {
                                    h->firstIn->headFieldPrevious = nullptr;
                                }
                            }
                        }

                        out = out->tailFieldNext;
                        delete dOut;
                        edgeNum--;
                    }

                    if (save == vertices) {
                        vertices = vertices->next;
                    } else {
                        save->next = pos->next;
                    }
                    delete pos;
                    vertexNum--;
                    break;
                }
                save = pos;
                pos = pos->next;
            }
        }

        void remove_edge(long num1, long num2) {
            auto vp = check_vertex_pair(num1, num2);
            GenericVertex<T> *v1 = vp.first;
            GenericVertex<T> *v2 = vp.second;

            if (v1 != nullptr && v2 != nullptr) {
                auto in = v1->firstIn;
                while (in != nullptr) {
                    if (in->tailNum == num2) {
                        if (in->tailFieldPrevious != nullptr) {
                            in->tailFieldPrevious->tailFieldNext = in->tailFieldNext;
                            if (in->tailFieldNext != nullptr) {
                                in->tailFieldNext->tailFieldPrevious = in->tailFieldPrevious;
                            }
                        } else {
                            if (v2->firstOut == in) {
                                v2->firstOut = in->tailFieldNext;
                                if (v2->firstOut != nullptr) {
                                    v2->firstOut->tailFieldPrevious = nullptr;
                                }
                            }
                        }

                        if (in->headFieldPrevious != nullptr) {
                            in->headFieldPrevious->headFieldNext = in->headFieldNext;
                            if (in->headFieldNext != nullptr) {
                                in->headFieldNext->headFieldPrevious = in->headFieldPrevious;
                            }
                        } else {
                            if (v1->firstIn == in) {
                                v1->firstIn = in->headFieldNext;
                                if (v1->firstIn != nullptr) {
                                    v1->firstIn->headFieldPrevious = nullptr;
                                }
                            }
                        }

                        delete in;
                        edgeNum--;
                        return;
                    }
                    in = in->headFieldNext;
                }
            }
        }

        GenericVertex<T> *get_vertex(long num) {
            auto pos = vertices;
            while (pos != nullptr) {
                if (pos->num == num) {
                    return pos;
                }
                pos = pos->next;
            }
            return nullptr;
        }

        auto vertex_neighbors(long num) {
            std::vector<GenericEdge<T> *> neighbors{};
            auto vertex = get_vertex(num);
            if (vertex != nullptr) {
                auto edges = vertex->firstIn;
                while (edges != nullptr) {
                    neighbors.push_back(edges);
                    edges = edges->headFieldNext;
                }
            }

            return neighbors;
        }

        auto get_vertexNum() {
            return vertexNum;
        }

        auto get_edgeNum() {
            return edgeNum;
        }

    private:
        std::pair<GenericVertex<T> *, GenericVertex<T> *> check_vertex_pair(long num1, long num2) {
            auto vp = std::make_pair<GenericVertex<T> *, GenericVertex<T> *>(nullptr, nullptr);
            GenericVertex<T> *v1 = nullptr;
            GenericVertex<T> *v2 = nullptr;
            auto v = vertices;
            while (v != nullptr) {
                if (v->num == num1) {
                    v1 = v;
                }
                if (v->num == num2) {
                    v2 = v;
                }
                if (v1 != nullptr && v2 != nullptr) {
                    break;
                }
                v = v->next;
            }
            vp.first = v1;
            vp.second = v2;
            return vp;
        }

        GenericVertex<T> *vertices;
        unsigned long vertexNum;
        unsigned long edgeNum;
    };

    void generic_directed_graph_test();

}

#endif //EX_ORTHOGONAL_LIST_GENERIC_DIRECTED_GRAPH_H
