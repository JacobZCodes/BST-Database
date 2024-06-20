// Jacob Zamore
// Header file for a max-queue based on a node's depth 

#ifndef D_QUEUE_H
#define D_QUEUE_H

#include "DblList.h"
#include "TreeNode.h"  // Include the TreeNode class definition

template <typename T>
class DQueue {
public:
    DQueue(bool isMax); // Constructor
    virtual ~DQueue();  // Destructor
    void add(TreeNode<T>* node);  // Add a TreeNode to the priority queue
    TreeNode<T>* remove();  // Remove and return the TreeNode based on priority
    int size();  // Get the size of the priority queue
    bool isEmpty();  // Check if the priority queue is empty
    TreeNode<T>* peek();

private:
    bool isMaxQ;
    DblList<TreeNode<T>*>* m_list;

    // Define a custom comparison function to compare TreeNode objects based on m_depth
    bool compare(TreeNode<T>* node1, TreeNode<T>* node2) {
        if (isMaxQ) {
            return node1->m_depth < node2->m_depth; // For max priority (deepest nodes at front)
        } else {
            return node1->m_depth > node2->m_depth; // For min priority (shallowest nodes at front)
        }
    }
};

template <typename T>
DQueue<T>::DQueue(bool isMax) {
    isMaxQ = isMax;
    m_list = new DblList<TreeNode<T>*>();
}

template <typename T>
DQueue<T>::~DQueue() {
    delete m_list;
}

template <typename T>
TreeNode<T>* DQueue<T>::peek() {
    ListNode<TreeNode<T>*>* frontNode = m_list->getFront();
    if (frontNode != nullptr) {
        return frontNode->m_data;
    } else {
        return nullptr; // Return nullptr if the priority queue is empty
    }
}

template <typename T>
bool DQueue<T>::isEmpty() {
    return m_list->isEmpty();
}

template <typename T>
int DQueue<T>::size() {
    return m_list->getSize();
}

template <typename T>
void DQueue<T>::add(TreeNode<T>* node) {
    if (isEmpty()) {
        m_list->addFront(node);
    } else {
        int currIdx = 0;
        ListNode<TreeNode<T>*>* currNode = m_list->getFront();
        while (currNode != NULL && compare(node, currNode->m_data)) {
            ++currIdx;
            currNode = currNode->m_next;
        }
        m_list->add(currIdx, node);
    }
}

template <typename T>
TreeNode<T>* DQueue<T>::remove() {
    if (!isEmpty()) {
        return m_list->removeFront();
    } else {
        return nullptr; // Return nullptr if the priority queue is empty
    }
};

#endif
