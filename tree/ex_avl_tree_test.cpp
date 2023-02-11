// /*
//  * Copyright 2018-2023 洪振健.
//  * Use of this source code is governed by the GNU general public license that can be found in the LICENSE file.
//  *

//
// Created by Peter on 2022/4/15.
//

#include "ex_avl_tree.h"

void avl_tree_common_test();
void avl_tree_left_rotation_test();
void avl_tree_right_rotation_test();
void avl_tree_left_right_rotation_test();
void avl_tree_right_left_rotation_test();

void Ex::LinkedListImpl::ex_avl_tree_test() {
    avl_tree_common_test();
    avl_tree_left_rotation_test();
    avl_tree_right_rotation_test();
    avl_tree_left_right_rotation_test();
    avl_tree_right_left_rotation_test();
}

void avl_tree_common_test() {
    Ex::LinkedListImpl::AVLTree<std::string> avlTree{};
    avlTree.insert(1, "1");
    avlTree.insert(2, "2");
    avlTree.insert(3, "3");
    assert(avlTree.get_size() == 3);

    auto root = avlTree.get_root();
    assert(root->num == 2);
    assert(root->data == "2");
    assert(root->height == 1);
    assert(root->parent == nullptr);

    auto left = root->left;
    assert(left->num == 1);
    assert(left->data == "1");
    assert(left->height == 0);
    assert(left->parent == root);

    auto right = root->right;
    assert(right->num == 3);
    assert(right->data == "3");
    assert(right->height == 0);
    assert(right->parent == root);

    assert(avlTree.find(1) == "1");
    assert(avlTree.find(2) == "2");
    assert(avlTree.find(3) == "3");
    assert(!avlTree.find(4).has_value());

    avlTree.remove(3);
    assert(!avlTree.find(3).has_value());
    assert(avlTree.get_size() == 2);
}

void avl_tree_left_rotation_test() {
    Ex::LinkedListImpl::AVLTree<std::string> avlTree{};
    avlTree.insert(1, "1");
    avlTree.insert(2, "2");
    avlTree.insert(3, "3");

    // insert trigger left rotation
    auto root = avlTree.get_root();
    assert(root->num == 2);
    assert(root->parent == nullptr);
    assert(root->height == 1);
    assert(root->left->num == 1);
    assert(root->left->parent == root);
    assert(root->left->height == 0);
    assert(root->right->num == 3);
    assert(root->right->parent == root);
    assert(root->right->height == 0);

    avlTree.insert(4, "4");
    avlTree.insert(5, "5");
    avlTree.insert(0, "0");
    avlTree.insert(6, "6");

    // remove trigger left rotation
    avlTree.remove(4);
    assert(root->num == 2);
    assert(root->height == 2);
    assert(root->parent == nullptr);
    auto leftSubTree = root->left;
    assert(leftSubTree->num == 1);
    assert(leftSubTree->parent == root);
    assert(leftSubTree->height == 1);
    assert(leftSubTree->left->num == 0);
    assert(leftSubTree->left->parent == leftSubTree);
    assert(leftSubTree->left->height == 0);
    assert(leftSubTree->right == nullptr);
    auto rightSubTree = root->right;
    assert(rightSubTree->num == 5);
    assert(rightSubTree->parent == root);
    assert(rightSubTree->height == 1);
    assert(rightSubTree->left->num == 3);
    assert(rightSubTree->left->parent == rightSubTree);
    assert(rightSubTree->left->height == 0);
    assert(rightSubTree->right->num == 6);
    assert(rightSubTree->right->parent == rightSubTree);
    assert(rightSubTree->right->height == 0);
}

void avl_tree_right_rotation_test() {
    Ex::LinkedListImpl::AVLTree<std::string> avlTree{};
    avlTree.insert(30, "30");
    avlTree.insert(20, "20");
    avlTree.insert(10, "10");

    // insert trigger right rotation
    auto root = avlTree.get_root();
    assert(root->num == 20);
    assert(root->parent == nullptr);
    assert(root->height == 1);

    assert(root->left->num == 10);
    assert(root->left->parent == root);
    assert(root->left->height == 0);

    assert(root->right->num == 30);
    assert(root->right->parent == root);
    assert(root->right->height == 0);

    avlTree.insert(5, "5");
    avlTree.insert(2, "2");
    avlTree.insert(40, "40");
    avlTree.insert(1, "1");

    // remove trigger right rotation
    avlTree.remove(10);
    assert(root->num == 20);
    assert(root->height == 2);
    assert(root->parent == nullptr);

    auto leftSubTree = root->left;
    assert(leftSubTree->num == 2);
    assert(leftSubTree->parent == root);
    assert(leftSubTree->height == 1);

    assert(leftSubTree->left->num == 1);
    assert(leftSubTree->left->parent == leftSubTree);
    assert(leftSubTree->left->height == 0);

    assert(leftSubTree->right->num == 5);
    assert(leftSubTree->right->parent == leftSubTree);
    assert(leftSubTree->right->height == 0);

    auto rightSubTree = root->right;
    assert(rightSubTree->num == 30);
    assert(rightSubTree->parent == root);
    assert(rightSubTree->height == 1);

    assert(rightSubTree->left == nullptr);

    assert(rightSubTree->right->num == 40);
    assert(rightSubTree->right->parent == rightSubTree);
    assert(rightSubTree->right->height == 0);
}

void avl_tree_left_right_rotation_test() {
    Ex::LinkedListImpl::AVLTree<std::string> avlTree{};
    avlTree.insert(30, "30");
    avlTree.insert(10, "10");
    avlTree.insert(20, "20");

    // insert trigger left_right rotation
    auto root = avlTree.get_root();
    assert(root->num == 20);
    assert(root->parent == nullptr);
    assert(root->height == 1);

    auto leftSubTree = root->left;
    assert(leftSubTree->num == 10);
    assert(leftSubTree->parent == root);
    assert(leftSubTree->height == 0);

    auto rightSubTree = root->right;
    assert(rightSubTree->num == 30);
    assert(rightSubTree->parent == root);
    assert(rightSubTree->height == 0);

    // remove trigger left_left rotation
    avlTree.insert(15, "15");
    avlTree.remove(30);
    root = avlTree.get_root();
    assert(root->num == 15);
    assert(root->parent == nullptr);
    assert(root->height == 1);

    leftSubTree = root->left;
    assert(leftSubTree->num == 10);
    assert(leftSubTree->parent == root);
    assert(leftSubTree->height == 0);

    rightSubTree = root->right;
    assert(rightSubTree->num == 20);
    assert(rightSubTree->parent == root);
    assert(rightSubTree->height == 0);
}

void avl_tree_right_left_rotation_test() {
    Ex::LinkedListImpl::AVLTree<std::string> avlTree{};
    avlTree.insert(20, "20");
    avlTree.insert(30, "30");
    avlTree.insert(25, "25");

    // insert trigger right_left rotation
    auto root = avlTree.get_root();
    assert(root->num == 25);
    assert(root->parent == nullptr);
    assert(root->height == 1);

    auto leftSubTree = root->left;
    assert(leftSubTree->num == 20);
    assert(leftSubTree->parent == root);
    assert(leftSubTree->height == 0);

    auto rightSubTree = root->right;
    assert(rightSubTree->num == 30);
    assert(rightSubTree->parent == root);
    assert(rightSubTree->height == 0);

    // remove trigger right_left rotation
    avlTree.insert(28, "28");
    avlTree.remove(20);
    root = avlTree.get_root();
    assert(root->num == 28);
    assert(root->parent == nullptr);
    assert(root->height == 1);

    leftSubTree = root->left;
    assert(leftSubTree->num == 25);
    assert(leftSubTree->parent == root);
    assert(leftSubTree->height == 0);

    rightSubTree = root->right;
    assert(rightSubTree->num == 30);
    assert(rightSubTree->parent == root);
    assert(rightSubTree->height == 0);

}
