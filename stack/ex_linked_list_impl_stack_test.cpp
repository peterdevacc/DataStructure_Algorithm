// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_linked_list_impl_stack.h"

void Ex::LinkedListImpl::stack_test() {
    Stack<int> si{};
    si.push(8);
    si.push(5);
    si.push(3);
    si.push(2);
    si.push(4);
    si.push(1);
    si.push(7);
    si.push(6);
    auto r = si.pop();
    assert(r == 6);
    si.remove(4);
    assert(si.get_top()->data == 7);
    assert(si.get_size() == 6);
    si.clear();
    assert(si.is_empty());
}