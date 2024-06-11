#include "FibonacciHeap.h"
#include <iostream>
#include <cmath>
#include <limits>

namespace FibonacciHeapStructure {

    FibonacciHeap* MAKE_HEAP() {
        FibonacciHeap* H = new FibonacciHeap();
        return H;
    }

    void FibonacciHeap::INSERT(FibonacciNode* x){
        x->degree = 0;
        x->parent = nullptr;
        x->child = nullptr;
        x->mark = false;

        if (minNode == nullptr) {
            x->left = x;
            x->right = x;
            minNode = x;
        } else {
            x->left = minNode;
            x->right = minNode->right;
            minNode->right->left = x;
            minNode->right = x;
            if (x->key < minNode->key)
                minNode = x;
        }

        n++;
    } 

    FibonacciNode* FibonacciHeap::MINIMUM() {

        return minNode;
    }

    FibonacciNode* FibonacciHeap::EXTRACT_MIN(){
        FibonacciNode* zeta = minNode;
        if (zeta != nullptr) {
            FibonacciNode* child = zeta->child;
            FibonacciNode* temp;

            while (child != nullptr) {
                temp = child->right;
                ADD_NODE_TO_ROOT_LIST(child);
                child->parent = nullptr;
                child = temp;
            }

            REMOVE_NODE_FROM_ROOT_LIST(zeta);
            if (zeta == zeta->right) {
                minNode = nullptr;
            } else {
                minNode = zeta->right;
                CONSOLIDATE();
            }
            n--;
        }
        return zeta;
    }

    void FibonacciHeap::UNION(FibonacciHeap* H2){
        FibonacciHeap* H = new FibonacciHeap();

        H->minNode = minNode;
        if (H->minNode != nullptr && H2->minNode != nullptr) {
            FibonacciNode* temp = H->minNode->right;
            H->minNode->right = H2->minNode;
            H2->minNode->left->right = temp;
            temp->left = H2->minNode->left;
            H2->minNode->left = H->minNode;
        } else if (H2->minNode != nullptr) {
            H->minNode = H2->minNode;
        }

        if (minNode == nullptr || (H2->minNode != nullptr && H2->minNode->key < minNode->key))
            H->minNode = H2->minNode;

        H->n += H2->n;
    }

    void FibonacciHeap::DECREASE_KEY(FibonacciNode* x, int k) {
        if (k > x->key) {
            throw std::invalid_argument("New key is greater than current key");
        }

        x->key = k;
        FibonacciNode* y = x->parent;

        if (y != nullptr && x->key < y->key) {
            CUT(x, y);
            CASCADING_CUT(y);
        }

        if (minNode != nullptr && x->key < minNode->key) {
            minNode = x;
        }
    }

    void FibonacciHeap::DELETE(FibonacciNode* x) {
        DECREASE_KEY(x, std::numeric_limits<int>::min());
        EXTRACT_MIN();
    }

    void FibonacciHeap::CONSOLIDATE() {
        int maxDegree = static_cast<int>(log2(n)) + 1;
        std::vector<FibonacciNode*> A(maxDegree, nullptr);

        std::vector<FibonacciNode*> rootList;
        FibonacciNode* x = minNode;
        if (x != nullptr) {
            do {
                rootList.push_back(x);
                x = x->right;
            } while (x != minNode);
        }

        for (auto w : rootList) {
            x = w;
            int d = x->degree;
            while (A[d] != nullptr) {
                FibonacciNode* y = A[d];
                if (x->key > y->key) {
                    std::swap(x, y);
                }
                LINK(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
        }

        minNode = nullptr;
        for (auto y : A) {
            if (y != nullptr) {
                if (minNode == nullptr) {
                    minNode = y;
                    minNode->left = minNode;
                    minNode->right = minNode;
                } else {
                    y->left = minNode;
                    y->right = minNode->right;
                    minNode->right->left = y;
                    minNode->right = y;
                    if (y->key < minNode->key) {
                        minNode = y;
                    }
                }
            }
        }
    }

    void FibonacciHeap::LINK(FibonacciNode* y, FibonacciNode* x) {
        REMOVE_NODE_FROM_ROOT_LIST(y);
        y->parent = x;
        if (x->child == nullptr) {
            x->child = y;
            y->left = y;
            y->right = y;
        } else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right->left = y;
            x->child->right = y;
        }
        x->degree++;
        y->mark = false;
    }

    void FibonacciHeap::CUT(FibonacciNode* x, FibonacciNode* y) {
        if (x->right == x) {
            y->child = nullptr;
        } else {
            x->left->right = x->right;
            x->right->left = x->left;
            if (y->child == x) {
                y->child = x->right;
            }
        }
        y->degree--;
        ADD_NODE_TO_ROOT_LIST(x);
        x->parent = nullptr;
        x->mark = false;
    }

    void FibonacciHeap::CASCADING_CUT(FibonacciNode* y) {
        FibonacciNode* zeta = y->parent;
        if (zeta != nullptr) {
            if (!y->mark) {
                y->mark = true;
            } else {
                CUT(y, zeta);
                CASCADING_CUT(zeta);
            }
        }
    }

    void FibonacciHeap::ADD_NODE_TO_ROOT_LIST(FibonacciNode* x) {
        if (minNode == nullptr) {
            x->left = x;
            x->right = x;
            minNode = x;
        } else {
            x->left = minNode;
            x->right = minNode->right;
            minNode->right->left = x;
            minNode->right = x;
        }
    }

    void FibonacciHeap::REMOVE_NODE_FROM_ROOT_LIST(FibonacciNode* x) {
        if (x->right == x) {
            minNode = nullptr;
        } else {
            x->left->right = x->right;
            x->right->left = x->left;
            if (minNode == x) {
                minNode = x->right;
            }
        }
        x->left = x;
        x->right = x;
    }

}
