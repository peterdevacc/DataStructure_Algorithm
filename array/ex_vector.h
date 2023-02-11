// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_PLAIN_ARRAY_H
#define EX_PLAIN_ARRAY_H

#include "core_array.h"

namespace Ex::ArrayImpl {

    template<typename T>
    class Vector {
    public:
        explicit Vector(unsigned long capacity = 3, unsigned long increment = 2)
                : capacity(capacity), size(0), increment(increment) {
            data = new std::optional<T>[capacity];
        }

        ~Vector() {
            delete[]data;
        }

        void insert(T value) {
            std::unique_lock lock(readWriteLock);

            if (size == capacity) {
                auto l = new std::optional<T>[capacity * increment];
                for (int i = 0; i < capacity; ++i) {
                    l[i] = data[i];
                }
                capacity *= increment;
                delete[]data;
                data = l;
            }

            data[size] = value;
            size++;
        }

        void remove(T value) {
            std::unique_lock lock(readWriteLock);

            for (int i = 0; i < capacity; ++i) {
                if (data[i] == value) {
                    data[i].reset();
                    size -= 1;
                    return;
                }
            }
        }

        void remove_all() {
            std::unique_lock lock(readWriteLock);

            for (int i = 0; i < capacity; ++i) {
                if (data[i].has_value()) {
                    data[i].reset();
                    size -= 1;
                }
            }
        }

        auto at(unsigned long position) {
            std::unique_lock lock(readWriteLock);

            if (position >= 0 && position < size) {
                return data[position];
            } else {
                return std::optional<T>();
            }
        }

        auto operator[](unsigned long position) {
            return at(position);
        }

        auto get_size() {
            std::unique_lock lock(readWriteLock);

            return size;
        }

        auto get_capacity() {
            std::unique_lock lock(readWriteLock);

            return capacity;
        }

        auto is_empty() {
            std::unique_lock lock(readWriteLock);

            return size == 0;
        }

        struct iterator {

            explicit iterator(std::optional<T> *data) : current(data) {}

            std::optional<T>& operator*() const {
                return *current;
            }

            std::optional<T>* operator->() const {
                return current;
            }

            bool operator==(const iterator& other) const {
                return this->current == other.current;
            }

            bool operator!=(const iterator& other) const {
                return this->current != other.current;
            }

            iterator& operator++() {
                current++;
                return *this;
            }

            iterator operator++(int) {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator& operator+=(int i) {
                current += i;
                return *this;
            }

            std::optional<T>& operator[](std::ptrdiff_t position) const {
                return current[position];
            }

        private:
            std::optional<T> *current;
        };

        iterator begin() {
            std::unique_lock lock(readWriteLock);

            return iterator(data);
        }

        iterator end() {
            std::unique_lock lock(readWriteLock);

            return iterator(data + size);
        }

    private:
        std::optional<T> *data;
        unsigned long capacity;
        unsigned long size;
        unsigned long increment;

        mutable std::shared_mutex readWriteLock;
    };

    void vector_test();

}

#endif //EX_PLAIN_ARRAY_H
