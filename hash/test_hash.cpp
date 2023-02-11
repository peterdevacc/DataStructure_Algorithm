// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/14.
//
#include "ex_closed_addressing_hash_table.h"
#include "ex_open_addressing_hash_table.h"

void Ex::test_hash() {
    ClosedAddressing::ex_closed_addressing_hash_table_test();
    OpenAddressing::ex_open_addressing_hash_table_test();
}
