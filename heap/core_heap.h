// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/3.
//

#ifndef CORE_HEAP_H
#define CORE_HEAP_H

#include <optional>
#include <stack>
#include <cassert>
#include <queue>
#include <string>
#include <vector>
#include <iostream>

namespace Ex {

    namespace LinkedListImpl {

        template<typename T>
        struct HeapNode {
            HeapNode *left{nullptr};
            HeapNode *right{nullptr};
            HeapNode *parent{nullptr};
            long num{0};
            std::optional<T> data;
        };

    }

    void test_heap();

}

#endif //CORE_HEAP_H
