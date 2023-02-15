// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_CLOSED_HASH_H
#define EX_CLOSED_HASH_H

#include "core_hash.h"

namespace Ex::ClosedAddressing {

    const uint32_t SEED = 2019;

    template<typename T>
    class HashTable {
    public:
        explicit HashTable(unsigned long size)
                : size(size), dataNum(0), seed(SEED) {
            data = new HashLinkedList<T>[size];
        }

        ~HashTable() {
            for (unsigned long i = 0; i < size; ++i) {
                auto list = data[i].head;
                while (list != nullptr) {
                    auto next = list->next;
                    delete list;
                    list = next;
                }
            }
            delete[]data;
            data = nullptr;
        }

        void insert(std::string &key, T value) {

            if (key.empty()) {
                return;
            }

            uint32_t hash_result = murmurHash(key,seed);
            auto position = hash_result % size;

            auto node = new HashLinkedListNode<T>;
            node->key = key;
            node->value = value;

            if (data[position].head == nullptr) {
                data[position].head = node;
                data[position].tail = node;
            } else {
                auto temp = data[position].head;
                while (temp != nullptr) {
                    if (temp->key == key) {
                        delete node;
                        return;
                    }
                    temp = temp->next;
                }
                data[position].tail->next = node;
                data[position].tail = node;
            }
            dataNum++;
        }

        void remove(std::string &key) {

            if (key.empty() && dataNum > 0) {
                return;
            }

            uint32_t hash_result = murmurHash(key, seed);
            auto position = hash_result % size;

            auto temp = data[position].head;
            HashLinkedListNode<T> *save = nullptr;
            while (temp != nullptr) {
                if (temp->key == key) {
                    if (save == nullptr) {
                        data[position].head = temp->next;
                    } else {
                        save->next = temp->next;
                        if (data[position].tail == temp) {
                            data[position].tail = save;
                        }
                    }
                    delete temp;
                    dataNum--;
                    return;
                }
                save = temp;
                temp = temp->next;
            }

        }

        auto find(std::string &key) {

            if (key.empty()) {
                return std::optional<T>();
            }

            uint32_t hash_result = murmurHash(key, seed);
            auto position = hash_result % size;

            auto temp = data[position].head;
            while (temp != nullptr) {
                if (temp->key == key) {
                    return temp->value;
                }
                temp = temp->next;
            }

            return std::optional<T>();
        }

        auto get_size() {
            return size;
        }

        auto get_dataNum() {
            return dataNum;
        }

    private:
        HashLinkedList<T> *data;
        unsigned long size;
        unsigned long dataNum;
        uint32_t seed;
    };

    void hash_table_test();

}

#endif //EX_CLOSED_HASH_H
