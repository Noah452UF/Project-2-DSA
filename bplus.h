// Author: Carter Veit
// Description: Declares prototype for bplus class for use
//              in project 2.
//
// Last Modified: November 3, 2026
// Last Modified By: Carter Veit

#ifndef PROJECT_2_DSA_BPLUS_H
#define PROJECT_2_DSA_BPLUS_H

#include <cars.h>
#include <vector>

struct Node {
    vector<Car> arr;
    vector<Node*> directions;
    Node* parent;
    Node* next;
    Node* prev;
    bool leaf;
    Node(const Car& n);
    Node(vector<Car> arr_);
};

class BPlus {
private:
    bool (*operation)(Car,Car);
    Node* root;
    Node* head;
    Node* tail;
    int k;

    Node* traverseDown(Node* root, const Car& n);
    Node* split(Node* root);
public:
    BPlus(bool (*operation_)(Car,Car), int k_ = 3);
    void insert(const Car& n);
    void getHead();
    void getTail();
};

#endif //PROJECT_2_DSA_BPLUS_H