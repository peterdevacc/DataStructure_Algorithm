// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_vector.h"

void Ex::ArrayImpl::vector_test() {
    Vector<int> vector{};

    assert(vector.get_capacity() == 3);
    vector.insert(5);
    vector.insert(3);
    vector.insert(2);
    vector.insert(1);
    assert(vector.get_capacity() == 6);
    vector.insert(4);
    vector.insert(9);
    vector.insert(6);
    assert(vector.get_capacity() == 12);
    vector.insert(7);
    assert(vector.get_size() == 8);

    assert(vector.at(3) == 1);
    assert(vector[3] == 1);

    vector.remove(1);
    vector.remove(7);
    assert(!vector.at(3).has_value());

    vector.remove(2);
    vector.remove(4);
    vector.remove(3);
    vector.remove(5);
    vector.remove(6);
    vector.remove(9);

    vector.insert(3);
    vector.insert(5);
    vector.insert(2);
    vector.insert(1);
    vector.insert(4);
    vector.insert(9);
    vector.insert(6);
    vector.insert(7);
    vector.remove_all();
    assert(vector.get_size() == 0);
    assert(vector.is_empty());
}
