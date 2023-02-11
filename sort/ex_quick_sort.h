// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#ifndef EX_QUICK_SORT_H
#define EX_QUICK_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    unsigned long quick_sort_partition(std::vector<T> &data, unsigned long begin, unsigned long end) {
        auto pivot = data[begin];
        auto i = begin;
        auto j = end;
        while (i < j) {
            while (i < data.size() && data[i] <= pivot) {
                i++;
            }
            while (data[j] > pivot) {
                j--;
            }
            if (i < j) {
                swap(data[i], data[j]);
            }
        }
        swap(data[j], data[begin]);
        return j;
    }

    template<typename T>
    void quick_sort_recursive_helper(std::vector<T> &data, unsigned long begin, unsigned long end) {
        if (begin < end) {
            auto p = quick_sort_partition(data, begin, end);
            quick_sort_recursive_helper(data, begin, p);
            quick_sort_recursive_helper(data, p + 1, end);
        }
    }

    template<typename T>
    void quick_sort_recursive(std::vector<T> &data) {
        auto end = data.size() - 1;
        if (end < 1) {
            return;
        }
        quick_sort_recursive_helper(data, 0, end);
    }

    template<typename T>
    void quick_sort_iterative(std::vector<T> &data) {
        auto begin = 0;
        auto end = data.size() - 1;

        if (end < 1) {
            return;
        }

        std::stack<T> si{};
        si.push(begin);
        si.push(end);

        while (!si.empty()) {
            end = si.top();
            si.pop();
            begin = si.top();
            si.pop();

            if (begin < end) {
                auto p = quick_sort_partition(data, begin, end);

                si.push(begin);
                si.push(p);

                si.push(p + 1);
                si.push(end);
            }

        }
    }

}

#endif //EX_QUICK_SORT_H
