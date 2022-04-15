//
// Created by Peter on 2022/4/14.
//

#ifndef CORE_SORT_H
#define CORE_SORT_H

#include <vector>
#include <stack>
#include <algorithm>
#include <functional>
#include <random>
#include <cassert>

namespace Ex {

    template<typename T>
    void swap(T &t1, T &t2) {
        auto temp = t1;
        t1 = t2;
        t2 = temp;
    }

    template<typename T>
    void sorted_vector_verify(std::vector<T> &vi) {
        auto size = vi.size();
        for (unsigned long i = 0; i < size; ++i) {
            assert(vi[i] == i);
        }
    }

    template<typename T>
    void vector_shuffle(std::vector<T> &vi) {
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(vi.begin(), vi.end(), g);
    }

    void test_sorting();

}

#endif //CORE_SORT_H
