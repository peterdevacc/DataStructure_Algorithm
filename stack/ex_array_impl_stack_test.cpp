// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_array_impl_stack.h"

void Ex::ArrayImpl::ex_array_impl_stack_test() {
    Stack<int> si{8};
    for (int i = 0; i < 8; ++i) {
        si.push(i);
        auto top = si.get_top();
        assert(top == i);
        auto size = i + 1;
        assert(si.get_size() == size);
    }
    for (int j = 8; j > 0; j--) {
        auto value = j - 1;
        auto pop = si.pop();
        assert(pop == value);
        assert(si.get_size() == value);
    }
    assert(si.is_empty());
    for (int i = 0; i < 8; ++i) {
        si.push(i);
    }
    si.pop();
    si.pop();
    si.push(10);
    assert(si.get_top() == 10);
}