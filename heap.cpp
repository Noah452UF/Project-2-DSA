// Author: Carter Veit
// Description: Declares prototype for cars structure for use
//              in project 2.
//
// Last Modified: November 2, 2026
// Last Modified By: Carter Veit

#include "heap.h"

Heap::Heap(bool (*operation_)(Car, Car)) {
    operation = operation_;
}

void Heap::heapify_down(const int &root) {
    // Check for base case.
    if (root >= arr.size()-1) {
        return;
    }

    // Obtain child nodes
    int c1 = root * 2 + 1;
    int c2 = root * 2 + 2;

    // Determine if swap is necessary, and if so which one.
    bool swap = operation(arr[root], arr[c1]) || operation(arr[root], arr[c2]);
    bool left = operation(arr[c1], arr[c2]);

    // Swap logic, and further heapify down
    if (!swap) {
        return;
    }

    if (left) {
        Car temp = arr[root];
        arr[root] = arr[c1];
        arr[c1] = temp;
        heapify_down(c1);
    }
    else {
        Car temp = arr[root];
        arr[root] = arr[c2];
        arr[c2] = temp;
        heapify_down(c2);
    }
}

void Heap::heapify_up(const int &node) {
    // Base case
    if (node == 0) {
        return;
    }

    // Obtain parent node
    int p = (node - 1) / 2;

    // Determine if swap is necessary, and then implement swap.
    if (operation(arr[node], arr[p])) {
        Car temp = arr[node];
        arr[node] = arr[p];
        arr[p] = temp;
        heapify_up(p);
    }
}

void Heap::insert(Car n) {
    // Add new object to end of vector.
    arr.push_back(n);
    // Heapify up to sort new object into the heap
    heapify_up(arr.size() - 1);
}

Car Heap::extract() {
    // Store object to be returned
    Car top = arr[0];
    // Swap first and last objects of the heap, and then remove the extracted object.
    arr[0] = arr[arr.size() - 1];
    arr.pop_back();

    // Heapify down to sort heap.
    heapify_down(0);

    // Return extarcted top of heap.
    return top;
}
