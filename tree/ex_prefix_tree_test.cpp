// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/12.
//

#include "ex_prefix_tree.h"

void Ex::LinkedListImpl::prefix_tree_test() {
    PrefixTree tree{"abc"};
    tree.insert("a");
    tree.insert("ab");
    tree.insert("aaa");
    tree.insert("c");
    tree.insert("b");
    tree.insert("cab");
    tree.insert("a");

    auto root = tree.get_root();
    assert(root->prefix.size() == 3);

    tree.remove("cab");
    PrefixTreeNode * startWithC = nullptr;
    for (const auto &item: root->prefix) {
        if (item->data.value() == 'c') {
            startWithC = item;
        }
    }
    assert(startWithC != nullptr);
    assert(startWithC->prefix.front()->data == 'a');
    assert(startWithC->prefix.front()->prefix.empty());

    tree.remove("a");
    assert(root->prefix.front()->data == 'a');

    tree.remove("b");
    assert(root->prefix.size() == 2);
    PrefixTreeNode * startWithB = nullptr;
    for (const auto &item: root->prefix) {
        if (item->data.value() == 'b') {
            startWithB = item;
        }
    }
    assert(startWithB == nullptr);

    tree.remove("aa");
    PrefixTreeNode * startWithA = root->prefix.front();
    assert(startWithA->data == 'a');
    bool isAbExisted = false;
    for (const auto &item: startWithA->prefix) {
        if (item->data.value() == 'a') {
            isAbExisted = true;
        }
    }
    assert(isAbExisted);

    bool cabExisted = tree.is_existed("cab");
    assert(!cabExisted);

    bool aaExisted = tree.is_existed("aa");
    assert(aaExisted);

    bool aaaExisted = tree.is_existed("aaa");
    assert(aaaExisted);

    bool bExisted = tree.is_existed("b");
    assert(!bExisted);
}
