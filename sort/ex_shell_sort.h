// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_SHELL_SORT_H
#define EX_SHELL_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    void shell_sort(std::vector<T> &data) {
        auto size = data.size();
        if (size < 2) {
            return;
        }
        int h = 1;
        while (h < size / 3) {
            h = 3 * h + 1;
        }
        while (h >= 1) {
            for (int i = h; i < size; ++i) {
                for (int j = i;
                     j >= h && data[j] <= data[j - h];
                     j -= h) {
                    swap(data[j - h], data[j]);
                }
            }
            h = h / 3;
        }
    }

}

#endif //EX_SHELL_SORT_H
