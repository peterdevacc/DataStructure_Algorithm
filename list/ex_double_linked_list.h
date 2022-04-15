//
// Created by Peter on 2022/4/14.
//

#ifndef EX_DOUBLE_LINKED_LIST_H
#define EX_DOUBLE_LINKED_LIST_H

#include "core_list.h"

namespace Ex::LinkedListImpl {

    template<typename T>
    class DoubleLinkedList {
    public:
        DoubleLinkedList() : head(nullptr), tail(nullptr), pivot(nullptr), size(0) {}

        ~DoubleLinkedList() {
            if (size > 0) {
                auto temp = head->next;
                while (temp != head) {
                    auto d = temp;
                    temp = temp->next;
                    delete d;
                }
                delete head;
            }
        }

        void insert(T data) {
            auto *node = new DoubleLinkedListNode<T>;
            node->data = data;

            if (head == nullptr) {
                node->prev = node;
                node->next = node;
                head = node;
                tail = node;
            } else {
                node->prev = tail;
                node->next = head;
                head->prev = node;
                tail->next = node;
                tail = node;
            }
            size++;
            pivot = node;
        }

        void remove_head() {
            if (size > 0) {
                auto d = head;
                if (size != 1) {
                    head = head->next;
                    head->prev = tail;
                    tail->next = head;
                } else {
                    head = nullptr;
                    tail = nullptr;
                }
                delete d;
                size--;
            }
        }

        void remove_tail() {
            if (size > 0) {
                auto d = tail;
                if (size != 1) {
                    head->prev = tail->prev;
                    tail->prev->next = head;
                    tail = tail->prev;
                } else {
                    head = nullptr;
                    tail = nullptr;
                }
                delete d;
                size--;
            }
        }

        void remove(T data) {
            if (size > 0) {
                if (head->data == data) {
                    remove_head();
                    return;
                }

                if (tail->data == data) {
                    remove_tail();
                    return;
                }

                auto temp = head->next;
                while (temp != tail) {
                    if (temp->data == data) {
                        auto d = temp;
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;
                        delete d;
                        size--;
                        return;
                    }
                    temp = temp->next;
                }
            }
        }

        auto get_head() {
            if (size == 0) {
                return std::optional<T>();
            }
            return head->data;
        }

        auto get_tail() {
            if (size == 0) {
                return std::optional<T>();
            }
            return tail->data;
        }

        auto at(unsigned long position) {
            if (position >= 0 && position < size) {
                if (position == 0) {
                    return head->data;
                }
                if (position == size - 1) {
                    return tail->data;
                }
                auto temp = head->next;
                unsigned long counter = 1;
                while (temp != tail) {
                    if (counter == position) {
                        return temp->data;
                    }
                    temp = temp->next;
                    counter++;
                }
            }

            return std::optional<T>();
        }

        auto operator[](unsigned long position) {
            return at(position);
        }

        auto is_exist(T data) {
            if (size > 0) {
                if (pivot->data == data) {
                    return true;
                }
                auto temp = pivot->next;
                while (temp != pivot) {
                    if (temp->data == data) {
                        pivot = temp;
                        return true;
                    }
                    temp = temp->next;
                }

                return false;
            }

            return false;
        }

        long index_of(T data) {
            if (size > 0) {
                long index = 1;

                if (head->data == data) {
                    return 0;
                }

                if (tail->data == data) {
                    return size - 1;
                }

                auto temp = head->next;
                while (temp != tail) {
                    if (temp->data == data) {
                        return index;
                    }
                    temp = temp->next;
                    index++;
                }

                return -1;
            }

            return -1;
        }

        auto get_size() {
            return size;
        }

    private:
        DoubleLinkedListNode <T> *head;
        DoubleLinkedListNode <T> *tail;
        DoubleLinkedListNode <T> *pivot;
        unsigned long size;
    };

    void ex_double_linked_list_test();

}

#endif //EX_DOUBLE_LINKED_LIST_H
