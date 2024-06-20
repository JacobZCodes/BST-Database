// Jacob Zamore
// Header file for a tree node class representing a node in our BST
#ifndef TREENODE_H
#define TREENODE_H

#include <cstdlib>

template <typename T>
class TreeNode{
    public:
        TreeNode(T data);
        virtual ~TreeNode();
        TreeNode(const TreeNode<T>& other); // copy constructor only implemented for sentinel node
        T getData();
        int m_depth;
        

template <typename S>
friend class BST;
        T m_data;
        TreeNode<T>* m_left;
        TreeNode<T>* m_right; 
};

template <typename T>
TreeNode<T>::TreeNode(T data){
    m_data = data;
    m_left = NULL;
    m_right = NULL;
}

template <typename T>
TreeNode<T>::~TreeNode(){
    if(m_left != NULL){
        delete m_left;
    }
    if(m_right != NULL){
        delete m_right;
    }
}

template <typename T>
T TreeNode<T>::getData(){
    return m_data;
}
#endif