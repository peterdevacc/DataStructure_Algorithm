// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_COUNTER_SORT_H
#define EX_COUNTER_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    void counting_sort(std::vector<T> &data) {
        auto size = data.size();
        if (size < 2) {
            return;
        }
        auto max = data[0];
        for (int i = 1; i < size; ++i) {
            if (data[i] > max) {
                max = data[i];
            }
        }
        max += 1;
        std::vector<T> count(max);
        std::vector<T> result(size);
        for (int j = 0; j < size; ++j) {
            count[data[j]]++;
        }
        for (int k = 0; k + 1 < size; ++k) {
            count[k + 1] += count[k];
        }
        int l = size - 1;
        while (l >= 0) {
            count[data[l]] -= 1;
            auto index = count[data[l]];
            result[index] = data[l];
            l--;
        }
        for (int m = 0; m < size; ++m) {
            data[m] = result[m];
        }
    }

}

#endif //EX_COUNTER_SORT_H
