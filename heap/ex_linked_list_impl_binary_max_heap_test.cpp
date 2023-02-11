// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/3.
//

#include "ex_linked_list_impl_binary_max_heap.h"

Ex::LinkedListImpl::BinaryMaxHeap<std::string> generate_test_heap(std::vector<long> &testData) {
    Ex::LinkedListImpl::BinaryMaxHeap<std::string> heap{};
    std::for_each(testData.begin(), testData.end(), [&](const long &num){
        heap.insert(num, std::to_string(num));
    });

    return heap;
}

void Ex::LinkedListImpl::binary_max_heap_test() {
    std::vector<long> testDataForInsert{
        3, 1, 2, 4, 6, 0, 4
    };
    auto heapForInsert = generate_test_heap(testDataForInsert);

    assert(heapForInsert.get_size() == 6);
    auto rootForInsert = heapForInsert.get_root();
    assert(rootForInsert->num == 6);
    assert(rootForInsert->data == "6");
    assert(rootForInsert->left->num == 4);
    assert(rootForInsert->left->data == "4");
    assert(rootForInsert->left->left->num == 1);
    assert(rootForInsert->left->left->data == "1");
    assert(rootForInsert->left->right->num == 3);
    assert(rootForInsert->left->right->data == "3");
    assert(rootForInsert->right->num == 2);
    assert(rootForInsert->right->data == "2");
    assert(rootForInsert->right->left->num == 0);
    assert(rootForInsert->right->left->data == "0");

    std::vector<long> testDataForDelete{
        58,8,53,22,83,65,59,31,36,20,84,40,82,94
    };
    auto heapForDelete = generate_test_heap(testDataForDelete);

    heapForDelete.remove(58);
    auto rootForDelete = heapForDelete.get_root();
    assert(rootForDelete->num == 94);
    assert(rootForDelete->left->num == 83);
    assert(rootForDelete->left->right->num == 59);
    assert(rootForDelete->left->right->left->num == 20);
    assert(rootForDelete->left->right->right->num == 22);
    assert(rootForDelete->right->right->num == 82);
    assert(rootForDelete->right->right->left == nullptr);

    heapForDelete.remove(53);
    assert(rootForDelete->num == 94);
    assert(rootForDelete->right->left->num == 65);
    assert(rootForDelete->right->left->right == nullptr);

    heapForDelete.remove(40);
    assert(rootForDelete->num == 94);
    assert(rootForDelete->right->left->num == 65);
    assert(rootForDelete->right->left->left == nullptr);

    heapForDelete.remove(82);
    assert(rootForDelete->num == 94);
    assert(rootForDelete->right->num == 84);
    assert(rootForDelete->right->right->num == 22);
    assert(rootForDelete->right->left->num == 65);
    assert(rootForDelete->left->right->num == 59);
    assert(rootForDelete->left->right->left->num == 20);
    assert(rootForDelete->left->right->right == nullptr);

    heapForDelete.remove(8);
    assert(rootForDelete->num == 94);
    assert(rootForDelete->left->right->num == 59);
    assert(rootForDelete->left->right->left == nullptr);
    assert(rootForDelete->left->left->num == 36);
    assert(rootForDelete->left->left->left->num == 20);
    assert(rootForDelete->left->left->right->num == 31);

    heapForDelete.remove_max();
    assert(rootForDelete->num == 84);
    assert(rootForDelete->left->left->num == 36);
    assert(rootForDelete->left->left->right == nullptr);
}
