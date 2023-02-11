// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_OPEN_ADDRESSING_H
#define EX_OPEN_ADDRESSING_H

#include "core_hash.h"

namespace Ex::OpenAddressing {

    const uint32_t SEED = 2019;

    template<typename T>
    class HashTable {
    public:
        explicit HashTable(unsigned long capacity)
                : capacity(capacity), size(0), seed(SEED) {
            data = new HashNode<T>[capacity];
        }

        ~HashTable() {
            delete[]data;
        }

        bool insert(std::string &key, T value) {

            if (key.empty() || size == capacity) {
                return false;
            }

            uint32_t hash_result = murmurHash(key, seed);
            auto position = hash_result % capacity;

            auto i = position;
            while (i < capacity - 1) {
                if (data[i].key.empty()) {
                    data[i].key = key;
                    data[i].value = value;
                    size++;
                    return true;
                }
                i++;
            }

            i = 0;
            while (i < position) {
                if (data[i].key.empty()) {
                    data[i].key = key;
                    data[i].value = value;
                    size++;
                    return true;
                }
                i++;
            }

            return false;
        }

        void remove(std::string &key) {

            if (key.empty() && size > 0) {
                return;
            }

            uint32_t hash_result = murmurHash(key, seed);
            auto position = hash_result % size;

            auto up = position;
            while (up < capacity - 1) {
                if (data[up].key == key) {
                    data[up].key = "";
                    data[up].value = std::optional<T>();
                    size--;
                    return;
                }
                up++;
            }

            up = 0;
            while (up < position) {
                if (data[up].key == key) {
                    data[up].key = "";
                    data[up].value = std::optional<T>();
                    size--;
                    return;
                }
                up++;
            }
        }

        auto find(std::string &key) {

            if (key.empty()) {
                return std::optional<T>();
            }

            uint32_t hash_result = murmurHash(key, seed);
            auto position = hash_result % capacity;

            auto up = position;
            while (up < capacity - 1) {
                if (data[up].key == key) {
                    return data[up].value;
                }
                up++;
            }

            up = 0;
            while (up < position) {
                if (data[up].key == key) {
                    return data[up].value;
                }
                up++;
            }

            return std::optional<T>();
        }

        auto get_size() {
            return size;
        }

        auto get_capacity() {
            return capacity;
        }

    private:
        HashNode<T> *data;
        unsigned long capacity;
        unsigned long size;
        uint32_t seed;
    };

    void hash_table_test();

}

#endif //EX_OPEN_ADDRESSING_H
