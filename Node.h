#ifndef __NODE_H
#define __NODE_H

#include <string>

using namespace std;

class Node {
    //Too lazy to implement get function so am just gonna friend the tree class to access private elements althrough ig I could've just made it a struct or public but whatever I refuse to think anymore
    friend class AVLTree;

    private:
    string data;
    int count;

    Node *left;
    Node *right;
    Node *parent;

    Node();
    Node(const string&);
};

#endif // __NODE_H
