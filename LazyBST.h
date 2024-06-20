// Jacob Zamore
// Header file for a self-balancing Binary Search Tree

#ifndef LAZYBST_H
#define LAZYBST_H
#include "Student.h"
#include "Faculty.h"
#include <typeinfo>
#include "DQueue.h"
#include "IDQueue.h"
#include "TreeNode.h"
#include <type_traits>
#include <typeinfo>
#include <iostream>
using namespace std;

template <typename T>
class LazyBST{
    public:
        LazyBST();
        virtual ~LazyBST();
        int getSize();
        void insert(T data);
        void remove(T data);
        bool contains(T data);
        void printTreeInOrder();
        void printTreePostOrder();
        void setDepth(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        T getMin();
        T getMax();
        TreeNode<T>* getRoot();
        DQueue<T>* getRightSubtree();
        DQueue<T>* getLeftSubtree();
        IDQueue<T>* getNodes();
        void checkAndRebalanceTree();
        void removeNodeFromQueue(T d);
        TreeNode<T>* getNodeGivenID(int id);

    private:
        TreeNode<T>* m_root;
        TreeNode<T>* m_sentinelNode; // Contains a unique ID number and placed at the end of a dynamic array so that findSizeArray knows when to stop and doesn't go out of bounds
        int m_size;
        bool isOdd; 
        void insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode);
        bool containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode);
        void printTreeInOrderHelper(TreeNode<T>* subTreeRoot);
        void printTreePostOrderHelper(TreeNode<T>* subTreeRoot);
        T getMinHelper(TreeNode<T>* subTreeRoot);
        T getMaxHelper(TreeNode<T>* subTreeRoot);
        void findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent);
        TreeNode<T>* getSuccessor(TreeNode<T>* rightChild);
        DQueue<T>* m_leftSubtree;
        DQueue<T>* m_rightSubtree; // Max queues to keep track of nodes in left + right subtree based on depth
        IDQueue<T>* m_nodes; // IDQueue is a min queue
        TreeNode<T>** processNodes();
        TreeNode<T>** m_processedNodes; // Stores m_nodes as an array
        int findSizeSubtreeSubarray();
        void rebalanceTree();
        void displayTree();
        int rebalanceCounter = 0;
        int findMedianIndex(int size);
        int findSizeArray(TreeNode<T>** myArray);
        TreeNode<T>** getMedians(TreeNode<T>** myArray);
        
};
template <typename T>
LazyBST<T>::LazyBST(){
    m_root = NULL;
    m_size = 0;
    m_leftSubtree = new DQueue<T>(true); // isMax = true
    m_rightSubtree = new DQueue<T>(true); // isMax = true
    m_nodes = new IDQueue<T>(true);  // isMin = true
}

template <typename T>
TreeNode<T>* LazyBST<T>::getNodeGivenID(int id) {
    IDQueue<T> personIDs(true);
    TreeNode<T>* tempNode;
    TreeNode<T>* targetNode;
    while (!m_nodes->isEmpty()) {
        tempNode = m_nodes->remove();
        if (id == tempNode->getData()->getID()) {
            targetNode = tempNode;
        }
        personIDs.add(tempNode);
    }
    while (!personIDs.isEmpty()) {
        m_nodes->add(personIDs.remove());
    }
    return targetNode;
}


// Specialize the constructor for Student* - for m_sentinelNode
template <>
LazyBST<Student*>::LazyBST() {
    m_root = nullptr;
    m_size = 0;
    m_leftSubtree = new DQueue<Student*>(true); // isMax = true
    m_rightSubtree = new DQueue<Student*>(true); // isMax = true
    m_nodes = new IDQueue<Student*>(true); // isMin = true

    Student* defaultStudent = new Student();
    m_sentinelNode = new TreeNode<Student*>(defaultStudent);
    static_cast<Student*>(m_sentinelNode->getData())->setID(11);
}

// Specialize the constructor for Faculty* -  - for m_sentinelNode
template <>
LazyBST<Faculty*>::LazyBST() {
    m_root = nullptr;
    m_size = 0;
    m_leftSubtree = new DQueue<Faculty*>(true); // isMax = true
    m_rightSubtree = new DQueue<Faculty*>(true); // isMax = true
    m_nodes = new IDQueue<Faculty*>(true); // isMin = true

    Faculty* defaultFaculty = new Faculty();
    m_sentinelNode = new TreeNode<Faculty*>(defaultFaculty);
    static_cast<Faculty*>(m_sentinelNode->getData())->setID(11);
}

template <typename T>
LazyBST<T>::~LazyBST(){
    //free memory
    if(m_root != NULL){
        delete m_root;
  }
}

template <typename T>
// Returns an array filled all the gathered medians from our right subTree subArray and left subTree subArray (these represent everything to the left + right of our newly found root)
TreeNode<T>** LazyBST<T>::getMedians(TreeNode<T>** myArray) {
    int initialSize = findSizeArray(myArray); // static
    int size = findSizeArray(myArray); // changes
    TreeNode<T>** loggedMedians = new TreeNode<T>*[size]; // statis
    TreeNode<T>** newArray = myArray;
    int currentLoggedMediansIndex = 0; // changes
    while (size != 0) {
        loggedMedians[currentLoggedMediansIndex] = newArray[findMedianIndex(size)];
        currentLoggedMediansIndex++;
        size--;
        newArray = new TreeNode<T>*[size];
        // newArray will house our array without the median we just found
        int currentNewArrayIndex = 0;
        // Add to the newArray only those values which have not been logged in loggedMedians array
        for (int i =0; i<initialSize; ++i) {
            bool addToNewArray = true;
            // Checks if element to be added to newArray already in loggedMedians or not
            for (int j=0; j<currentLoggedMediansIndex; j++) {
                if (myArray[i] == loggedMedians[j]) {
                    for (int z=0; z<currentLoggedMediansIndex; z++) {
                    }
                    addToNewArray = false;
                }
            }
            if (addToNewArray) {
                newArray[currentNewArrayIndex] = myArray[i];
                currentNewArrayIndex++;
            }
        }
    }
    return loggedMedians;
}


template <typename T>
int LazyBST<T>::findSizeArray(TreeNode<T>** myArray) {
    int size = 0;
    int tempIndex = 0;  
    while (myArray[tempIndex]->getData()->getID() != 11) {
        tempIndex++;
        size++;
    }
    return size;
}

template <typename T>
int LazyBST<T>::findMedianIndex(int size) {
    if (size % 2 != 0) { // Odd
        return size / 2;
    }
    else if (size % 2 == 0){ // Even
        return (size / 2) - 1;
    }
}


template <typename T>
void LazyBST<T>::displayTree() {
    string dir;
    for (int i=0; i<m_size; i++) {
    }
}
template <typename T>
void LazyBST<T>::rebalanceTree() {
    // Establish new root of our new tree
    TreeNode<T>* newRoot = m_processedNodes[findMedianIndex(m_size)];
    int nodeDataIDToSplitOn = m_processedNodes[findMedianIndex(m_size)]->getData()->getID();
    bool startPopulatingRightSubtreeSubarray = false;
    // If we have an odd number of nodes, our subtree subarrays will be of equal size
    // If we have an even number of nodes, our right subtree subarray will be of size (sizeBST/2) 
    // and our left subtree subarray will be of size ((sizeBST/2) - 1)
    TreeNode<T>** leftSubTreeSubArray;
    TreeNode<T>** rightSubTreeSubArray;
    int leftSubTreeSubArraySize;
    int rightSubTreeSubArraySize;
    if (m_size%2!=0) {
        leftSubTreeSubArraySize = getSize() / 2;
        rightSubTreeSubArraySize = getSize() / 2;
        leftSubTreeSubArray = new TreeNode<T>*[leftSubTreeSubArraySize+1]; 
        rightSubTreeSubArray = new TreeNode<T>*[rightSubTreeSubArraySize+1]; 
    }
    else if (m_size%2==0){
        rightSubTreeSubArraySize = getSize() / 2;
        leftSubTreeSubArraySize = (getSize() / 2) - 1;
        leftSubTreeSubArray = new TreeNode<T>*[leftSubTreeSubArraySize+1];
        rightSubTreeSubArray = new TreeNode<T>*[rightSubTreeSubArraySize+1]; 
    }
    int currentIndexLeftSubTreeSubArray = 0;
    int currentIndexLRightSubTreeSubArray = 0;
    for (int i = 0; i < getSize(); i++) {
        if (!startPopulatingRightSubtreeSubarray) {
            if (m_processedNodes[i]->getData()->getID() == nodeDataIDToSplitOn) {
                startPopulatingRightSubtreeSubarray = true;
                continue;
            }
            leftSubTreeSubArray[currentIndexLeftSubTreeSubArray] = m_processedNodes[i];
            currentIndexLeftSubTreeSubArray++;
        }
        else if (startPopulatingRightSubtreeSubarray) {
            rightSubTreeSubArray[currentIndexLRightSubTreeSubArray] = m_processedNodes[i];
            currentIndexLRightSubTreeSubArray++;
        }
    }
    leftSubTreeSubArray[leftSubTreeSubArraySize] = m_sentinelNode; // Implant sentinelNode so that findSizeArray can function properly
    rightSubTreeSubArray[rightSubTreeSubArraySize] = m_sentinelNode;
    m_root = NULL;
    m_size = 0;
    m_leftSubtree = new DQueue<T>(true); // isMax = true
    m_rightSubtree = new DQueue<T>(true); // isMax = true
    m_nodes = new IDQueue<T>(true);  // isMin = true
    delete[] m_processedNodes; 
    // Begin insertion process (creation of new tree) with insertion of new root
    insert(newRoot->getData());
    // Get medians of leftSubTreeSubArray and rightSubTreeSubArray
    TreeNode<T>** leftMedians = getMedians(leftSubTreeSubArray);
    TreeNode<T>** rightMedians = getMedians(rightSubTreeSubArray);
    // Insert left median, insert right median until all medians are inserted
    int size1 = leftSubTreeSubArraySize;
    int size2 = rightSubTreeSubArraySize;
    int i = 0;
    int index1 = 0;
    int index2 = 0;
    while (index1 < size1 || index2 < size2) {
        if (i % 2 == 0 && index1 < size1) {
            insert(leftMedians[index1]->getData());
            index1++;
        } else if (index2 < size2) {
            insert(rightMedians[index2]->getData());
            index2++;
        }
        i++;
    }
    delete[] leftMedians;
    delete[] rightMedians;
    rebalanceCounter++;
}
    
template <typename T>
IDQueue<T>* LazyBST<T>::getNodes() {
    return m_nodes;
}

template <typename T>
TreeNode<T>** LazyBST<T>::processNodes() {
    int sizeLBST = getSize();
    TreeNode<T>** tempArray = new TreeNode<T>*[sizeLBST]; 
    for (int i = 0; i<sizeLBST; i++) {
        tempArray[i] = m_nodes->remove();
    }
    for (int i = 0; i<sizeLBST; i++) {
        m_nodes->add(tempArray[i]);
    }
    return tempArray;
}

template <typename T>
void LazyBST<T>::removeNodeFromQueue(T d) {
    // Create a temporary queue to hold nodes except the one to be removed
    IDQueue<T>* tempQueue = new IDQueue<T>(true);
    TreeNode<T>* tempNode;

    while (!m_nodes->isEmpty()) {
        tempNode = m_nodes->remove();
        if (tempNode->getData() != d) {
            tempQueue->add(tempNode);
        }
    }

    // Swap m_nodes with tempQueue
    delete m_nodes;
    m_nodes = tempQueue;
}

template <typename T>
DQueue<T>* LazyBST<T>::getLeftSubtree(){
    return m_leftSubtree;
}

template <typename T>
DQueue<T>* LazyBST<T>::getRightSubtree(){
    return m_rightSubtree;
}


template <typename T>
TreeNode<T>* LazyBST<T>::getRoot() {
    return m_root;
}

template <typename T>
int LazyBST<T>::getSize(){
    return m_size;
}

template <typename T>
void LazyBST<T>::insert(T data) {
    TreeNode<T>* newNode = new TreeNode<T>(data);
    insertHelper(m_root, newNode);
    ++m_size;
    // Add node to m_nodes so that it can be sorted by ascending ID order
    m_nodes->add(newNode);
    // Process m_nodes into a dynamic array called m_processedNodes
    m_processedNodes = processNodes();
    // Print all nodes to screen
    
    // Establish conditions for find target
    TreeNode<T>* target = NULL;
    TreeNode<T>* parent = NULL;
    target = m_root;
    findTarget(newNode->m_data,target, parent);
    // Set depth
    if (parent == NULL) {
        target->m_depth = 0;
    }
    else if (parent != NULL) {
        target->m_depth = parent->m_depth + 1;
    }
    // Add node to subtree left or subtree right
    if (target->m_data->getID() > m_root->m_data->getID()) {
        m_rightSubtree->add(target);
    }
    else if (target->m_data->getID() < m_root->m_data->getID()) {
        m_leftSubtree->add(target);
    }
    checkAndRebalanceTree();
}
template <typename T>
void LazyBST<T>::insertHelper(TreeNode<T>*& subTreeRoot, TreeNode<T>* newNode){
    if(subTreeRoot == NULL){
        subTreeRoot = newNode; //pointer swap
    }else if(newNode->m_data->getID() < subTreeRoot->m_data->getID()){
        insertHelper(subTreeRoot->m_left, newNode);
    }else if(newNode->m_data->getID() > subTreeRoot->m_data->getID()){
        insertHelper(subTreeRoot->m_right, newNode);
    }
}

template <typename T>
void LazyBST<T>::checkAndRebalanceTree() {
    if (!m_rightSubtree->isEmpty() && !m_leftSubtree->isEmpty()) {
        int rightDepth = m_rightSubtree->peek()->m_depth;
        int leftDepth = m_leftSubtree->peek()->m_depth;
        float imbalance = static_cast<float>(rightDepth) - leftDepth;

        if (imbalance > 1.5 || imbalance < -1.5) {
            rebalanceTree();
        }
    }
    else if (m_leftSubtree->isEmpty() && !m_rightSubtree->isEmpty() && m_rightSubtree->peek()->m_depth >= 2) {
        rebalanceTree();
    }
    else if (!m_leftSubtree->isEmpty() && m_rightSubtree->isEmpty() && m_leftSubtree->peek()->m_depth >= 2) {
        rebalanceTree();
    }
}

template <typename T>
bool LazyBST<T>::contains(T data){
    TreeNode<T>* newNode = new TreeNode<T>(data);
    return containsHelper(m_root, newNode);
}

template <typename T>
bool LazyBST<T>::containsHelper(TreeNode<T>* subTreeRoot, TreeNode<T>* newNode){
    if(subTreeRoot == NULL){
        return false;
    }else if(newNode->m_data == subTreeRoot->m_data){
        return true;
    }else if(newNode->m_data < subTreeRoot->m_data){
        return containsHelper(subTreeRoot->m_left, newNode);
    }else{
        return containsHelper(subTreeRoot->m_right, newNode);
    }
}

template <typename T>
void LazyBST<T>::printTreeInOrder(){
    printTreeInOrderHelper(m_root);
}

template <typename T>
void LazyBST<T>::printTreeInOrderHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot != NULL){
        printTreeInOrderHelper(subTreeRoot -> m_left);
        printTreeInOrderHelper(subTreeRoot -> m_right);
    }
}

template <typename T>
void LazyBST<T>::printTreePostOrder(){
    printTreePostOrderHelper(m_root);
}

template <typename T>
void LazyBST<T>::printTreePostOrderHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot != NULL){
        printTreePostOrderHelper(subTreeRoot->m_left);
        printTreePostOrderHelper(subTreeRoot->m_right);
    }
}

template <typename T>
T LazyBST<T>::getMin(){
    //check if empty
    return getMinHelper(m_root);
}

template <typename T>
T LazyBST<T>::getMinHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot->m_left == NULL){
        return subTreeRoot->m_data;
    }else{
        return getMinHelper(subTreeRoot->m_left);
    }
}

template <typename T>
T LazyBST<T>::getMax(){
    //check if empty
    return getMaxHelper(m_root);
}

template <typename T>
T LazyBST<T>::getMaxHelper(TreeNode<T>* subTreeRoot){
    if(subTreeRoot->m_right == NULL){
        return subTreeRoot->m_data;
    }else{
        return getMaxHelper(subTreeRoot->m_right);
    }
}

template <typename T>
void LazyBST<T>::findTarget(T key, TreeNode<T>*& target, TreeNode<T>*& parent){
    // key, root, null
    while(target != NULL && target->m_data != key){
        parent = target;
        if(key->getID() < target->m_data->getID()){
            target = target->m_left;
        }else{
            target = target->m_right;
        }
    }
    if (target == NULL) {
    }
}

template <typename T>
TreeNode<T>* LazyBST<T>::getSuccessor(TreeNode<T>* rightChild){
    while(rightChild->m_left != NULL){
        rightChild = rightChild->m_left;
    }
    return rightChild;
}

template <typename T>
void LazyBST<T>::remove(T d){
    //TODO - check if empty 
    TreeNode<T>* target = NULL;
    TreeNode<T>* parent = NULL;
    target = m_root;
    findTarget(d,target, parent);
    if(target == NULL){ //not in the tree, nothing to do
        return;
    }
    if(target->m_left == NULL && target->m_right == NULL){ //no children, it's a leaf
        if(target == m_root){
            m_root = NULL;
        }else{ //it's not the root
            if(target == parent->m_left){
                parent->m_left = NULL;
            }else{
                parent->m_right = NULL;
            }
        }
    }else if(target->m_left != NULL && target->m_right !=NULL){ // 2 child case
        TreeNode<T>* suc = getSuccessor(target->m_right);
        T value = suc->m_data;
        remove(value);
        target->m_data = value;
    }else{ // 1 child case
        TreeNode<T>* child;
        if(target->m_left != NULL){
            child = target->m_left;
        }else{
            child = target->m_right;
        }
        if(target == m_root){
            m_root = child;
        }else{
            if(target == parent->m_left){
                parent->m_left = child;
            }else{
                parent->m_right = child;
            }
        }
    }
    --m_size;
    // Inverse of insertion - remove node from m_nodes, update m_processedNodes to reflect the updated m_nodes, and check if the tree needs rebalancing
    removeNodeFromQueue(d);
    m_processedNodes = processNodes();
    checkAndRebalanceTree();
}



#endif