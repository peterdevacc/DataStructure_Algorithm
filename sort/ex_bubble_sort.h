// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_BUBBLE_SORT_H
#define EX_BUBBLE_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    void bubble_sort(std::vector<T> &data) {
        auto size = data.size();
        if (size < 2) {
            return;
        }
        for (auto i = 0; i < size; ++i) {
            for (auto j = 0; j < size - 1 - i; ++j) {
                if (data[j] > data[j + 1]) {
                    swap(data[j + 1], data[j]);
                }
            }
        }
    }

}

#endif //EX_BUBBLE_SORT_H
