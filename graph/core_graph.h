// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef CORE_GRAPH_H
#define CORE_GRAPH_H

#include <vector>
#include <set>
#include <string>
#include <optional>
#include <cassert>

namespace Ex {

    namespace AdjacencyList {

        template<typename T>
        struct Vertex {
            Vertex *next{nullptr};
            unsigned long num{0};
            unsigned long weight{0};
            std::optional<T> data;
        };

        template<typename T>
        void check_vertex(
            Vertex<T> *vertex,
            long num, T data,
            unsigned long weight = 1
        ) {
            assert(vertex->num == num);
            assert(vertex->data == data);
            assert(vertex->weight == weight);
        }

    }

    namespace AdjacencyMatrix {

        template<typename T>
        struct Vertex {
            unsigned long num{0};
            unsigned long weight{0};
            std::optional<T> data;
        };

        template<typename T>
        void check_vertex(
            Vertex<T> vertex,
            unsigned long num,
            T data,
            unsigned long weight = 1
        ) {
            assert(vertex.num == num);
            assert(vertex.data == data);
            assert(vertex.weight == weight);
        }

    }

    namespace AdjacencyMultiList {

        template<typename T>
        struct Edge {
            Edge *headRelatedNext{nullptr};
            Edge *tailRelatedNext{nullptr};
            long headVertexPosition{-1};
            long tailVertexPosition{-1};
            unsigned long weight{0};
            std::optional<T> tailData;
        };

        template<typename T>
        struct Vertex {
            Edge<T> *firstEdge{nullptr};
            std::optional<long> num;
            std::optional<T> data;
        };

        template<typename T>
        void undirected_check_edge_data(
            Edge<T> *edge,
            T data,
            unsigned long position,
            unsigned long weight = 1
        ) {
            assert(edge->tailData == data);
            assert(edge->weight == weight);
            assert(edge->tailVertexPosition == position);
        }

        template<typename T>
        void undirected_check_edge_field(
            Edge<T> *edge,
            Edge<T> *headRelatedNext,
            Edge<T> *tailRelatedNext
        ) {
            assert(edge->headRelatedNext == headRelatedNext);
            assert(edge->tailRelatedNext == tailRelatedNext);
        }

    }

    namespace OrthogonalList {

        template<typename T>
        struct Edge {
            Edge *headFieldPrevious{nullptr};
            Edge *headFieldNext{nullptr};
            Edge *tailFieldPrevious{nullptr};
            Edge *tailFieldNext{nullptr};
            std::optional<long> headNum;
            std::optional<long> tailNum;
            unsigned long weight{0};
            std::optional<T> tailData;
        };

        template<typename T>
        struct Vertex {
            Edge<T> *firstIn{nullptr};
            Edge<T> *firstOut{nullptr};
            Vertex *next{nullptr};
            std::optional<long> num;
            std::optional<T> data;
        };

        template<typename T>
        void directed_check_vertex_field(
            Vertex<T> *vertex,
            Edge<T> *in,
            Edge<T> *out
        ) {
            assert(vertex->firstIn == in);
            assert(vertex->firstOut == out);
        }

        template<typename T>
        void directed_check_edge_field(
            Edge<T> *neighbor,
            Edge<T> *hfp, Edge<T> *hfn,
            Edge<T> *tfp, Edge<T> *tfn
        ) {
            assert(neighbor->headFieldPrevious == hfp);
            assert(neighbor->headFieldNext == hfn);
            assert(neighbor->tailFieldPrevious == tfp);
            assert(neighbor->tailFieldNext == tfn);
        }

        template<typename T>
        void directed_check_edge_data(
            Edge<T> *neighbor,
            unsigned long num,
            T data,
            unsigned long weight = 1
        ) {
            assert(neighbor->tailNum == num);
            assert(neighbor->tailData == data);
            assert(neighbor->weight == weight);
        }

    }

    void test_graph();

}

#endif //CORE_GRAPH_H
