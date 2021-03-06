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

        struct Vertex {
            Vertex *next{nullptr};
            unsigned long num{0};
            unsigned long weight{0};
        };

        template<typename T>
        struct GenericVertex {
            GenericVertex *next{nullptr};
            GenericVertex *edge{nullptr};
            std::optional<long> num;
            unsigned long weight{0};
            std::optional<T> data;
        };

        void adjacencyListCheckVertex(
            Vertex *vertex,
            unsigned long num,
            unsigned long weight = 1
        );

        template<typename T>
        void adjacencyListCheckVertex(
            GenericVertex<T> *vertex,
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
        struct GenericVertex {
            std::optional<long> num;
            unsigned long weight{0};
            std::optional<T> data;
        };

        void adjacencyMatrixCheckVertex(
            std::pair<unsigned long, unsigned long> vertex, 
            unsigned long data, 
            unsigned long weight = 1
        );

        template<typename T>
        void adjacencyMatrixCheckVertex(
            GenericVertex<T> vertex,
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

        struct Edge {
            Edge *headRelatedNext{nullptr};
            Edge *tailRelatedNext{nullptr};
            std::optional<unsigned long> headVertexPosition;
            std::optional<unsigned long> tailVertexPosition;
            unsigned long weight{0};
        };

        struct Vertex {
            Edge *firstEdge{nullptr};
        };

        template<typename T>
        struct GenericEdge {
            GenericEdge *headRelatedNext{nullptr};
            GenericEdge *tailRelatedNext{nullptr};
            long headVertexPosition{-1};
            long tailVertexPosition{-1};
            unsigned long weight{0};
            std::optional<T> tailData;
        };

        template<typename T>
        struct GenericVertex {
            GenericEdge<T> *firstEdge{nullptr};
            std::optional<long> num;
            std::optional<T> data;
        };

        void adjacencyMultiListUnDirectedCheckEdgeData(
            Edge *edge,
            unsigned long position,
            unsigned long weight = 1
        );

        template<typename T>
        void adjacencyMultiListUnDirectedCheckEdgeData(
            GenericEdge<T> *edge,
            T data,
            unsigned long position,
            unsigned long weight = 1
        ) {
            assert(edge->tailData == data);
            assert(edge->weight == weight);
            assert(edge->tailVertexPosition == position);
        }

        void adjacencyMultiListUnDirectedCheckEdgeField(
            Edge *edge,
            Edge *headRelatedNext,
            Edge *tailRelatedNext
        );

        template<typename T>
        void adjacencyMultiListUnDirectedCheckEdgeField(
            GenericEdge<T> *edge,
            GenericEdge<T> *headRelatedNext,
            GenericEdge<T> *tailRelatedNext
        ) {
            assert(edge->headRelatedNext == headRelatedNext);
            assert(edge->tailRelatedNext == tailRelatedNext);
        }

    }

    namespace OrthogonalList {

        struct Edge {
            Edge *headFieldNext{nullptr};
            Edge *tailFieldNext{nullptr};
            std::optional<long> head;
            std::optional<long> tail;
            unsigned long weight{0};
        };

        struct Vertex {
            Edge *firstIn{nullptr};
            Edge *firstOut{nullptr};
        };

        template<typename T>
        struct GenericEdge {
            GenericEdge *headFieldPrevious{nullptr};
            GenericEdge *headFieldNext{nullptr};
            GenericEdge *tailFieldPrevious{nullptr};
            GenericEdge *tailFieldNext{nullptr};
            std::optional<long> headNum;
            std::optional<long> tailNum;
            unsigned long weight{0};
            std::optional<T> tailData;
        };

        template<typename T>
        struct GenericVertex {
            GenericEdge<T> *firstIn{nullptr};
            GenericEdge<T> *firstOut{nullptr};
            GenericVertex *next{nullptr};
            std::optional<long> num;
            std::optional<T> data;
        };

        void orthogonalListDirectedCheckVertexField(
            std::optional<Vertex> vertex,
            Edge *in,
            Edge *out
        );

        template<typename T>
        void orthogonalListDirectedCheckVertexField(
            GenericVertex<T> *vertex,
            GenericEdge<T> *in,
            GenericEdge<T> *out
        ) {
            assert(vertex->firstIn == in);
            assert(vertex->firstOut == out);
        }

        void orthogonalListDirectedCheckEdgeField(
            Edge *edge,
            Edge *nextHead,
            Edge *nextTail
        );

        template<typename T>
        void orthogonalListDirectedCheckEdgeField(
            GenericEdge<T> *neighbor,
            GenericEdge<T> *hfp, GenericEdge<T> *hfn,
            GenericEdge<T> *tfp, GenericEdge<T> *tfn
        ) {
            assert(neighbor->headFieldPrevious == hfp);
            assert(neighbor->headFieldNext == hfn);
            assert(neighbor->tailFieldPrevious == tfp);
            assert(neighbor->tailFieldNext == tfn);
        }

        void orthogonalListDirectedCheckEdgeData(
            Edge *neighbor,
            unsigned long num,
            unsigned long weight = 1
        );

        template<typename T>
        void orthogonalListDirectedCheckEdgeData(
            GenericEdge<T> *neighbor,
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
