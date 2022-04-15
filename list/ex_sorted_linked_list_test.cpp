//
// Created by Peter on 2022/4/14.
//

#include "ex_sorted_linked_list.h"

void Ex::LinkedListImpl::ex_sorted_linked_list_test() {
    SortedLinkedList<int> list{};
    list.insert(1);
    list.insert(3);
    list.insert(2);
    list.insert(4);
    list.insert(6);
    list.insert(7);
    list.insert(8);
    list.insert(9);
    list.insert(5);
    list.insert(0);
    assert(list.get_head() == 0);
    assert(list.at(9) == 9);
    assert(!list.at(99).has_value());
    assert(list.index_of(5) == 5);
    assert(list.index_of(55) == -1);
    assert(list.get_size() == 10);

    for (int i = 0; i < 10; ++i) {
        assert(list[i] == i);
    }

    list.remove(0);
    assert(list.at(0) == 1);
    list.remove(9);
    assert(list.at(7) == 8);

    for (int j = 2; j < 8; ++j) {
        list.remove(j);
        assert(!list.is_exist(j));
    }

    assert(list[0] == 1);
    assert(list[1] == 8);
}