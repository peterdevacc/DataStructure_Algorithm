// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//
#include "ex_closed_addressing_hash_table.h"
#include "ex_open_addressing_hash_table.h"

void Ex::test_hash() {
    ClosedAddressing::hash_table_test();
    OpenAddressing::hash_table_test();
}
