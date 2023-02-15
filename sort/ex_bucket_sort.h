// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_BUCKET_SORT_H
#define EX_BUCKET_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    void bucket_sort(std::vector<T> &data) {
        auto size = data.size();
        if (size < 2) {
            return;
        }
        std::vector<std::vector<T>> temp(size);
        auto max = data[0];
        for (int i = 1; i < size; ++i) {
            if (data[i] > max) {
                max = data[i];
            }
        }
        max += 1;
        for (int j = 0; j < size; ++j) {
            auto index = (data[j] * size) / max;
            temp[index].push_back(data[j]);
        }
        int k = 0;
        while (k < size) {
            auto subList = temp[k];
            if (!subList.empty()) {
                auto subListSize = subList.size();
                for (int i = 0; i < subListSize; ++i) {
                    data[k] = subList[i];
                    k++;
                }
            }
        }

    }

}

#endif //EX_BUCKET_SORT_H
