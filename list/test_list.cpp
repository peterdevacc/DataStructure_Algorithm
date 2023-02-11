// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//

#include "ex_single_linked_list.h"
#include "ex_double_linked_list.h"
#include "ex_sorted_linked_list.h"

void Ex::test_list() {
    LinkedListImpl::ex_single_linked_list_test();
    LinkedListImpl::ex_double_linked_list_test();
    LinkedListImpl::ex_sorted_linked_list_test();
}
