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
    /**
     * @brief Paramaterized constructor for a B+ tree of Car structure utilizing passed function pointer.
     *
     * Constructor accepts a function pointer with two Car struct parameters and a boolean return.
     * When the return of the function is 1, the first Car input will sort towards the left of the tree.
     * When the return of the function is 0, the second Car input will sort towards the right of the heap.
     *
     * @param operation_ Function pointer utilized for sorting insertions
     * @param k_ Number of permitted branches from node. Default value of 3.
     */
    BPlus(bool (*operation_)(Car,Car), int k_ = 3);
    /**
     * @brief Destructor.
     *
     * Uses postOrder traversal to delete all nodes of tree.
     */
    ~BPlus();
    /**
     * @brief Inserts Car c into tree according to function defiend at constructor.
     *
     * Inserts new object into tree, and then checks all traversed nodes to determine if a split
     * is necessary.
     *
     * @param c Car object to be inserted.
     */
    void insert(const Car& c);
    /**
     * @brief Returns head (leftmost node) of leaf linked-list.
     *
     * @return Head of linked list.
     */
    Node* getHead();
    /**
     * @brief Returns tail (rightmost node) of leaf linked-list.
     *
     * @return Tail of linked list.
     */
    Node* getTail();
};

#endif //PROJECT_2_DSA_BPLUS_H