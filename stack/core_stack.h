// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

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
