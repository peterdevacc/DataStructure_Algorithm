//
// Created by Peter on 2022/4/14.
//

#ifndef CORE_STACK_H
#define CORE_STACK_H

#include <optional>
#include <cassert>

namespace Ex {

    namespace LinkedListImpl {

        template<typename T>
        struct StackNode {
            std::optional<T> data;
            StackNode<T> *next;
        };

    }

    void test_stack();

}

#endif //CORE_STACK_H
