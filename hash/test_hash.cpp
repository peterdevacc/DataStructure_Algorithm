//
// Created by Peter on 2022/4/14.
//
#include "ex_closed_addressing_hash_table.h"
#include "ex_open_addressing_hash_table.h"

void Ex::test_hash() {
    ClosedAddressing::ex_closed_addressing_hash_table_test();
    OpenAddressing::ex_open_addressing_hash_table_test();
}
