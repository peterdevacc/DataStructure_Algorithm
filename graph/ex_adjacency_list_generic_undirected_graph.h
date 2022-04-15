//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ADJACENCY_LIST_GENERIC_UNDIRECTED_GRAPH_H
#define EX_ADJACENCY_LIST_GENERIC_UNDIRECTED_GRAPH_H

#include "core_graph.h"

namespace Ex::AdjacencyList {

    template<typename T>
    class GenericUnDirectedGraph {
    public:
        GenericUnDirectedGraph() : vertices(nullptr), vertexNum(0), edgeNum(0) {}

        ~GenericUnDirectedGraph() {
            while (vertices != nullptr) {
                auto edges = vertices->edge;
                while (edges != nullptr) {
                    auto e = edges;
                    edges = edges->next;
                    delete e;
                }
                auto v = vertices;
                v->edge = nullptr;
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
            if (weight <= 0) {
                return;
            }

            bool v1 = false;
            bool v2 = false;
            std::optional<T> v1Data{};
            std::optional<T> v2Data{};
            auto pos1 = vertices;
            while (pos1 != nullptr) {
                if (pos1->num == num1) {
                    v1Data = pos1->data;
                    v1 = true;
                }
                if (pos1->num == num2) {
                    v2Data = pos1->data;
                    v2 = true;
                }
                if (v1 && v2) {
                    break;
                }
                pos1 = pos1->next;
            }

            if (v1 && v2) {
                v1 = false;
                v2 = false;
                auto pos2 = vertices;
                while (pos2 != nullptr) {
                    if (num1 != num2) {
                        if (pos2->num == num1) {
                            v1 = insert_direction(pos2, num2, v2Data, weight);
                        }
                        if (pos2->num == num2) {
                            v2 = insert_direction(pos2, num1, v1Data, weight);
                        }
                    } else {
                        if (pos2->num == num1) {
                            v1 = insert_direction(pos2, num2, v2Data, weight);
                            v2 = v1;
                        }
                    }
                    pos2 = pos2->next;
                }
                if (v1 || v2) {
                    edgeNum++;
                }
            }
        }

        void remove_vertex(long num) {
            bool exist = remove_vertex_part(num);
            if (exist) {
                remove_vertex_relate_edge(num);
            }
        }

        void remove_edge(long num1, long num2) {
            auto exist = remove_direction(num1, num2);
            if (exist) {
                remove_direction(num2, num1);
                edgeNum--;
            }
        }

        auto vertex_neighbors(long num) {
            std::vector<GenericVertex < T>*> neighbors{};

            auto pos = vertices;
            while (pos != nullptr) {
                if (pos->num == num) {
                    auto edge = pos->edge;
                    while (edge != nullptr) {
                        neighbors.push_back(edge);
                        edge = edge->next;
                    }
                    break;
                }
                pos = pos->next;
            }

            return neighbors;
        }

        auto is_vertex_exist(long num) {
            bool exist = false;
            auto pos = vertices;
            while (pos != nullptr) {
                if (pos->num == num) {
                    exist = true;
                    break;
                }
                pos = pos->next;
            }
            return exist;
        }

        auto is_edge_exist(long num1, long num2) {
            auto pos = vertices;
            while (pos != nullptr) {
                if (pos->num == num1) {
                    auto edge = pos->edge;
                    while (edge != nullptr) {
                        if (edge->num == num2) {
                            return true;
                        }
                        edge = edge->next;
                    }
                }
                pos = pos->next;
            }
            return false;
        }

        auto get_vertexNum() {
            return vertexNum;
        }

        auto get_edgeNum() {
            return edgeNum;
        }

    private:
        bool insert_direction(GenericVertex <T> *gv, long num, std::optional<T> data, unsigned long weight) {
            auto vertex = new GenericVertex<T>;
            vertex->num = num;
            vertex->data = data;
            vertex->weight = weight;

            auto edges = gv->edge;
            if (edges == nullptr) {
                gv->edge = vertex;
            } else {
                auto es1 = edges;
                while (edges != nullptr) {
                    if (edges->num == num) {
                        delete vertex;
                        return false;
                    }
                    es1 = edges;
                    edges = edges->next;
                }
                es1->next = vertex;
            }

            return true;
        }

        bool remove_vertex_part(long num) {
            bool exist = false;
            auto pos = vertices;
            auto save = pos;
            while (pos != nullptr) {
                if (pos->num == num) {
                    auto dV = pos;
                    if (pos == vertices) {
                        vertices = pos->next;
                    } else {
                        save->next = pos->next;
                    }
                    auto dVE = dV->edge;
                    while (dVE != nullptr) {
                        auto dVe = dVE;
                        dVE = dVE->next;
                        delete dVe;
                    }
                    delete dV;
                    exist = true;
                    vertexNum--;
                    break;
                }
                save = pos;
                pos = pos->next;
            }

            return exist;
        }

        void remove_vertex_relate_edge(long vertex) {
            auto pos = vertices;
            while (pos != nullptr) {
                auto edge = pos->edge;
                auto save = edge;
                while (edge != nullptr) {
                    if (edge->num == vertex) {
                        auto dE = edge;
                        if (save == edge) {
                            pos->edge = edge->next;
                        } else {
                            save->next = edge->next;
                        }
                        delete dE;
                        edgeNum--;
                        break;
                    }
                    save = edge;
                    edge = edge->next;
                }
                pos = pos->next;
            }
        }

        bool remove_direction(long num1, long num2) {
            auto pos = vertices;
            while (pos != nullptr) {
                if (pos->num == num1) {
                    auto edge = pos->edge;
                    auto save = edge;
                    while (edge != nullptr) {
                        if (edge->num == num2) {
                            auto dE = edge;
                            if (save == edge) {
                                pos->edge = edge->next;
                            } else {
                                save->next = edge->next;
                            }
                            delete dE;
                            return true;
                        }
                        save = edge;
                        edge = edge->next;
                    }
                }
                pos = pos->next;
            }
            return false;
        }

        GenericVertex <T> *vertices;
        unsigned long vertexNum;
        unsigned long edgeNum;
    };

    void ex_adjacency_list_generic_undirected_graph_test();

}

#endif //EX_ADJACENCY_LIST_GENERIC_UNDIRECTED_GRAPH_H
