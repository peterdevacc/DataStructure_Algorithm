// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_SINGLE_LINKED_LIST_H
#define EX_SINGLE_LINKED_LIST_H

#include "core_list.h"

namespace Ex::LinkedListImpl {

    template<typename T>
    class SingleLinkedList {
    public:
        SingleLinkedList() : head{nullptr}, tail{nullptr}, size(0) {}

        ~SingleLinkedList() {
            while (head != nullptr) {
                auto del = head;
                head = head->next;
                delete del;
            }
        }

        void insert(T data) {
            auto node = new SingleLinkedListNode<T>;
            node->data = data;

            if (head == nullptr) {
                head = node;
                tail = node;
                size++;
                return;
            }

            tail->next = node;
            tail = node;
            size++;
        }

        void remove(T data) {

            if (size == 0) {
                return;
            }

            if (head->data == data) {
                if (head->next == nullptr) {
                    delete head;
                    head = nullptr;
                    tail = nullptr;
                } else {
                    auto del = head;
                    head = head->next;
                    delete del;
                }
                size--;
                return;
            }

            if (tail->data == data) {
                auto temp = head;
                auto save = temp;
                while (temp != tail) {
                    save = temp;
                    temp = temp->next;
                }
                auto del = tail;
                tail = save;
                tail->next = nullptr;
                delete del;
                size--;
                if (size == 1) {
                    head = tail;
                }
                return;
            }

            auto temp = head;
            auto save = temp;
            while (temp != tail) {
                if (temp->data == data) {
                    save->next = temp->next;
                    delete temp;
                    size--;
                    return;
                }
                save = temp;
                temp = temp->next;
            }

        }

        void remove_head() {
            auto data = head->data.value();
            remove(data);
        }

        void remove_tail() {
            auto data = tail->data.value();
            remove(data);
        }

        auto get_head() {
            if (size == 0) {
                return std::optional<T>();
            }
            return head->data;
        }

        auto get_tail() {
            if (size == 0) {
                return std::optional<T>();
            }
            return tail->data;
        }

        auto at(unsigned long position) {
            if (position < size) {
                if (position == 0) {
                    return get_head();
                }

                if (position == size - 1) {
                    return get_tail();
                }

                unsigned long counter = 1;
                auto temp = head->next;
                while (temp != tail) {
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

        auto is_exist(T data) {
            if (size > 0) {
                if (head->data == data) {
                    return true;
                }

                if (tail->data == data) {
                    return true;
                }

                auto temp = head->next;
                while (temp != tail) {
                    if (temp->data == data) {
                        return true;
                    }
                    temp = temp->next;
                }

                return false;
            }

            return false;
        }

        long index_of(T data) {
            if (size > 0) {
                long index = 1;

                if (head->data == data) {
                    return 0;
                }

                if (tail->data == data) {
                    return size - 1;
                }

                auto temp = head->next;
                while (temp != tail) {
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

        auto get_size() {
            return size;
        }

    private:
        SingleLinkedListNode<T> *head;
        SingleLinkedListNode<T> *tail;
        unsigned long size;
    };

    void single_linked_list_test();

}

#endif //EX_SINGLE_LINKED_LIST_H
