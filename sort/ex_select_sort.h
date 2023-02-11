// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_SELECT_SORT_H
#define EX_SELECT_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    void select_sort(std::vector<T> &data) {
        auto size = data.size();
        if (size < 2) {
            return;
        }
        for (auto i = 0; i < size; ++i) {
            auto min = i;
            for (auto j = i + 1; j < size; ++j) {
                if (data[j] < data[min]) {
                    min = j;
                }
            }
            swap(data[i], data[min]);
        }
    }

}

#endif //EX_SELECT_SORT_H
