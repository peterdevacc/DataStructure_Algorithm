// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef CORE_LIST_H
#define CORE_LIST_H

#include <optional>
#include <cassert>

namespace Ex {

    namespace LinkedListImpl {

        template<typename T>
        struct SingleLinkedListNode {
            SingleLinkedListNode<T> *next{nullptr};
            std::optional<T> data;
        };

        template<typename T>
        struct DoubleLinkedListNode {
            DoubleLinkedListNode<T> *next{nullptr};
            DoubleLinkedListNode<T> *prev{nullptr};
            std::optional<T> data;
        };

    }

    void test_list();

}

#endif //CORE_LIST_H
