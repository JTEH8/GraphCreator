//Header guard
#ifndef NODE_H
#define NODE_H
#include <cstring>

//Tree Clas
class Node{
private:
    //Vairables
    char name;
    int index;
    int edges[20];
public:
    //Function prototypes
    Node();
    ~Node();
    //Getters
    char getName();
    int getIndex();
    int getEdge(int retrieved);
    //Setters
    void setName(char);
    void setIndex(int);
    void setEdge(int, int);
};

#endif