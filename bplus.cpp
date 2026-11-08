// Author: Carter Veit
// Description: Defines functions for bplus for use
//              in project 2.
//
// Last Modified: November 3, 2026
// Last Modified By: Carter Veit

#include "bplus.h"
#include <algorithm>

Node::Node(const bool &leaf_) {
    leaf = leaf_;
    parent = nullptr;
    next = nullptr;
    prev = nullptr;
}

Node::Node(const Car &c, const bool& leaf_) {
    leaf = leaf_;
    parent = nullptr;
    next = nullptr;
    prev = nullptr;
    arr.push_back(c);
}
Node::Node(vector<Car> arr_, const bool& leaf_) {
    leaf = leaf_;
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

void BPlus::postOrderDelete(Node *n) {
    for (int i = 0; i < n->directions.size(); i++) {
        postOrderDelete(n->directions[i]);
    }

    delete n;
}

BPlus::~BPlus() {
    postOrderDelete(root);
}

Node* BPlus::traverseDown(stack<pair<Node*, int>>& traversed,Node *n, const Car& c) {
    // Pass node to stack to keep track of traversed nodes.
    // Base case. At bottom of the tree and no further traversal downwards.
    if (n->directions.size() == 0) {
        return n;
    }

    // Loop through node. Inserted node traverses to the left of whatever Car obj in node array
    // satisfies operation. If none satisfies, traverse down the right direction.
    for (int i = 0; i < n->arr.size(); i++) {
        if (operation(c, n->arr[i])) {
            traversed.push(make_pair(n, i));
            return traverseDown(traversed, n->directions[i], c);
        }
    }
    traversed.push(make_pair(n, n->arr.size()));
    return traverseDown(traversed, n->directions[n->arr.size()], c);
}

Node *BPlus::split(Node *parent, Node* child, const int& child_ind){
    // Base cases. No split needed.
    if (child == nullptr) {
        return parent;
    }
    if (child->arr.size() < k) {
        return parent;
    }

    // Find middle of child.
    int mid = child->arr.size() / 2;
    Car mid_car = child->arr[mid];
    vector<Car> left, right;

    // Create nodes to left and right of the split
    for (int i = 0; i < mid; i++) {
        left.push_back(child->arr[i]);
    }
    // When child is leaf, middle is included. When child is not leaf. Middle is excluded form right
    // split.
    for (int i = mid + !(child->leaf); i < child->arr.size(); i++) {
        right.push_back(child->arr[i]);
    }

    Node* child_left = new Node(left, child->leaf);
    Node* child_right = new Node(right, child->leaf);
    // give the nodes directions if they are not leaf nodes
    if (!child->leaf) {
        for (int i = 0; i <= mid; i++) {
            child_left->directions.push_back(child->directions[i]);
        }
        for (int i = mid + 1; i < child->directions.size(); i++) {
            child_right->directions.push_back(child->directions[i]);
            }
        }
    child_left->prev = child->prev;
    child_left->next = child_right;
    child_right->prev = child_left;
    child_right->next = child->next;

    // update pointers of the nodes next to them
    if (child->leaf == 1) {
        if (child->prev != nullptr) {
            child->prev->next = child_left;
        }
        if (child->next != nullptr) {
            child->next->prev = child_right;
        }

    }

    // Check if children are new start or head of leaf linked list
    if (child_left->leaf == 1 && child_left->prev == nullptr) {
        head = child_left;
    }
    if (child_right->leaf == 1 && child_right->next == nullptr) {
        tail = child_right;
    }

    // Child is root. Create new root. Parent cannot be leaf node.
    if (root == child) {
        root = new Node(mid_car, 0);
        root->directions.push_back(child_left);
        root->directions.push_back(child_right);
    }
    else { // Child is not root. Insert middle and Node* to parent.
        // Delete pointer to old child
        parent->directions.erase(parent->directions.begin() + child_ind);

        // Insert middle of child into parent array. Then overwrite the pointer to old child.
        int i;
        for (i = 0; i < parent->arr.size(); i++) {
            if (operation(mid_car, parent->arr[i])) {
                parent->arr.insert(parent->arr.begin() + child_ind, mid_car);
                break;
            }
        }
        parent->directions.insert(parent->directions.begin() + i, child_left);
        parent->directions.insert(parent->directions.begin() + i + 1, child_right);
    }

    // Delete old child
    delete child;
    return parent;
}

void BPlus::insert(const Car &c) {
    // Base case.
    if (root == nullptr) {
        root = new Node(c, 1);
        head = root;
        tail = root;
        return;
    }

    // Insert new Car into desired node at appropriate position.
    stack<pair<Node*, int>> traversed;
    Node* point = traverseDown(traversed, root, c);
    int i;
    for (i = 0; i < point->arr.size(); i++) {
        if (operation(c, point->arr[i])) {
            break;
        }
    }
    point->arr.insert(point->arr.begin() + i, c);

    // Go up traversed nodes and split when necessary. If root node is leaf. Traversed is empty.
    Node* child = point;
    Node* parent = nullptr;
    int ind = 0;
    while (!traversed.empty()) {
        parent = traversed.top().first;
        ind = traversed.top().second;
        traversed.pop();
        split(parent, child, ind);
        child = parent;
    }
    // Replace root if necessary.
    Node* top = split(nullptr, child, 0);
    if (top != nullptr) {
        root = top;
    }
}

Node* BPlus::getHead() {
    return head;
}

Node *BPlus::getTail() {
    return tail;
}
