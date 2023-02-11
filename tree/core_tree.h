// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef CORE_TREE_H
#define CORE_TREE_H

#include <optional>
#include <stack>
#include <cassert>
#include <string>

namespace Ex {

    namespace LinkedListImpl {

        template<typename T>
        T max(T a, T b) {
            if (a > b) {
                return a;
            }
            return b;
        }

        template<typename T>
        struct AVLTreeNode {
            AVLTreeNode *left{nullptr};
            AVLTreeNode *right{nullptr};
            AVLTreeNode *parent{nullptr};
            long height{0};
            long num{0};
            std::optional<T> data;
        };

        template<typename T>
        struct BinarySearchTreeNode {
            BinarySearchTreeNode *left{nullptr};
            BinarySearchTreeNode *right{nullptr};
            BinarySearchTreeNode *parent{nullptr};
            long num{0};
            std::optional<T> data;
        };

        template<typename T>
        struct SplayTreeNode {
            SplayTreeNode *left{nullptr};
            SplayTreeNode *right{nullptr};
            SplayTreeNode *parent{nullptr};
            long num{0};
            std::optional<T> data;
        };

    }

    void test_tree();

}

#endif //CORE_TREE_H
