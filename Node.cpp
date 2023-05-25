#include <iostream>
#include <string>
using namespace std;

#include "Node.h"

//Default Constructor
Node::Node() : data(""), left(nullptr), right(nullptr), parent(nullptr) {}
//Parameterized Constructor
Node::Node(const string& value) : data(value), left(nullptr), right(nullptr), parent(nullptr) {}