// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter Dev on 2023/2/3.
//

#include "ex_array_impl_binary_max_heap.h"

Ex::ArrayImpl::BinaryMaxHeap<long> generate_test_heap(std::vector<long> &testData) {
    Ex::ArrayImpl::BinaryMaxHeap<long> heap{};
    std::for_each(testData.begin(), testData.end(), [&](const long &num){
        heap.insert(num);
    });

    return heap;
}

void verify_result(std::vector<std::optional<long>> &actual, std::vector<std::optional<long>> &expected) {
    assert(actual.size() == expected.size());
    for (int i = 0; i < expected.size(); ++i) {
        assert(actual[i] == expected[i]);
    }
}

void Ex::ArrayImpl::binary_max_heap_test() {
    std::vector<long> testDataForInsert{
        3, 1, 2, 4, 6, 0, 4
    };
    auto heapForInsert = generate_test_heap(testDataForInsert);

    auto resultForInsert = heapForInsert.get_vector();
    std::vector<std::optional<long>> expectedInsert{
        6, 4, 2, 1, 3, 0
    };
    assert(resultForInsert.size() == expectedInsert.size());
    for (int i = 0; i < expectedInsert.size(); ++i) {
        assert(resultForInsert[i] == expectedInsert[i]);
    }
    verify_result(resultForInsert, expectedInsert);

    std::vector<long> testDataForDelete{
        58,8,53,22,83,65,59,31,36,20,84,40,82,94
    };
    auto heapForDelete = generate_test_heap(testDataForDelete);

    heapForDelete.remove(58);
    auto resultForDeleteA = heapForDelete.get_vector();
    std::vector<std::optional<long>> expectedDeleteA{
        94,83,84,36,59,65,82,8,31,20,22,40,53
    };
    verify_result(resultForDeleteA, expectedDeleteA);

    heapForDelete.remove(53);
    auto resultForDeleteB = heapForDelete.get_vector();
    std::vector<std::optional<long>> expectedDeleteB{
        94,83,84,36,59,65,82,8,31,20,22,40
    };
    verify_result(resultForDeleteB, expectedDeleteB);

    heapForDelete.remove(40);
    auto resultForDeleteC = heapForDelete.get_vector();
    std::vector<std::optional<long>> expectedDeleteC{
        94,83,84,36,59,65,82,8,31,20,22
    };
    verify_result(resultForDeleteC, expectedDeleteC);

    heapForDelete.remove(82);
    auto resultForDeleteD = heapForDelete.get_vector();
    std::vector<std::optional<long>> expectedDeleteD{
        94,83,84,36,59,65,22,8,31,20
    };
    verify_result(resultForDeleteD, expectedDeleteD);

    heapForDelete.remove(8);
    auto resultForDeleteE = heapForDelete.get_vector();
    std::vector<std::optional<long>> expectedDeleteE{
        94,83,84,36,59,65,22,20,31
    };
    verify_result(resultForDeleteE, expectedDeleteE);

    heapForDelete.remove_max();
    auto resultForDeleteF = heapForDelete.get_vector();
    std::vector<std::optional<long>> expectedDeleteF{
        84,83,65,36,59,31,22,20
    };
    verify_result(resultForDeleteF, expectedDeleteF);

}
