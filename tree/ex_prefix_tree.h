// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/12.
//

#ifndef EX_PREFIX_TREE_H
#define EX_PREFIX_TREE_H

#include "core_tree.h"

namespace Ex::LinkedListImpl {

    class PrefixTree {
    public:
        explicit PrefixTree(std::string_view range) {
            auto size = range.size();
            prefixRange = new char[size];
            prefixRangeSize = size;
            for (unsigned long i = 0; i < size; ++i) {
                prefixRange[i] = range[i];
            }

            root = new PrefixTreeNode;
        }

        ~PrefixTree() {
            std::stack<PrefixTreeNode *> st{};
            st.push(root);
            while (!st.empty()) {
                auto node = st.top();
                st.pop();
                auto temp = node;
                for (const auto &item: temp->prefix) {
                    st.emplace(item);
                }
                delete temp;
            }

            delete[]prefixRange;
        }

        void insert(std::string_view data) {
            bool isValid = check_data(data);
            if (isValid) {
                std::stack<PrefixTreeNode *> st{};
                st.push(root);

                unsigned long position = 0;
                while (position < data.size()) {
                    auto top = st.top();
                    st.pop();
                    if (top->prefix.empty()) {
                        while (position < data.size()) {
                            auto node = new PrefixTreeNode;
                            node->data = data[position];
                            top->prefix.push_back(node);
                            top = top->prefix.front();

                            position++;
                        }

                        return;
                    }

                    bool isExisted = false;
                    for (const auto &current: top->prefix) {
                        if (current->data == data[position]) {
                            isExisted = true;
                            st.push(current);
                            position++;
                            break;
                        }
                    }

                    if (!isExisted) {
                        auto node = new PrefixTreeNode;
                        node->data = data[position];
                        top->prefix.push_back(node);
                        position++;

                        auto temp = node;
                        while (position < data.size()) {
                            auto otherNode = new PrefixTreeNode;
                            otherNode->data = data[position];
                            temp->prefix.push_back(otherNode);
                            temp = otherNode;

                            position++;
                        }

                        return;
                    }
                }
            }
        }

        void remove(std::string_view data) {
            bool isValid = check_data(data);
            if (isValid) {
                auto temp = root;
                std::stack<PrefixTreeNode *> st{};
                st.push(temp);

                unsigned long position = 0;
                while (!st.empty()) {
                    auto node = st.top();
                    st.pop();

                    bool isExisted = false;
                    PrefixTreeNode * delParent = nullptr;
                    PrefixTreeNode * delNode = nullptr;
                    for (const auto &current: node->prefix) {
                        if (current->data == data[position]) {
                            st.push(current);
                            position++;
                            isExisted = true;

                            delNode = current;
                            delParent = node;

                            break;
                        }
                    }

                    if (isExisted) {
                        if (position == data.size()) {
                            if (!delNode->prefix.empty()) {
                                return;
                            } else {
                                delParent->prefix.remove(delNode);
                                delete delNode;

                                return;
                            }
                        }
                    } else {
                        return;
                    }

                }
            }
        }

        bool is_existed(std::string_view data) {
            bool isValid = check_data(data);
            if (isValid) {
                auto temp = root;
                std::stack<PrefixTreeNode *> st{};
                st.push(temp);

                unsigned long position = 0;
                while (!st.empty()) {
                    auto node = st.top();
                    st.pop();

                    bool isExisted = false;
                    for (const auto &current: node->prefix) {
                        if (current->data == data[position]) {
                            st.push(current);
                            position++;
                            isExisted = true;

                            break;
                        }
                    }

                    if (isExisted) {
                        if (position == data.size()) {
                            return true;
                        }
                    } else {
                        return false;
                    }
                }
            }

            return false;
        }

        auto get_root() {
            return root;
        }

    private:
        bool check_data(std::string_view data) const {
            bool isValid = false;
            for (const auto &c: data) {
                isValid = false;
                for (unsigned long i = 0; i < prefixRangeSize; ++i) {
                    if (c == data[i]) {
                        isValid = true;
                        break;
                    }
                }
            }

            return isValid;
        }

        PrefixTreeNode *root;
        char *prefixRange{};
        unsigned long prefixRangeSize;
    };

    void prefix_tree_test();

}

#endif //EX_PREFIX_TREE_H
