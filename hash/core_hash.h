// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef CORE_HASH_H
#define CORE_HASH_H

#include <optional>
#include <string>
#include <bit>
#include <cassert>

namespace Ex {

    // murmurHash3 x86 32, MurmurHash3 was written by Austin Appleby
    uint32_t murmurHash(const std::string &key, uint32_t seed);

    namespace ClosedAddressing {

        template<typename T>
        struct HashLinkedListNode {
            std::string key;
            std::optional<T> value;
            HashLinkedListNode *next{nullptr};
        };

        template<typename T>
        struct HashLinkedList {
            HashLinkedListNode<T> *head{nullptr};
            HashLinkedListNode<T> *tail{nullptr};
        };

    }

    namespace OpenAddressing {

        template<typename T>
        struct HashNode {
            std::string key;
            std::optional<T> value;
        };

    }

    void test_hash();

}

#endif //CORE_HASH_H
