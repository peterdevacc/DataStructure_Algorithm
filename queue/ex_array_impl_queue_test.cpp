//
// Created by Peter on 2022/4/14.
//

#include "ex_array_impl_queue.h"

void Ex::ArrayImpl::ex_array_impl_queue_list() {
    Queue<int> qi{10};
    assert(qi.get_capacity() == 10);
    for (int i = 0; i < 10; ++i) {
        qi.enqueue(i);
    }
    qi.enqueue(10);
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