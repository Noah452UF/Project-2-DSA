// Author: Carter Veit
// Description: Defines functions for bplus for use
//              in project 2.
//
// Last Modified: November 3, 2026
// Last Modified By: Carter Veit

#include "bplus.h"
#include <algorithm>

Node::Node(const Car &n) {
    leaf = 0;
    parent = nullptr;
    next = nullptr;
    prev = nullptr;
    arr.push_back(n);
}
Node::Node(vector<Car> arr_) {
    leaf = 0;
    parent = nullptr;
    next = nullptr;
    prev = nullptr;
    arr = arr_;
}

BPlus::BPlus(bool (*operation_)(Car, Car), int k_) {
    operation = operation_;
    k = k_;
    root = nullptr;
    head = nullptr;
    tail = nullptr;
}

Node* BPlus::traverseDown(Node *root, const Car& n) {
    // Base case. At bottom of the tree and no further traversal downwards.
    if (root->directions.size() == 0) {
        return root;
    }

    // Loop through node. Inserted node traverses to the left of whatever Car obj in node array
    // satisfies operation. If none satisfies, traverse down the right direction.
    for (int i = 0; i < root->arr.size(); i++) {
        if (operation(n, root->arr[i])) {
            return traverseDown(root->directions[i], n);
        }
    }
    return traverseDown(root->directions[root->arr.size()], n);
}

Node *BPlus::split(Node *root) {

}

void BPlus::insert(const Car &n) {
    // Base case.
    if (root == nullptr) {
        root = new Node(n);
        return;
    }

    // Insert new Car into desired node at appropriate position.
    Node* point = traverseDown(root, n);
    int i;
    for (i = 0; i < point->arr.size(); i++) {
        if (operation(n, point->arr[i])) {
            break;
        }
    }
    point->arr.insert(point->arr.begin() + i, n);

    // Check
}
