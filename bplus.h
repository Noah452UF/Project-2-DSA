// Author: Carter Veit
// Description: Declares prototype for bplus class for use
//              in project 2.
//
// Last Modified: November 3, 2026
// Last Modified By: Carter Veit

#ifndef PROJECT_2_DSA_BPLUS_H
#define PROJECT_2_DSA_BPLUS_H

#include "cars.h"
#include <vector>
#include <stack>

struct Node {
    vector<Car> arr;
    vector<Node*> directions;
    Node* parent;
    Node* next;
    Node* prev;
    bool leaf;
    Node(const bool& leaf_);
    Node(const Car& c, const bool& leaf_);
    Node(vector<Car> arr_, const bool& leaf_);
};

class BPlus {
private:
    bool (*operation)(Car,Car);
    Node* root;
    Node* head;
    Node* tail;
    int k;

    void postOrderDelete(Node* n);
    Node* traverseDown(stack<pair<Node*, int>>& traversed, Node* n, const Car& c);
    Node* split(Node* parent, Node* child, const int& child_ind);
public:
    BPlus(bool (*operation_)(Car,Car), int k_ = 3);
    ~BPlus();
    void insert(const Car& c);
    void getHead();
    void getTail();
};

#endif //PROJECT_2_DSA_BPLUS_H