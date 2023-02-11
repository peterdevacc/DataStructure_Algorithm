// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_binary_search_tree.h"

void binary_search_tree_common_test();
void binary_search_tree_insert_test();
void binary_search_tree_delete_test();

void Ex::LinkedListImpl::binary_search_tree_test() {
    binary_search_tree_common_test();
    binary_search_tree_insert_test();
    binary_search_tree_delete_test();
}

void binary_search_tree_common_test() {
    Ex::LinkedListImpl::BinarySearchTree<std::string> binaryTree{};
    binaryTree.insert(50, "50");
    binaryTree.insert(30, "30");
    binaryTree.insert(60, "60");
    binaryTree.insert(50, "50");
    binaryTree.insert(30, "30");
    binaryTree.insert(60, "60");
    assert(binaryTree.get_size() == 3);

    auto root = binaryTree.get_root();
    assert(root->num == 50);
    assert(root->data == "50");
    assert(root->parent == nullptr);
    assert(root->left->num == 30);
    assert(root->left->data == "30");
    assert(root->left->parent == root);
    assert(root->right->num == 60);
    assert(root->right->data == "60");
    assert(root->right->parent == root);

    assert(binaryTree.find(50) == "50");
    assert(binaryTree.find(30) == "30");
    assert(binaryTree.find(60) == "60");

    binaryTree.remove(30);
    assert(!binaryTree.find(30).has_value());
    binaryTree.remove(60);
    assert(!binaryTree.find(60).has_value());
    binaryTree.remove(50);
    assert(!binaryTree.find(50).has_value());

    assert(binaryTree.get_size() == 0);
}

void binary_search_tree_insert_test() {
    Ex::LinkedListImpl::BinarySearchTree<std::string> binaryTree{};
    binaryTree.insert(50, "50");
    binaryTree.insert(30, "30");
    binaryTree.insert(60, "60");

    // left sub tree
    binaryTree.insert(20, "20");
    binaryTree.insert(25, "25");
    binaryTree.insert(10, "10");
    auto leftSubTree = binaryTree.get_root()->left->left;
    assert(leftSubTree->num == 20);
    assert(leftSubTree->left->num == 10);
    assert(leftSubTree->right->num == 25);

    // right sub tree
    binaryTree.insert(70, "70");
    binaryTree.insert(65, "65");
    binaryTree.insert(80, "80");
    auto rightSubTree = binaryTree.get_root()->right->right;
    assert(rightSubTree->num == 70);
    assert(rightSubTree->left->num == 65);
    assert(rightSubTree->right->num == 80);
}

void binary_search_tree_delete_test() {
    Ex::LinkedListImpl::BinarySearchTree<std::string> binaryTree{};

    // leaf
    binaryTree.insert(50, "50");
    binaryTree.insert(30, "30");
    binaryTree.insert(60, "60");

    binaryTree.remove(30);
    binaryTree.remove(60);
    auto root = binaryTree.get_root();
    assert(root->left == nullptr);
    assert(root->right == nullptr);
    binaryTree.remove(50);
    assert(binaryTree.get_root() == nullptr);

    // node only have left child
    binaryTree.insert(50, "50");
    binaryTree.insert(30, "30");
    binaryTree.insert(20, "20");
    binaryTree.insert(10, "10");

    binaryTree.remove(20);
    assert(binaryTree.get_root()->left->left->num == 10);
    binaryTree.remove(50);
    assert(binaryTree.get_root()->num == 30);
    binaryTree.remove(30);
    assert(binaryTree.get_root()->num == 10);
    binaryTree.remove(10);
    assert(binaryTree.get_root() == nullptr);

    // node only have right child
    binaryTree.insert(10, "10");
    binaryTree.insert(20, "20");
    binaryTree.insert(30, "30");
    binaryTree.insert(50, "50");

    binaryTree.remove(30);
    assert(binaryTree.get_root()->right->right->num == 50);
    binaryTree.remove(10);
    assert(binaryTree.get_root()->num == 20);
    binaryTree.remove(20);
    assert(binaryTree.get_root()->num == 50);
    binaryTree.remove(50);
    assert(binaryTree.get_root() == nullptr);

    // node have left and right child, leftSubTree largest is itself
    binaryTree.insert(50, "50");
    binaryTree.insert(30, "30");
    binaryTree.insert(60, "60");

    binaryTree.remove(50);
    root = binaryTree.get_root();
    assert(root->num == 30);
    assert(root->left == nullptr);
    assert(root->right->num == 60);
    assert(root->right->parent == root);

    // node have left and right child, leftSubTree largest is it's rightSubTree largest
    // and that node is leaf
    binaryTree.insert(20, "20");
    binaryTree.insert(25, "25");
    binaryTree.insert(28, "28");

    binaryTree.remove(30);
    root = binaryTree.get_root();
    assert(root->num == 28);
    assert(root->right->num == 60);
    assert(root->right->parent == root);
    auto leftSubTree = root->left;
    assert(leftSubTree->num == 20);
    assert(leftSubTree->parent == root);
    assert(leftSubTree->right->num == 25);
    assert(leftSubTree->right->parent == leftSubTree);
    assert(leftSubTree->right->right == nullptr);

    // node have left and right child, leftSubTree largest is it's rightSubTree largest
    // and that node have left child
    binaryTree.insert(23, "23");

    binaryTree.remove(28);
    root = binaryTree.get_root();
    assert(root->num == 25);
    assert(root->right->num == 60);
    assert(root->right->parent == root);
    leftSubTree = root->left;
    assert(leftSubTree->num == 20);
    assert(leftSubTree->parent == root);
    assert(leftSubTree->right->num == 23);
    assert(leftSubTree->right->parent == leftSubTree);
    assert(leftSubTree->right->right == nullptr);
}
