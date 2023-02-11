// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_single_linked_list.h"

void Ex::LinkedListImpl::ex_single_linked_list_test() {
    SingleLinkedList<int> list{};
    list.insert(3);
    list.insert(5);
    list.insert(4);
    list.insert(6);
    list.insert(9);
    assert(list.get_size() == 5);
    list.remove(3);
    list.remove(4);
    list.remove(99);
    list.remove_head();
    list.remove_tail();
    assert(list.at(0) == 6);
    list.remove_head();
    list.insert(3);
    list.insert(5);
    list.insert(4);
    list.insert(9);
    assert(list.at(0) == 3);
    assert(list.at(1) == 5);
    assert(list.at(2) == 4);
    assert(list.at(3) == 9);
    assert(list[0] == 3);
    assert(list[1] == 5);
    assert(list[2] == 4);
    assert(list[3] == 9);
    assert(list.is_exist(3));
    assert(list.is_exist(4));
    assert(list.is_exist(9));
    assert(!list.is_exist(7));
    assert(list.get_head() == 3);
    assert(list.get_tail() == 9);
    assert(list.index_of(5) == 1);
    assert(list.index_of(4) == 2);
    assert(list.index_of(99) == -1);
}