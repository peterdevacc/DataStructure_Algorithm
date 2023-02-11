// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_INSERT_SORT_H
#define EX_INSERT_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    void insert_sort(std::vector<T> &data) {
        auto size = data.size();
        if (size < 2) {
            return;
        }
        for (int i = 1; i < size; ++i) {
            auto temp = data[i];
            int j;
            for (j = i; j > 0; --j) {
                if (data[j - 1] > temp) {
                    data[j] = data[j - 1];
                } else {
                    break;
                }
            }
            data[j] = temp;
        }
    }

    template<typename T>
    void binary_insert_sort(std::vector<T> &data) {
        auto size = data.size();
        if (size < 2) {
            return;
        }
        for (int i = 1; i < size; ++i) {
            auto begin = 0;
            auto end = i - 1;
            int m;
            while (begin < end) {
                m = (begin + end) / 2;
                if (data[m] < data[i]) {
                    begin = m + 1;
                } else {
                    end = m;
                }
            }

            auto temp = data[i];
            int j;
            for (j = i; j != 0 && j >= begin; --j) {
                if (data[j - 1] > temp) {
                    data[j] = data[j - 1];
                } else {
                    break;
                }
            }
            data[j] = temp;
        }
    }

}

#endif //EX_INSERT_SORT_H
