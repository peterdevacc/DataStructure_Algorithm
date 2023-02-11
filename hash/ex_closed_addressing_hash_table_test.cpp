// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_closed_addressing_hash_table.h"

void Ex::ClosedAddressing::ex_closed_addressing_hash_table_test() {
    const unsigned int size = 2;
    auto strList = {
        std::string{"hello"},
        std::string{"hell"},
        std::string{"hel"},
        std::string{"aaaaa"},
        std::string{"aaaa"},
        std::string{"aaa"}
    };
    Ex::ClosedAddressing::HashTable<int> ht{size};
    int i = 1;
    for (auto str : strList) {
        ht.insert(str, i);
        assert(ht.get_dataNum() == i);
        i++;
    }
    i = 1;
    for (auto str : strList) {
        assert(ht.find(str) == i);
        i++;
    }
    auto j = strList.size();
    for (auto str : strList) {
        ht.remove(str);
        j--;
        assert(!ht.find(str).has_value());
        assert(ht.get_dataNum() == j);
    }
    assert(ht.get_size() == size);
}
