// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/3.
//

#ifndef EX_LINKED_LIST_IMPL_BINARY_MAX_HEAP_H
#define EX_LINKED_LIST_IMPL_BINARY_MAX_HEAP_H

#include "core_heap.h"

namespace Ex::LinkedListImpl {

    template<typename T>
    class BinaryMaxHeap {
    public:
        BinaryMaxHeap() : root(nullptr), lastInserted(nullptr), size(0) {}

        ~BinaryMaxHeap() {
            std::stack<HeapNode<T> *> st{};
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

            auto node = new HeapNode<T>;
            node->num = num;
            node->data = data;

            if (root == nullptr) {
                root = node;
                lastInserted = node;
                size++;
                return;
            }

            std::queue<HeapNode<T> **> nodeQueue{};
            std::stack<HeapNode<T> **> nodeStack{};
            nodeQueue.push(&root);
            nodeStack.push(&root);

            while (!nodeQueue.empty()) {
                HeapNode<T> **position = nodeQueue.front();
                if (*position != nullptr) {
                    if ((*position)->num == num) {
                        delete node;
                        return;
                    }
                    nodeQueue.push(&((*position)->left));
                    nodeQueue.push(&((*position)->right));
                    nodeStack.push(&((*position)->left));
                    nodeStack.push(&((*position)->right));
                } else {
                    while (!nodeStack.empty()) {
                        HeapNode<T> **top = nodeStack.top();
                        if (&((*top)->left) == position || &((*top)->right) == position) {
                            node->parent = *top;
                            break;
                        }
                        nodeStack.pop();
                    }

                    *position = node;
                    lastInserted = node;
                    break;
                }

                nodeQueue.pop();
            }

            fix_up(node);

            size++;

        }

        void remove(long num) {

            if (size == 0) {
                return;
            }

            if (lastInserted->num == num) {
                if (size != 1) {
                    auto lastInsertedParent = lastInserted->parent;
                    if (lastInsertedParent->left == lastInserted) {
                        lastInsertedParent->left = nullptr;
                        update_last_inserted();
                    } else {
                        lastInsertedParent->right = nullptr;
                        delete lastInserted;
                        lastInserted = lastInsertedParent->left;
                    }

                    size--;

                    return;
                } else {
                    delete lastInserted;
                    root = nullptr;
                    size = 0;

                    return;
                }
            }

            std::queue<HeapNode<T> **> delQueue{};
            delQueue.push(&root);
            HeapNode<T> * del = nullptr;
            while (!delQueue.empty()) {
                HeapNode<T> **position = delQueue.front();
                if (*position != nullptr) {
                    if ((*position)->num == num) {
                        del = *position;
                        break;
                    } else {
                        delQueue.push(&((*position)->left));
                        delQueue.push(&((*position)->right));
                    }
                }

                delQueue.pop();
            }

            del->num = root->num + 1l;
            fix_up(del);

            root->num = lastInserted->num;
            root->data = lastInserted->data;
            auto lastInsertedParent = lastInserted->parent;
            if (lastInsertedParent->left == lastInserted) {
                lastInsertedParent->left = nullptr;
                update_last_inserted();
            } else {
                lastInsertedParent->right = nullptr;
                delete lastInserted;
                lastInserted = lastInsertedParent->left;
            }

            auto position = root;
            while (position != nullptr) {
                if (position->left != nullptr && position->right != nullptr) {
                    bool isLeft = false;
                    long biggerNum = position->right->num;
                    if (position->left->num > position->right->num) {
                        isLeft = true;
                        biggerNum = position->left->num;
                    }
                    if (position->num < biggerNum) {
                        if (isLeft) {
                            swap_data(position, position->left);
                            position = position->left;
                        } else {
                            swap_data(position, position->right);
                            position = position->right;
                        }
                    } else {
                        break;
                    }
                } else if (position->left != nullptr && position->right == nullptr) {
                    if (position->num < position->left->num) {
                        swap_data(position, position->left);
                        position = position->left;
                    } else {
                        break;
                    }
                } else if (position->left == nullptr && position->right != nullptr) {
                    if (position->num < position->right->num) {
                        swap_data(position, position->right);
                        position = position->right;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }

            size--;
        }

        void remove_max() {
            remove(root->num);
        }

        auto get_size() {
            return size;
        }

        auto get_root() {
            return root;
        }

    private:
        HeapNode<T> *root;
        HeapNode<T> *lastInserted;
        unsigned long size;

        void fix_up(HeapNode<T> *node) {
            while (node->parent != nullptr) {
                if (node->num > node->parent->num) {
                    swap_data(node->parent, node);
                }

                node = node->parent;
            }
        }

        void swap_data(HeapNode<T> *a, HeapNode<T> *b) {
            auto tempNum = a->num;
            auto tempData = a->data;
            a->num = b->num;
            a->data = b->data;
            b->num = tempNum;
            b->data = tempData;
        }

        void update_last_inserted() {
            std::queue<HeapNode<T> **> nodeQueue{};
            nodeQueue.push(&root);
            HeapNode<T> **save = nullptr;
            while (!nodeQueue.empty()) {
                HeapNode<T> **position = nodeQueue.front();
                if (*position != nullptr) {
                    nodeQueue.push(&((*position)->left));
                    nodeQueue.push(&((*position)->right));
                } else {
                    delete lastInserted;
                    lastInserted = *save;
                    break;
                }

                save = position;
                nodeQueue.pop();
            }
        }
    };

    void binary_max_heap_test();

}


#endif //EX_LINKED_LIST_IMPL_BINARY_MAX_HEAP_H
