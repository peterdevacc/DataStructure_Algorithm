//
// Created by Peter on 2022/4/14.
//

#ifndef EX_MERGE_SORT_H
#define EX_MERGE_SORT_H

#include "core_sort.h"

namespace Ex {

    template<typename T>
    void merge_sort_merger(std::vector<T> &data, unsigned long begin, unsigned long middle, unsigned long end) {
        std::vector<T> temp(end + 1);
        auto i = begin;
        auto j = middle + 1;
        auto k = begin;
        while (i <= middle && j <= end) {
            if (data[i] < data[j]) {
                temp[k++] = data[i++];
            } else {
                temp[k++] = data[j++];
            }
        }
        for (; i <= middle; i++) {
            temp[k++] = data[i];
        }
        for (; j <= end; j++) {
            temp[k++] = data[j];
        }
        for (i = begin; i <= end; i++) {
            data[i] = temp[i];
        }
    }

    template<typename T>
    void merge_sort_divider(std::vector<T> &data, unsigned long begin, unsigned long end) {
        if (begin < end) {
            auto middle = (begin + end) / 2;
            merge_sort_divider(data, begin, middle);
            merge_sort_divider(data, middle + 1, end);
            merge_sort_merger(data, begin, middle, end);
        }
    }

    template<typename T>
    void merge_sort_recursive(std::vector<T> &data) {
        auto size = data.size() - 1;
        if (size < 1) {
            return;
        }
        auto middle = size / 2;
        merge_sort_divider(data, 0, middle);
        merge_sort_divider(data, middle + 1, size);
        merge_sort_merger(data, 0, middle, size);
    }

    template<typename T>
    void merge_sort_iterative(std::vector<T> &data) {
        auto size = data.size();
        if (size < 2) {
            return;
        }

        int i = 2;
        while (i <= size) {
            auto times = size / i;
            int j = 0;
            bool hasRemain = false;
            int middle = 0;
            if (size >= i && size % i != 0) {
                times++;
                hasRemain = true;
            }
            while (times > 0) {
                auto begin = j;
                auto end = j + i - 1;
                middle = (begin + end) / 2;
                if (times == 1 && hasRemain) {
                    end = size - 1;
                    middle = begin - 1;
                    begin -= i;
                }
                merge_sort_merger(data, begin, middle, end);
                j += i;
                times--;
            }
            i *= 2;
        }


    }

}

#endif //EX_MERGE_SORT_H
