#include <iostream>
#include "Node.h"

using namespace std;

//Constructor
Node::Node(){
name = '\0';
    for(int i = 0; i < 20; i++){
        edges[i] = '\0';
    }
}

//Getters
char Node::getName(){
    return name;
}

int Node::getIndex(){
    return index;
}

int Node::getEdge(int retrieved){
    return edges[retrieved];
}

//Setters
void Node::setName(char newName){
    name = newName;
}

void Node::setIndex(int newIndex){
    index = newIndex;
}

void Node::setEdge(int retrieved, int value){
    edges[retrieved] = value;
}



//Destructor
Node::~Node(){
name = '\0';
    for(int i = 0; i < 20; i++){
        edges[i] = '\0';
    }    
}