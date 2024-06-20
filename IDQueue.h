// Jacob Zamore
// Header file for a min-queue based on a Student or Faculty member's ID

#ifndef ID_QUEUE_H
#define ID_QUEUE_H

#include "DblList.h"
#include "TreeNode.h"  // Include the TreeNode class definition

template <typename T>
class IDQueue {
public:
    IDQueue(bool isMin); // Constructor
    virtual ~IDQueue();  // Destructor
    void add(TreeNode<T>* node);  // Add a TreeNode to the priority queue
    TreeNode<T>* remove();  // Remove and return the TreeNode based on priority
    int size();  // Get the size of the priority queue
    bool isEmpty();  // Check if the priority queue is empty
    TreeNode<T>* peek();
    void clearQueue(); 
    bool contains(int id);

private:
    bool isMinQ;
    DblList<TreeNode<T>*>* m_list;
    // Define a custom comparison function to compare TreeNode objects based on ID value
    bool compare(TreeNode<T>* node1, TreeNode<T>* node2) {
        if (isMinQ) {
            return node1->getData()->getID() > node2->getData()->getID(); // Sort nodes (whose data consist of Student or Faculty records) by ascending ID
        } 
    }
};

template <typename T>
IDQueue<T>::IDQueue(bool isMin) {
    isMinQ = isMin;
    m_list = new DblList<TreeNode<T>*>();
}

template <typename T>
IDQueue<T>::~IDQueue() {
    delete m_list;
}

template <typename T>
bool IDQueue<T>::contains(int id) {
    ListNode<TreeNode<T>*>* currentNode = m_list->getFront();
    while (currentNode != NULL) {
        if (currentNode->m_data->getData()->getID() == id) {
            return true; // Found the TreeNode with the specified ID
        }
        currentNode = currentNode->m_next; // Move to the next node in the list
    }
    return false; // ID not found in the queue
}

template <typename T>
void IDQueue<T>::clearQueue() {
    while (!isEmpty()) {
        remove();
    }
}
template <typename T>
TreeNode<T>* IDQueue<T>::peek() {
    ListNode<TreeNode<T>*>* frontNode = m_list->getFront();
    if (frontNode != nullptr) {
        return frontNode->m_data;
    } else {
        return nullptr; // Return nullptr if the priority queue is empty
    }
}

template <typename T>
bool IDQueue<T>::isEmpty() {
    return m_list->isEmpty();
}

template <typename T>
int IDQueue<T>::size() {
    return m_list->getSize();
}

template <typename T>
void IDQueue<T>::add(TreeNode<T>* node) {
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
TreeNode<T>* IDQueue<T>::remove() {
    if (!isEmpty()) {
        return m_list->removeFront();
    } else {
        return nullptr; // Return nullptr if the priority queue is empty
    }
};

#endif
