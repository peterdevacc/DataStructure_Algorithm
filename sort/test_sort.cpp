// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_bubble_sort.h"
#include "ex_bucket_sort.h"
#include "ex_counting_sort.h"
#include "ex_heap_sort.h"
#include "ex_insert_sort.h"
#include "ex_merge_sort.h"
#include "ex_quick_sort.h"
#include "ex_radix_sort.h"
#include "ex_select_sort.h"
#include "ex_shell_sort.h"

const unsigned int times = 100;
const unsigned int vectorSize = 500;

void sorting_test_core(unsigned int size);

void Ex::test_sorting() {
    for (unsigned int i = 0; i < times; ++i) {
        sorting_test_core(vectorSize);
    }
}

void sorting_test_core(unsigned int size) {
    std::vector<int> vi{0};
    for (int j = 1; j < size; ++j) {
        vi.push_back(j);
    }

    std::vector<std::function<void(std::vector<int> &)>> vf{
            Ex::bubble_sort<int>,
            Ex::select_sort<int>,
            Ex::insert_sort<int>,
            Ex::binary_insert_sort<int>,
            Ex::shell_sort<int>,
            Ex::merge_sort_recursive<int>,
            Ex::merge_sort_iterative<int>,
            Ex::quick_sort_recursive<int>,
            Ex::quick_sort_iterative<int>,
            Ex::heap_sort<int>,
            Ex::bucket_sort<int>,
            Ex::counting_sort<int>,
            Ex::radix_sort<int>
    };

    std::for_each(vf.begin(), vf.end(), [&vi](std::function<void(std::vector<int> &)> &sorting) {
        Ex::vector_shuffle(vi);
        sorting(vi);
        Ex::sorted_vector_verify(vi);
    });
}