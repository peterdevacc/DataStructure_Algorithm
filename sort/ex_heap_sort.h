// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_HEAP_SORT_H
#define EX_HEAP_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    void max_heapify(std::vector<T> &data, unsigned long begin, unsigned long end) {
        auto parent = begin;
        auto leftNode = parent * 2 + 1;
        while (leftNode <= end) {
            auto rightNode = leftNode + 1;
            if (rightNode <= end && data[leftNode] < data[rightNode]) {
                leftNode++;
            }
            if (data[parent] > data[leftNode]) {
                return;
            } else {
                swap(data[parent], data[leftNode]);
                parent = leftNode;
                leftNode = parent * 2 + 1;
            }
        }
    }

    template<typename T>
    void heap_sort(std::vector<T> &data) {
        auto size = data.size() - 1;
        if (size < 1) {
            return;
        }
        for (int i = data.size() / 2 - 1; i >= 0; i--) {
            max_heapify(data, i, size);
        }
        for (int j = size; j > 0; j--) {
            swap(data[0], data[j]);
            max_heapify(data, 0, j - 1);
        }
    }

}

#endif //EX_HEAP_SORT_H
