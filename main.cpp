#include "array/core_array.h"
#include "list/core_list.h"
#include "queue/core_queue.h"
#include "stack/core_stack.h"
#include "hash/core_hash.h"
#include "tree/core_tree.h"
#include "graph/core_graph.h"
#include "sort/core_sort.h"

int main() {
    Ex::test_array();
    Ex::test_list();
    Ex::test_queue();
    Ex::test_stack();
    Ex::test_hash();
    Ex::test_tree();
    Ex::test_graph();
    Ex::test_sorting();
    return 0;
}
