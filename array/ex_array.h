//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ARRAY_H
#define EX_ARRAY_H

#include "core_array.h"

namespace Ex::ArrayImpl {

    template<typename T>
    class Array {
    public:
        explicit Array(unsigned long capacity = 3, unsigned long increment = 3)
                : capacity(capacity), size(0), increment(increment) {
            data = new std::optional<T>[capacity];
        }

        ~Array() {
            delete[]data;
        }

        int insert(T value) {
            if (size == capacity) {
                auto l = new std::optional<T>[capacity + increment];
                for (int i = 0; i < capacity; ++i) {
                    l[i] = data[i];
                }
                capacity += increment;
                delete[]data;
                data = l;
                increment *= 2;
            }

            for (int i = 0; i < capacity; ++i) {
                if (!data[i].has_value()) {
                    data[i] = value;
                    size += 1;
                    return 1;
                }
            }
            return -1;
        }

        void remove(T value) {
            for (int i = 0; i < capacity; ++i) {
                if (data[i] == value) {
                    data[i].reset();
                    size -= 1;
                    return;
                }
            }
        }

        void remove_all() {
            for (int i = 0; i < capacity; ++i) {
                if (data[i].has_value()) {
                    data[i].reset();
                    size -= 1;
                }
            }
        }

        auto at(unsigned long position) {
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
            return size;
        }

        auto get_capacity() {
            return capacity;
        }

        auto is_empty() {
            return size == 0;
        }

    private:
        std::optional<T> *data;
        unsigned long capacity;
        unsigned long size;
        unsigned long increment;
    };

    void ex_array_test();

}

#endif //EX_ARRAY_H
