// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_LINKED_LIST_IMPL_STACK_H
#define EX_LINKED_LIST_IMPL_STACK_H

#include "core_stack.h"

namespace Ex::LinkedListImpl {

    template<typename T>
    class Stack {
    public:
        Stack() : head(nullptr), size(0) {}

        ~Stack() {
            while (head != nullptr) {
                auto temp = head;
                head = head->next;
                delete temp;
            }
        }

        void push(T data) {
            auto sn = new StackNode<T>;
            sn->data = data;
            sn->next = head;
            head = sn;
            size++;
        }

        auto pop() {
            if (head != nullptr) {
                auto d = head;
                head = head->next;
                auto r = std::optional<T>{d->data};
                delete d;
                size--;
                return r;
            }
            return std::optional<T>();
        }

        void remove(T data) {
            if (head->data == data) {
                auto d = head;
                head = head->next;
                delete d;
                size--;
                return;
            }

            auto temp = head->next;
            auto save = head;
            while (temp != nullptr) {
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

        void clear() {
            while (head != nullptr) {
                auto temp = head;
                head = head->next;
                delete temp;
                size--;
            }
        }

        auto get_top() {
            return head;
        }

        auto get_size() {
            return size;
        }

        auto is_empty() {
            return head == nullptr;
        }

    private:
        StackNode<T> *head;
        unsigned long size;
    };

    void stack_test();

}

#endif //EX_LINKED_LIST_IMPL_STACK_H
