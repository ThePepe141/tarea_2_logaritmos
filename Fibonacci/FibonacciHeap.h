#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <vector>
#include <cmath>
#include <unordered_map>

namespace FibonacciHeapStructure {

    struct FibonacciNode {
        int key;
        int degree;
        bool mark;
        FibonacciNode* parent;
        FibonacciNode* child;
        FibonacciNode* left;
        FibonacciNode* right;

        FibonacciNode(int k) : key(k), degree(0), mark(false), parent(nullptr), child(nullptr), left(this), right(this) {}
    };

    class FibonacciHeap {
    public:
        FibonacciHeap() : minNode(nullptr), n(0) {}

        FibonacciNode* MAKE_HEAP(); // creates and returns a new heap containing no elements.
        void INSERT(FibonacciNode* x); // inserts element x, whose key has already been filled in, into heap H
        FibonacciNode* MINIMUM(); // returns a pointer to the element in heap H whose key is minimum
        FibonacciNode* EXTRACT_MIN(); // deletes the element from heap H whose key is minimum, returning a pointer to the element.
        void UNION(FibonacciHeap* H2); // creates and returns a new heap that contains all the elements of heaps H1 and H2. Heaps H1 and H2 are “destroyed” by this operation.
        void DECREASE_KEY(FibonacciNode* x, int k); // assigns to element x within heap H the new key value k, which we assume to be no greater than its current key value
        void DELETE(FibonacciNode* x); // deletes element x from heap H.

    private:
        FibonacciNode* minNode; // Pointer to the node with the minimum key
        int n; // Number of nodes in the heap

        void CONSOLIDATE();
        void LINK(FibonacciNode* y, FibonacciNode* x);
        void CUT(FibonacciNode* x, FibonacciNode* y);
        void CASCADING_CUT(FibonacciNode* y);

        void ADD_NODE_TO_ROOT_LIST(FibonacciNode* x);
        void REMOVE_NODE_FROM_ROOT_LIST(FibonacciNode* x);
    };

}

#endif
