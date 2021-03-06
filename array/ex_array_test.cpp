//
// Created by Peter on 2022/4/14.
//

#include "ex_array.h"

void Ex::ArrayImpl::ex_array_test() {
    Array<int> list{};

    assert(list.get_capacity() == 3);
    list.insert(5);
    list.insert(3);
    list.insert(2);
    list.insert(1);
    assert(list.get_capacity() == 6);
    list.insert(4);
    list.insert(9);
    list.insert(6);
    assert(list.get_capacity() == 12);
    list.insert(7);
    assert(list.get_size() == 8);

    assert(list.at(3) == 1);
    assert(list[3] == 1);

    list.remove(1);
    list.remove(7);
    assert(!list.at(3).has_value());

    list.remove(2);
    list.remove(4);
    list.remove(3);
    list.remove(5);
    list.remove(6);
    list.remove(9);

    list.insert(3);
    list.insert(5);
    list.insert(2);
    list.insert(1);
    list.insert(4);
    list.insert(9);
    list.insert(6);
    list.insert(7);
    list.remove_all();
    assert(list.get_size() == 0);
    assert(list.is_empty());
}
