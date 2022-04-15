//
// Created by Peter on 2022/4/14.
//

#ifndef EX_ARRAY_IMPL_QUEUE_H
#define EX_ARRAY_IMPL_QUEUE_H

#include "core_queue.h"

namespace Ex::ArrayImpl {

    template<typename T>
    class Queue {
    public:
        explicit Queue(unsigned long capacity)
                : head(0), tail(0), size(0), capacity(capacity) {
            data = new std::optional<T>[capacity];
        }

        ~Queue() {
            delete[]data;
        }

        void enqueue(T value) {
            if (size != capacity) {
                tail = tail % capacity;
                data[tail] = value;
                tail++;
                size++;
            }
        }

        void dequeue() {
            if (size > 0) {
                head = head % capacity;
                data[head] = std::optional<T>();
                head++;
                size--;
            }
        }

        auto get_head() {
            if (size > 0) {
                return data[head];
            }
            return std::optional<T>();
        }

        auto get_tail() {
            if (size > 0) {
                return data[tail - 1];
            }
            return std::optional<T>();
        }

        auto get_size() {
            return size;
        }

        auto get_capacity() {
            return capacity;
        }

        auto is_empty() {
            return size == 0;
        }

    private:
        std::optional<T> *data;
        unsigned long head;
        unsigned long tail;
        unsigned long size;
        unsigned long capacity;
    };

    void ex_array_impl_queue_list();

}

#endif //EX_ARRAY_IMPL_QUEUE_H
