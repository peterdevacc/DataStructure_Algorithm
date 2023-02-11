// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_LINKED_LIST_IMPL_QUEUE_H
#define EX_LINKED_LIST_IMPL_QUEUE_H

#include "core_queue.h"

namespace Ex::LinkedListImpl {

    template<typename T>
    class Queue {
    public:
        Queue() : head(nullptr), tail(nullptr), size(0) {}

        ~Queue() {
            while (head != nullptr) {
                auto temp = head;
                head = head->next;
                delete temp;
            }
        }

        void enqueue(T data) {
            auto qn = new QueueNode<T>;
            qn->data = data;
            qn->next = nullptr;
            if (head == nullptr) {
                head = qn;
                tail = qn;
            } else {
                tail->next = qn;
                tail = qn;
            }
            size++;
        }

        void dequeue() {
            if (head != nullptr) {
                auto temp = head;
                head = head->next;
                delete temp;
                if (head == nullptr) {
                    tail = nullptr;
                }
                size--;
            }
        }

        auto get_head() {
            if (size > 0) {
                return head->data;
            }
            return std::optional<T>();
        }

        auto get_tail() {
            if (size > 0) {
                return tail->data;
            }
            return std::optional<T>();
        }

        auto get_size() {
            return size;
        }

        auto is_empty() {
            return size == 0;
        }

    private:
        QueueNode<T> *head;
        QueueNode<T> *tail;
        unsigned long size;
    };

    void ex_linked_list_impl_queue_test();

}

#endif //EX_LINKED_LIST_IMPL_QUEUE_H
