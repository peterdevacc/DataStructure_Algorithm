// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/3.
//

#ifndef EX_ARRAY_IMPL_BINARY_MAX_HEAP_H
#define EX_ARRAY_IMPL_BINARY_MAX_HEAP_H

#include "core_heap.h"

namespace Ex::ArrayImpl {

    template<typename T>
    class BinaryMaxHeap {
    public:
        explicit BinaryMaxHeap(unsigned long capacity = 6, unsigned long increment = 3)
                : capacity(capacity), size(0), increment(increment) {
            data = new std::optional<T>[capacity];
        }

        ~BinaryMaxHeap() {
            delete[]data;
        }

        void insert(T value) {
            if (size + 1 > capacity) {
                auto *biggerArray = new std::optional<T>[capacity * increment];
                capacity = capacity * increment;
                for (unsigned long i = 0; i < capacity / increment; ++i) {
                    biggerArray[i] = data[i];
                }
                delete[]data;
                data = biggerArray;
            }

            for (unsigned long i = 0; i < size; ++i) {
                if (data[i].value() == value) {
                    return;
                }
            }

            data[size] = value;
            size++;
            fix_up(size - 1);

        }

        void remove(T value) {
            if (size == 0) {
                return;
            }

            long position = -1;
            for (long i = 0; i < size; ++i) {
                if (data[i].value() == value) {
                    position = i;
                }
            }

            if (position == -1) {
                return;
            }

            if (data[size - 1].value() == value) {
                data[size - 1].reset();
                size--;
                return;
            }

            data[position] = data[0].value() + 1;
            fix_up(position);

            data[0] = data[size - 1].value();
            data[size - 1].reset();
            size--;

            long i = 0;
            while (i < size) {
                auto index = i * 2;
                auto leftPosition = index + 1;
                auto rightPosition = index + 2;
                if (data[leftPosition].has_value() && data[rightPosition].has_value()) {
                    bool isLeft = false;
                    auto bigger = data[rightPosition].value();
                    if (data[leftPosition].value() > data[rightPosition].value()) {
                        isLeft = true;
                        bigger = data[leftPosition].value();
                    }

                    if (data[i] < bigger) {
                        if (isLeft) {
                            data[i].swap(data[leftPosition]);
                            i = leftPosition;
                        } else {
                            data[i].swap(data[rightPosition]);
                            i = rightPosition;
                        }
                    } else {
                        break;
                    }
                } else if (data[leftPosition].has_value() && !data[rightPosition].has_value()) {
                    if (data[i] < data[leftPosition].value()) {
                        data[i].swap(data[leftPosition]);
                        i = leftPosition;
                    } else {
                        break;
                    }
                } else if (!data[leftPosition].has_value() && data[rightPosition].has_value()) {
                    if (data[i] < data[rightPosition].value()) {
                        data[i].swap(data[rightPosition]);
                        i = rightPosition;
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }

        }

        void remove_max() {
            if (data != nullptr && data[0].has_value()) {
                remove(data[0].value());
            }
        }

        auto get_size() {
            return size;
        }

        auto get_vector() {
            return std::vector<std::optional<T>>(data, data + size);
        }

    private:
        std::optional<T> *data;
        unsigned long capacity;
        unsigned long size;
        unsigned long increment;

        auto get_parent_position(unsigned long position) {
            auto isLeft = (position + 1) % 2 == 0;
            unsigned long num = position / 2;
            if (num < 1) {
                return 0ul;
            } else {
                if (isLeft) {
                    return num;
                } else {
                    return num - 1;
                }
            }
        }

        void fix_up(unsigned long position) {
            while (position > 0) {
                auto parentPosition = get_parent_position(position);
                if (data[parentPosition] < data[position]) {
                    data[position].swap(data[parentPosition]);
                }
                position = parentPosition;
            }
        }
    };

    void binary_max_heap_test();

}


#endif //EX_ARRAY_IMPL_BINARY_MAX_HEAP_H
