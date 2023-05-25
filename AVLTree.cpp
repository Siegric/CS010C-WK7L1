#include <iostream>
#include <fstream>

#include "AVLTree.h" 
#include "Node.h"

using namespace std;

//Default constructor
AVLTree::AVLTree(){
    root = nullptr;
}
//Default destroctor
AVLTree::~AVLTree(){
    destroyTree(root);
}
//Helper to eradicate all nodes from tree
void AVLTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
//Cunny insertion 
void AVLTree::insert(const string &inStr){
    Node* node = new Node(inStr);
    Node* currNode = nullptr;
    //Case 1: Tree is empty
    if(root == nullptr){
        root = node;
    }
    //Case 2: Tree is not empty
    else{
        //While loop to find point of insertion
        currNode = root;
        while(currNode != nullptr){
            if(node->data == currNode->data){
                currNode->count += 1;
                currNode = nullptr;
            }
            else if(node->data < currNode->data){
                if(currNode->left != nullptr){
                    currNode = currNode->left;
                }
                else{
                    currNode->left = node;
                    node->parent = currNode;
                    currNode = nullptr;
                }
            }
            else{
                if(currNode->right != nullptr){
                    currNode = currNode->right;
                }
                else{
                    currNode->right = node;
                    node->parent = currNode;
                    currNode = nullptr;
                }
            }
        }
    }
    //Maintains AVL properties by rotating until reaching root again
    node = node->parent;
    while (node) { 
        rotate(node); 
        node = node->parent; 
    }
}

void AVLTree::printBalanceFactors(){
    printBalanceFactors(root);
    cout << endl;
}

//Calculates balance factor of given node by simply finding the difference between the left and right subtree of said node
int AVLTree::balanceFactor(Node* node){
    return ((returnHeight(node->left)) - (returnHeight(node->right)));
}

void AVLTree::printBalanceFactors(Node* node){
    if(node != nullptr){
        printBalanceFactors(node->left);
        cout << node->data << "(" << balanceFactor(node) << "), "; 
        printBalanceFactors(node->right); 
    }
}
//Helper to recursively find the height of a given node
int AVLTree::returnHeight(Node* node){
    if (node == nullptr){
       return -1; //Indicates error due to empty tree
    }
    //Finds the height of left and right subtrees
    int leftHeight = returnHeight(node->left);
    int rightHeight = returnHeight(node->right);
    //Compares the left and right subtree heights to find the actual height
    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }
    else{
        return rightHeight + 1;
    }
} 
//Rotates left at given node
void AVLTree::rotateLeft(Node* node){
    Node* rightLnode = node->right->left;

    if(node->parent != nullptr) { 
        if(node->parent->left == node){
            setLeft(node->parent, node->right);
        }
        else if(node->parent->right == node){
            setRight(node->parent, node->right);
        }
    }
    else{
      root = node->right;
      root->parent = nullptr;
    } 
    setLeft(node->right, node);
    setRight(node, rightLnode);
}
//Rotates right at given node
void AVLTree::rotateRight(Node *node) {
    Node* leftRnode = node->left->right;

    if(node->parent != nullptr) { 
        if(node->parent->left == node){
            setLeft(node->parent, node->left);
        }
        else if(node->parent->right == node){
            setRight(node->parent, node->left);
        }
    }
    else{
      root = node->left;
      root->parent = nullptr;
    } 
    setRight(node->left, node);
    setLeft(node, leftRnode);
}  

void AVLTree::setLeft(Node* parentNode, Node* childNode){
    parentNode->left = childNode;
    if(childNode != nullptr){
        childNode->parent = parentNode;
    }
}

void AVLTree::setRight(Node* parentNode, Node* childNode){
    parentNode->right = childNode;
    if(childNode != nullptr){
        childNode->parent = parentNode;
    }
}

//Helper to handle when to do what kind of rotate to maintain AVL properties
void AVLTree::rotate(Node* node){    
    if( balanceFactor(node) == 2){
        if(balanceFactor(node->left) == -1){
            rotateLeft(node->left);
        }
        rotateRight(node);
    }
    else if(balanceFactor(node) == -2){
        if(balanceFactor(node->right) == 1){
            rotateRight(node->right);
        }
        rotateLeft(node);
    }
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}