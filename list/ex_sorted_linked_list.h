// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_SORTED_LINKED_LIST_H
#define EX_SORTED_LINKED_LIST_H

#include "core_list.h"

namespace Ex::LinkedListImpl {

    template<typename T>
    class SortedLinkedList {
    public:
        SortedLinkedList() : head(nullptr), size(0) {}

        ~SortedLinkedList() {
            while (head != nullptr) {
                auto del = head;
                head = head->next;
                delete del;
            }
        }

        void insert(T data) {
            auto node = new DoubleLinkedListNode<T>;
            node->data = data;

            if (head == nullptr) {
                head = node;
                size++;
                return;
            }

            auto temp = head;
            DoubleLinkedListNode<T> *save = temp;
            DoubleLinkedListNode<T> **pos = &temp;
            while (temp != nullptr) {
                if (temp->data < data) {
                    pos = &temp->next;
                } else if (temp->data > data) {
                    break;
                } else {
                    delete node;
                    return;
                }
                save = temp;
                temp = *pos;
            }

            auto p = *pos;
            if (p == nullptr) {
                node->prev = save;
                save->next = node;
            } else if (p->prev == nullptr) {
                p->prev = node;
                node->next = p;
                head = node;
            } else {
                p->prev->next = node;
                node->prev = p->prev;
                node->next = p;
                p->prev = node;
            }

            size++;
        }

        void remove(T data) {
            if (size > 0) {
                if (head->data == data) {
                    auto del = head;
                    head = head->next;
                    head->prev = nullptr;
                    delete del;
                    size--;
                    return;
                }

                auto temp = head->next;

                while (temp != nullptr) {
                    if (temp->data != data) {
                        temp = temp->next;
                    } else {
                        break;
                    }
                }

                if (temp != nullptr) {
                    temp->prev->next = temp->next;
                    if (temp->next != nullptr) {
                        temp->next->prev = temp->prev;
                    }
                    delete temp;
                    size--;
                }
            }
        }

        auto at(unsigned long position) {
            if (position >= 0 && position < size) {
                auto temp = head;
                unsigned long counter = 0;
                while (temp != nullptr) {
                    if (counter == position) {
                        return temp->data;
                    }
                    temp = temp->next;
                    counter++;
                }
            }

            return std::optional<T>();
        }

        auto operator[](unsigned long position) {
            return at(position);
        }

        long index_of(T data) {
            if (size > 0) {
                auto temp = head;
                long index = 0;
                while (temp != nullptr) {
                    if (temp->data == data) {
                        return index;
                    }
                    temp = temp->next;
                    index++;
                }
                return -1;
            }

            return -1;
        }

        auto is_exist(T data) {
            auto temp = head;
            while (temp != nullptr) {
                if (temp->data == data) {
                    return true;
                }
                temp = temp->next;
            }
            return false;
        }

        auto get_head() {
            return head->data;
        }

        auto get_size() {
            return size;
        }

    private:
        DoubleLinkedListNode <T> *head;
        unsigned long size;
    };

    void ex_sorted_linked_list_test();

}

#endif //EX_SORTED_LINKED_LIST_H
