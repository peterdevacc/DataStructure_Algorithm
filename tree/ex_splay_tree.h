// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_SPLAY_TREE_H
#define EX_SPLAY_TREE_H

#include "core_tree.h"

namespace Ex::LinkedListImpl {

    template<typename T>
    class SplayTree {
    public:
        SplayTree() : root(nullptr), size(0) {}

        ~SplayTree() {
            std::stack<SplayTreeNode<T> *> st{};
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

            auto node = new SplayTreeNode<T>;
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

            root = splay(node);

            size++;
        }

        void remove(long num) {
            auto del = root;
            while (del != nullptr && del->num != num) {
                if (del->num > num) {
                    del = del->left;
                } else {
                    del = del->right;
                }
            }

            if (del != nullptr) {
                del = splay(del);
                auto leftSubTree = del->left;
                auto rightSubTree = del->right;
                delete del;
                if (leftSubTree != nullptr) {
                    leftSubTree->parent = nullptr;
                    if (leftSubTree->right != nullptr && rightSubTree != nullptr) {
                        while (leftSubTree->right != nullptr) {
                            leftSubTree = leftSubTree->right;
                        }
                        leftSubTree = splay(leftSubTree);
                    }
                    if (rightSubTree != nullptr) {
                        leftSubTree->right = rightSubTree;
                    }
                    root = leftSubTree;
                } else {
                    root = rightSubTree;
                }
                if (rightSubTree != nullptr) {
                    rightSubTree->parent = leftSubTree;
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
                        root = splay(temp);
                        return root->data;
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
        void zig_left(SplayTreeNode<T> *node) {
            auto parent = node->parent;
            auto grandparent = parent->parent;

            parent->right = node->left;
            if (node->left != nullptr) {
                node->left->parent = parent;
            }

            node->left = parent;
            node->left->parent = node;
            node->parent = grandparent;

            if (node->parent != nullptr) {
                if (node->parent->left == parent) {
                    node->parent->left = node;
                } else {
                    node->parent->right = node;
                }
            }
        }

        void zig_right(SplayTreeNode<T> *node) {
            auto parent = node->parent;
            auto grandparent = parent->parent;

            parent->left = node->right;
            if (node->right != nullptr) {
                node->right->parent = parent;
            }

            node->right = parent;
            node->right->parent = node;
            node->parent = grandparent;

            if (node->parent != nullptr) {
                if (node->parent->left == parent) {
                    node->parent->left = node;
                } else {
                    node->parent->right = node;
                }
            }
        }

        auto splay(SplayTreeNode<T> *node) {
            auto temp = node;
            while (temp->parent != nullptr) {
                auto g = temp->parent->parent;
                auto p = temp->parent;
                if (g != nullptr) {
                    if (p == g->left) {
                        if (temp == p->left) {
                            // zig-zig-right
                            zig_right(p);
                            zig_right(p->left);
                        } else {
                            // zig-zag-right
                            zig_left(temp);
                            zig_right(temp);
                        }
                    } else {
                        if (temp == p->right) {
                            // zig-zig-left
                            zig_left(p);
                            zig_left(p->right);
                        } else {
                            // zig-zag-left
                            zig_right(temp);
                            zig_left(temp);
                        }
                    }
                } else {
                    if (temp == temp->parent->left) {
                        zig_right(temp);
                    } else {
                        zig_left(temp);
                    }
                }
            }
            return node;
        }

        SplayTreeNode<T> *root;
        unsigned long size;
    };

    void splay_tree_test();

}

#endif //EX_SPLAY_TREE_H
