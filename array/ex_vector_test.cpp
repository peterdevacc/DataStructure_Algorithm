// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_vector.h"

using namespace Ex::ArrayImpl;

void vector_single_thread_test();
void vector_multi_thread_test();

void Ex::ArrayImpl::vector_test() {
    vector_single_thread_test();
    vector_multi_thread_test();
}

void vector_single_thread_test() {
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

    assert(vector.at(3) == 1);
    assert(vector[3] == 1);

    std::vector<std::optional<int>> expectedVector{
        5, 3, 2, 1, 4, 9, 6, 7
    };
    assert(vector.get_size() == expectedVector.size());
    auto i = 0;
    std::for_each(vector.begin(), vector.end(), [&](const auto num){
        assert(num.value() == expectedVector[i].value());
        i += 1;
    });

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

void vector_multi_thread_test() {
    Vector<std::string> vector{};

    auto vectorInsert = [&vector]() {
        for (int i = 0; i < 3; i++) {
            auto id = std::hash<std::thread::id>{}(std::this_thread::get_id());
            vector.insert(std::to_string(id) + "-num-" + std::to_string(i));
        }
    };

    std::thread threadA(vectorInsert);
    std::thread threadB(vectorInsert);

    threadA.join();
    threadB.join();

    assert(vector.get_size() == 6);
}
