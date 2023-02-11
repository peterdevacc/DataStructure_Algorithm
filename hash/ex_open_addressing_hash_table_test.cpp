// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_open_addressing_hash_table.h"

void Ex::OpenAddressing::hash_table_test() {
    const unsigned int capacity = 10;
    Ex::OpenAddressing::HashTable<int> ht{capacity};

    std::string emptyStr;
    auto result = ht.insert(emptyStr, 1);
    assert(!result);

    auto strList = {
        std::string{"hello"},
        std::string{"hell"},
        std::string{"hel"},
        std::string{"aaaaa"},
        std::string{"aaaa"},
        std::string{"aaa"}
    };
    int i = 1;
    for (auto str : strList) {
        ht.insert(str, i);
        assert(ht.get_size() == i);
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
        assert(ht.get_size() == j);
    }

    assert(ht.get_capacity() == capacity);
}
