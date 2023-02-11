// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

#include "array/core_array.h"
#include "list/core_list.h"
#include "queue/core_queue.h"
#include "stack/core_stack.h"
#include "hash/core_hash.h"
#include "heap/core_heap.h"
#include "tree/core_tree.h"
#include "graph/core_graph.h"
#include "sort/core_sort.h"

int main() {
    Ex::test_array();
    Ex::test_list();
    Ex::test_queue();
    Ex::test_stack();
    Ex::test_heap();
    Ex::test_hash();
    Ex::test_tree();
    Ex::test_graph();
    Ex::test_sorting();
    return 0;
}
