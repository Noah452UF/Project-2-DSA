// Author: Carter Veit
// Description: Declares prototype for cars structure for use
//              in project 2.
//
// Last Modified: November 2, 2026
// Last Modified By: Carter Veit

#ifndef PROJECT_2_DSA_HEAP_H
#define PROJECT_2_DSA_HEAP_H

#include <vector>
#include "cars.h"

class Heap {
private:
    bool (*operation)(Car,Car);
    vector<Car> arr;

    void heapify_down(const int& root);
    void heapify_up(const int& node);
public:
    /**
     * @brief Paramaterized constructor for a heap of Car structure utilizing passed function pointer.
     *
     * Constructor accepts a function pointer with two Car struct parameters and a boolean return.
     * When the return of the function is 1, the first Car input will sort towards the top of the heap.
     * When the return of the function is 0, the second Car input will sort towards the top of the heap.
     *
     * @param operation_ Function pointer utilized for sorting insertions
     */
    Heap(bool (*operation_)(Car,Car));
    /**
    * @brief Inserts car object into the heap
    *
    * Inserts new object to the end of the heap, and then heapifies up
    * according to the function passed in the constructor/
    *
    * @param n Car object to be inserted
    */
    void insert(Car n);
    /**
    * @brief Extracts car object from top of heap.
    *
    * Removes object from top of heap, replacing it with the last object in the heap
    * before heapifying down to sort heap.
    *
    * @return Car object at top of heap.
    */
    Car extract(void);
};

#endif //PROJECT_2_DSA_HEAP_H