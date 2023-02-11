// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_linked_list_impl_queue.h"

void Ex::LinkedListImpl::ex_linked_list_impl_queue_test() {
    Queue<int> qi{};
    for (int i = 0; i < 10; ++i) {
        qi.enqueue(i);
    }
    assert(qi.get_size() == 10);
    assert(qi.get_head() == 0);
    assert(qi.get_tail() == 9);
    qi.dequeue();
    qi.dequeue();
    assert(qi.get_size() == 8);
    assert(qi.get_head() == 2);
    qi.enqueue(11);
    assert(qi.get_tail() == 11);
    for (int j = 0; j < 9; ++j) {
        qi.dequeue();
    }
    assert(qi.is_empty());
}