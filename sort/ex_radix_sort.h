//
// Created by Peter on 2022/4/14.
//

#ifndef EX_RADIX_SORT_H
#define EX_RADIX_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    auto radix_sort_msd(T data, unsigned int position) {
        auto sd = 10;
        while (position > 0) {
            data /= 10;
            position--;
        }
        return data % sd;
    }

    const auto RADIX_SORT_KEY_LENGTH = 10;

    template<typename T>
    void radix_sort(std::vector<T> &data) {
        auto size = data.size();
        if (size < 2) {
            return;
        }
        std::vector<T> temp(size);
        auto max = data[0];
        for (int i = 1; i < size; ++i) {
            if (data[i] > max) {
                max = data[i];
            }
        }
        auto times = 0;
        while (max >= 10) {
            times++;
            max /= 10;
        }
        for (int j = 0; j <= times; j++) {
            std::vector<int> sdList(RADIX_SORT_KEY_LENGTH);
            for (int i = 0; i < size; ++i) {
                auto msd = radix_sort_msd(data[i], j);
                sdList[msd]++;
            }
            for (int i = 0; i + 1 < RADIX_SORT_KEY_LENGTH; ++i) {
                sdList[i + 1] += sdList[i];
            }
            int l = size - 1;
            while (l >= 0) {
                auto sd = radix_sort_msd(data[l], j);
                sdList[sd] -= 1;
                auto index = sdList[sd];
                temp[index] = data[l];
                l--;
            }
            for (int m = 0; m < size; ++m) {
                data[m] = temp[m];
            }
        }
    }

}

#endif //EX_RADIX_SORT_H
