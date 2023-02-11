// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ARRAY_IMPL_STACK_H
#define EX_ARRAY_IMPL_STACK_H

#include "core_stack.h"

namespace Ex::ArrayImpl {

    template<typename T>
    class Stack {
    public:
        explicit Stack(unsigned long capacity)
                : top(0), size(0), capacity(capacity) {
            data = new std::optional<T>[capacity];
        }

        ~Stack() {
            delete[]data;
        }

        void push(T value) {
            if (size < capacity) {
                data[top] = value;
                top++;
                size++;
            }
        }

        auto pop() {
            if (size > 0) {
                auto value = data[top - 1];
                data[top - 1] = std::optional<T>();
                top--;
                size--;
                return value;
            }
            return std::optional<T>();
        }

        auto get_top() {
            if (size > 0) {
                return data[top - 1];
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
        std::optional<T> *data;
        int top;
        unsigned long size;
        unsigned long capacity;
    };

    void stack_test();

}

#endif //EX_ARRAY_IMPL_STACK_H
