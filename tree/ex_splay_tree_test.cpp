// /*
//  * Copyright (c) 2018 - 2023 洪振健.
//  * Use of this source code is governed by the GNU GENERAL PUBLIC LICENSE Version 3 that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_splay_tree.h"

void splay_tree_common_test();
void splay_tree_zig_left_test();
void splay_tree_zig_right_test();
void splay_tree_zig_zig_left_test();
void splay_tree_zig_zig_right_test();
void splay_tree_zig_zag_left_test();
void splay_tree_zig_zag_right_test();

void Ex::LinkedListImpl::splay_tree_test() {
    splay_tree_common_test();
    splay_tree_zig_left_test();
    splay_tree_zig_right_test();
    splay_tree_zig_zig_left_test();
    splay_tree_zig_zig_right_test();
    splay_tree_zig_zag_left_test();
    splay_tree_zig_zag_right_test();
}

void splay_tree_common_test() {
    Ex::LinkedListImpl::SplayTree<std::string> splayTree{};

    splayTree.insert(10, "10");
    splayTree.insert(20, "20");
    splayTree.insert(30, "30");

    auto root = splayTree.get_root();
    assert(root->num == 30);
    assert(root->data == "30");
    assert(root->parent == nullptr);

    auto leftSubTree = root->left;
    assert(leftSubTree->num == 20);
    assert(leftSubTree->data == "20");
    assert(leftSubTree->parent == root);

    assert(leftSubTree->left->num == 10);
    assert(leftSubTree->left->data == "10");
    assert(leftSubTree->left->parent == leftSubTree);

    auto rightSubTree = root->right;
    assert(rightSubTree == nullptr);

    splayTree.remove(30);
    assert(!splayTree.find(30).has_value());
    assert(splayTree.get_root()->num == 20);
    splayTree.remove(25);
    assert(!splayTree.find(25).has_value());
    assert(splayTree.get_size() == 2);

    assert(splayTree.find(10) == "10");
    root = splayTree.get_root();
    assert(root->num == 10);
    assert(root->left == nullptr);
    assert(root->right->num == 20);
    assert(root->right->data == "20");
    assert(root->right->parent == root);
}

void splay_tree_zig_left_test() {
    Ex::LinkedListImpl::SplayTree<std::string> splayTree{};
    splayTree.insert(10, "10");

    // insert trigger zig_left
    splayTree.insert(20, "20");
    auto root = splayTree.get_root();
    assert(root->num == 20);
    assert(root->left->num == 10);
    assert(root->right == nullptr);

    splayTree.find(10);
    // delete trigger zig_left
    splayTree.remove(20);
    root = splayTree.get_root();
    assert(root->num == 10);
    assert(root->left == nullptr);
    assert(root->right == nullptr);

    splayTree.insert(5, "5");
    // find trigger zig_left
    splayTree.find(10);
    root = splayTree.get_root();
    assert(root->num == 10);
    assert(root->left->num == 5);
    assert(root->right == nullptr);
}

void splay_tree_zig_right_test() {
    Ex::LinkedListImpl::SplayTree<std::string> splayTree{};
    splayTree.insert(20, "20");

    // insert trigger zig_right
    splayTree.insert(10, "10");
    auto root = splayTree.get_root();
    assert(root->num == 10);
    assert(root->left == nullptr);
    assert(root->right->num == 20);

    splayTree.find(20);
    // delete trigger zig_right
    splayTree.remove(10);
    root = splayTree.get_root();
    assert(root->num == 20);
    assert(root->left == nullptr);
    assert(root->right == nullptr);

    splayTree.insert(25, "25");
    // find trigger zig_right
    splayTree.find(20);
    root = splayTree.get_root();
    assert(root->num == 20);
    assert(root->right->num == 25);
    assert(root->left == nullptr);
}

void splay_tree_zig_zig_left_test() {
    Ex::LinkedListImpl::SplayTree<std::string> splayTree{};
    splayTree.insert(20, "20");
    splayTree.insert(15, "15");
    splayTree.insert(10, "10");

    // insert trigger zig_zig_left
    splayTree.insert(25, "25");
    auto root = splayTree.get_root();
    assert(root->num == 25);
    auto leftSubTree = root->left;
    assert(leftSubTree->num == 10);
    assert(leftSubTree->left == nullptr);
    assert(leftSubTree->right->num == 20);
    assert(leftSubTree->right->left->num == 15);
    assert(leftSubTree->right->right == nullptr);

    splayTree.find(15);
    splayTree.find(10);
    // delete trigger zig_zig_left
    splayTree.remove(25);
    root = splayTree.get_root();
    assert(root->num == 15);
    assert(root->left->num == 10);
    assert(root->right->num == 20);

    splayTree.insert(5, "5");
    // find trigger zig_zig_left
    splayTree.find(15);
    root = splayTree.get_root();
    assert(root->num == 15);
    assert(root->left->num == 10);
    assert(root->right->num == 20);
    assert(root->left->left->num == 5);
    assert(root->left->right == nullptr);
}

void splay_tree_zig_zig_right_test() {
    Ex::LinkedListImpl::SplayTree<std::string> splayTree{};
    splayTree.insert(5, "5");
    splayTree.insert(10, "10");
    splayTree.insert(15, "15");

    // insert trigger zig_zig_right
    splayTree.insert(0, "0");
    auto root = splayTree.get_root();
    assert(root->num == 0);
    assert(root->left == nullptr);
    auto rightSubTree = root->right;
    assert(rightSubTree->num == 15);
    assert(rightSubTree->left->num == 5);
    assert(rightSubTree->right == nullptr);
    assert(rightSubTree->left->right->num == 10);
    assert(rightSubTree->left->left == nullptr);

    splayTree.find(10);
    splayTree.find(15);
    // delete trigger zig_zig_right
    splayTree.remove(0);
    root = splayTree.get_root();
    assert(root->num == 10);
    assert(root->left->num == 5);
    assert(root->right->num == 15);

    splayTree.insert(20, "20");
    // find trigger zig_zig_right
    splayTree.find(10);
    root = splayTree.get_root();
    assert(root->num == 10);
    assert(root->left->num == 5);
    assert(root->right->num == 15);
    assert(root->right->right->num == 20);
    assert(root->right->left == nullptr);
}

void splay_tree_zig_zag_left_test() {
    Ex::LinkedListImpl::SplayTree<std::string> splayTree{};
    splayTree.insert(20, "20");
    splayTree.insert(10, "10");

    // insert trigger zig_zag_left
    splayTree.insert(15, "15");
    auto root = splayTree.get_root();
    assert(root->num == 15);
    assert(root->left->num == 10);
    assert(root->right->num == 20);

    splayTree.insert(18, "18");
    splayTree.insert(13, "13");
    // delete trigger zig_zag_left
    splayTree.remove(15);
    root = splayTree.get_root();
    assert(root->num == 13);
    assert(root->left->num == 10);
    assert(root->right->num == 18);
    assert(root->right->left == nullptr);
    assert(root->right->right->num == 20);

    splayTree.insert(25, "25");
    // find trigger zig_zag_left
    splayTree.find(18);
    root = splayTree.get_root();
    assert(root->num == 18);
    auto leftSubTree = root->left;
    assert(leftSubTree->num == 13);
    assert(leftSubTree->left->num == 10);
    assert(leftSubTree->right == nullptr);
    auto rightSubTree = root->right;
    assert(rightSubTree->num == 25);
    assert(rightSubTree->left->num == 20);
    assert(rightSubTree->right == nullptr);
}

void splay_tree_zig_zag_right_test() {
    Ex::LinkedListImpl::SplayTree<std::string> splayTree{};
    splayTree.insert(10, "10");
    splayTree.insert(20, "20");

    // insert trigger zig_zag_right
    splayTree.insert(15, "15");
    auto root = splayTree.get_root();
    assert(root->num == 15);
    assert(root->left->num == 10);
    assert(root->right->num == 20);

    splayTree.insert(13, "13");
    splayTree.insert(18, "18");
    // delete trigger zig_zag_right
    splayTree.remove(15);
    root = splayTree.get_root();
    assert(root->num == 13);
    assert(root->left->num == 10);
    assert(root->right->num == 18);
    assert(root->right->left == nullptr);
    assert(root->right->right->num == 20);

    splayTree.insert(25, "25");
    // find trigger zig_zag_right
    splayTree.find(20);
    root = splayTree.get_root();
    assert(root->num == 20);
    auto leftSubTree = root->left;
    assert(leftSubTree->num == 13);
    assert(leftSubTree->left->num == 10);
    assert(leftSubTree->right->num == 18);
    auto rightSubTree = root->right;
    assert(rightSubTree->num == 25);
}
