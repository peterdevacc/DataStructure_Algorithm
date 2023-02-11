// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_avl_tree.h"
#include "ex_binary_search_tree.h"
#include "ex_splay_tree.h"

void Ex::test_tree() {
    LinkedListImpl::avl_tree_test();
    LinkedListImpl::binary_search_tree_test();
    LinkedListImpl::splay_tree_test();
}
