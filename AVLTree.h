#ifndef __BSTREE_H__
#define __BSTREE_H__

#include "Node.h"
#include "AVLTree.h"

class AVLTree {
    private:
        Node* root;
        void destroyTree(Node*);
        //Private helper for printout out balance factors of node
        void printBalanceFactors(Node*);
        //Get height of a node
        int returnHeight(Node*);
        //Rotate left at node
        void rotateLeft(Node*);
        //Rotate right at node
        void rotateRight(Node *);
        void setLeft(Node*, Node*);
        void setRight(Node*, Node*);
        void rotate(Node*);
        //Helper for visualize tree
        void visualizeTree(ofstream&, Node *);
        //Copy constructor 
        AVLTree(AVLTree*);
        //Assignment operator
        AVLTree* operator=(AVLTree* rhs);

    public:
        //Default Constructor;
        AVLTree();
        //Destructor;
        ~AVLTree();
        //Insertion
        void insert(const string&);
        //Print Balacnce factors of all nodes
        void printBalanceFactors();
        //Calculate balance factor of a given node;
        int balanceFactor(Node*);
        //generates a file to visual the avl tree
        void visualizeTree(const string&);
};

#endif // __BSTREE_H__
