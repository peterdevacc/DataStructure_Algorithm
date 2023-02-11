// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_BINARY_SEARCH_TREE_H
#define EX_BINARY_SEARCH_TREE_H

#include "core_tree.h"

namespace Ex::LinkedListImpl {

    template<typename T>
    class BinarySearchTree {
    public:
        BinarySearchTree() : root(nullptr), size(0) {}

        ~BinarySearchTree() {
            std::stack<BinarySearchTreeNode<T> *> st{};
            if (root != nullptr) {
                st.push(root);
                while (!st.empty()) {
                    auto node = st.top();
                    st.pop();
                    while (node != nullptr) {
                        auto temp = node;
                        if (temp->right != nullptr) {
                            st.push(temp->right);
                        }
                        node = node->left;
                        delete temp;
                    }
                }
            }
        }

        void insert(long num, T data) {

            auto node = new BinarySearchTreeNode<T>;
            node->num = num;
            node->data = data;

            if (root == nullptr) {
                root = node;
                size++;
                return;
            }

            auto temp = root;
            auto save = temp;
            auto isLeft = true;
            while (temp != nullptr) {
                save = temp;
                if (temp->num > num) {
                    temp = temp->left;
                    isLeft = true;
                } else if (temp->num < num) {
                    temp = temp->right;
                    isLeft = false;
                } else {
                    delete node;
                    return;
                }
            }
            if (isLeft) {
                save->left = node;
            } else {
                save->right = node;
            }
            node->parent = save;
            size++;
        }

        void remove(long num) {

            if (size == 0) {
                return;
            }

            auto del = root;
            auto isLeft = true;
            while (del != nullptr && del->num != num) {
                if (del->num > num) {
                    del = del->left;
                    isLeft = true;
                } else if (del->num < num) {
                    del = del->right;
                    isLeft = false;
                }
            }

            if (del != nullptr) {
                if (del->left == nullptr && del->right == nullptr) {
                    if (del->parent != nullptr) {
                        if (isLeft) {
                            del->parent->left = nullptr;
                        } else {
                            del->parent->right = nullptr;
                        }
                    } else {
                        root = nullptr;
                    }
                    delete del;
                } else if (del->right == nullptr) {
                    if (del->parent != nullptr) {
                        del->parent->left = del->left;
                        del->left->parent = del->parent;
                    } else {
                        del->left->parent = nullptr;
                        root = del->left;
                    }
                    delete del;
                } else if (del->left == nullptr) {
                    if (del->parent != nullptr) {
                        del->parent->right = del->right;
                        del->right->parent = del->parent;
                    } else {
                        del->right->parent = nullptr;
                        root = del->right;
                    }
                    delete del;
                } else {
                    auto leftSubTree = del->left;
                    if (leftSubTree->right == nullptr) {
                        del->num = leftSubTree->num;
                        del->data = leftSubTree->data;
                        del->left = leftSubTree->left;
                        delete leftSubTree;
                    } else {
                        auto largest = leftSubTree->right;
                        while (largest->right != nullptr) {
                            largest = largest->right;
                        }
                        del->num = largest->num;
                        del->data = largest->data;
                        if (largest->left != nullptr) {
                            largest->parent->right = largest->left;
                            largest->left->parent = largest->parent;
                        } else {
                            largest->parent->right = nullptr;
                        }
                        delete largest;
                    }
                }
                size--;
            }

        }

        auto find(long num) {

            if (size > 0) {
                auto temp = root;
                while (temp != nullptr) {
                    if (temp->num > num) {
                        temp = temp->left;
                    } else if (temp->num < num) {
                        temp = temp->right;
                    } else {
                        return temp->data;
                    }
                }
            }

            return std::optional<T>();
        }

        auto get_size() {
            return size;
        }

        auto get_root() {
            return root;
        }

    private:
        BinarySearchTreeNode<T> *root;
        unsigned long size;
    };

    void ex_binary_search_tree_test();

}

#endif //EX_BINARY_SEARCH_TREE_H
