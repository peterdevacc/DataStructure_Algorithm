// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_AVL_TREE_H
#define EX_AVL_TREE_H

#include "core_tree.h"

namespace Ex::LinkedListImpl {

    template<typename T>
    class AVLTree {
    public:
        AVLTree() : root(nullptr), size(0) {}

        ~AVLTree() {
            std::stack<AVLTreeNode<T> *> st{};
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

            auto node = new AVLTreeNode<T>;
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

            re_balance(node);
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
                AVLTreeNode<T> *reb = nullptr;
                if (del->left == nullptr && del->right == nullptr) {
                    reb = del->parent;
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
                    reb = del->parent;
                    delete del;
                } else if (del->left == nullptr) {
                    if (del->parent != nullptr) {
                        del->parent->right = del->right;
                        del->right->parent = del->parent;
                    } else {
                        del->right->parent = nullptr;
                        root = del->right;
                    }
                    reb = del->parent;
                    delete del;
                } else {
                    auto leftSubTree = del->left;
                    if (leftSubTree->right == nullptr) {
                        del->num = leftSubTree->num;
                        del->data = leftSubTree->data;
                        del->left = leftSubTree->left;
                        reb = leftSubTree->parent;
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
                        reb = largest->parent;
                        delete largest;
                    }
                }

                re_balance(reb);
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
        long node_height(AVLTreeNode<T> *node) {
            if (node != nullptr) {
                return node->height;
            }
            return -1;
        }

        auto left_rotation(AVLTreeNode<T> *node) {
            auto temp = node->right;

            temp->parent = node->parent;
            if (temp->left != nullptr) {
                temp->left->parent = node;
            }

            node->right = temp->left;
            node->parent = temp;

            temp->left = node;

            node->height = max(node_height(node->left), node_height(node->right)) + 1;
            temp->height = max(node_height(temp->right), node->height) + 1;

            return temp;
        }

        auto right_rotation(AVLTreeNode<T> *node) {
            auto temp = node->left;

            temp->parent = node->parent;
            if (temp->right != nullptr) {
                temp->right->parent = node;
            }

            node->left = temp->right;
            node->parent = temp;

            temp->right = node;

            node->height = max(node_height(node->left), node_height(node->right)) + 1;
            temp->height = max(node_height(temp->left), node->height) + 1;

            return temp;
        }

        auto left_right_rotation(AVLTreeNode<T> *node) {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }

        auto right_left_rotation(AVLTreeNode<T> *node) {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }

        auto re_balance_node(AVLTreeNode<T> *node) {
            node->height = max(node_height(node->left), node_height(node->right)) + 1;

            if (node_height(node->left) - node_height(node->right) == 2) {
                if (node_height(node->left->right) - node_height(node->left->left) == 1) {
                    node = left_right_rotation(node);
                } else {
                    node = right_rotation(node);
                }
            } else if (node_height(node->right) - node_height(node->left) == 2) {
                if (node_height(node->right->left) - node_height(node->right->right) == 1) {
                    node = right_left_rotation(node);
                } else {
                    node = left_rotation(node);
                }
            }

            return node;
        }

        void re_balance(AVLTreeNode<T> *node) {
            while (node != nullptr) {
                auto pre = node;
                node = re_balance_node(node);
                auto parent = node->parent;
                if (parent != nullptr) {
                    if (parent->left == pre) {
                        parent->left = node;
                    } else {
                        parent->right = node;
                    }
                } else {
                    root = node;
                }

                node = node->parent;
            }
        }

        AVLTreeNode<T> *root;
        unsigned long size;
    };

    void avl_tree_test();

}

#endif //EX_AVL_TREE_H
