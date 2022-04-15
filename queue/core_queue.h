//
// Created by Peter on 2022/4/14.
//

#ifndef CORE_QUEUE_H
#define CORE_QUEUE_H

#include <optional>
#include <cassert>

namespace Ex {

    namespace LinkedListImpl {

        template<typename T>
        struct QueueNode {
            std::optional<T> data;
            QueueNode<T> *next;
        };

    }

    void test_queue();

}

#endif //CORE_QUEUE_H
