#include <iostream>
#include <cstring>
#include "Node.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"

Node* findNode(Node** list, char input, int indexCount);
void addNode(char newName, Node **list, int indexCount);
void addEdge(Node ** list, int indexCount);
void PRINT(Node **list, int indexCount);
void PATH(char firstNode, char secondNode, char* vertices[20], int* edges[20][20]);
void deleteNode(char name, Node **list, int indexCount);
void deleteEdge(Node **list, int indexCount);

using namespace std;

int main(){
Node **list = new Node*[20];
int IndexCounter = 0;

char input[100];
bool running = true;
cout << "Welcome to Graph Creator!" << endl;
while(running == true){
cout << "To add a vertex, type 'VADD'. To add an edge, type 'EADD'. " << endl;
cout << "To remove a vertex type 'VREMOVE'. To remove an edge, type 'EREMOVE'. " << endl;
cout << "To search for the shortest path type 'PATH'. To print, type 'PRINT'." << endl;
cout << "To quit type QUIT." << endl;
cin >> input;
if(strcmp(input, "ADDV") == 0){
    char temp;
    cout << "Enter the  character name for the new vertex." << endl;
    cin >> temp; 
    addNode(temp, list, IndexCounter);
    IndexCounter++;
    }
else if(strcmp(input, "DELETEV")){
    char name;
    cout << "What is the name of the vertex you want to delete?" << endl;
    cin >> name;
    deleteNode(name, list, IndexCounter);
    IndexCounter--;
}
else if(strcmp(input, "PRINT")){
    PRINT(list, IndexCounter);
    cout << endl;
}
else if(strcmp(input, "PATH") == 0){
    char firstNode;
}
else if(strcmp(input, "QUIT")){
    cout << "Thanks for using graph creator!" << endl;
    running = false;
}
else{
    cout << "Invalid input, please enter something else." << endl;
        }
    }
}

void addNode(char newName, Node **list, int indexCount){
    //New Vertexr
    Node* newVertex = new Node();
    //Add in all it's info, make sure it's index and name are correct
    newVertex->setIndex(indexCount);
    newVertex->setName(newName);
    //Add it to the list
    list[indexCount] = newVertex;
    cout << endl;
    cout << "Vertex " << newVertex->getName() << " added." << endl;
}

void removeNode(char name, Node **list, int indexCount){
    if(list[0] == NULL){
        cout << endl;
        cout << "There's no vertices currently on the graph! Add some first." << endl;
        return;
    }
    Node* vertex = findNode(list, name, indexCount);
    if(vertex == NULL){
        cout << endl;
        cout << "No vertex found. Try another one!" << endl;
        return;
    }
    else{
        int x = vertex->getIndex();
        //Remove data from the vertex
        vertex->~Node(); 
        cout << "The vertex at index " << x << " has been removed." << endl;
        //Remake the edge list
        for(int i = 0; i < indexCount; i++){
            Node* current = list[i];
            for(int j = 1; j < indexCount; j++){
                //If you get to where the current edge is one less than the index
                if(j == (indexCount - 1)){
                    current->setEdge(j, 0);
                }
                //Otherwise move all the edges above down by 1 index.
                else{
                    int next  = j + 1;
                    current->setEdge(j, current->getEdge(next));
                }
            }
            list[i] = current;
        }
        list[x] = NULL;
        while(x < indexCount){
            if(x = (indexCount - 1)){
                list[x] = NULL;
                break;
            }
            list[x] = list[x+1];
            list[x]->setIndex(x);
            x++;
        }
    cout << endl;
    cout << "Vertex has been deleted" << endl;
    }
}

void PRINT(Node **list, int indexCount){
    //[row][column] (There's 21 spots to account for the nodes on top/Left)
    char print[21][21];
    //Sets it to empty
    for(int i = 0; i < 21; i++){
        for(int j = 0; j < 21; j++){
            print[i][j] = ' ';
        }
    }
    char edgePrint[20][20];
    int num = 0;
    //Build the adjacency matrix visual
    //For the first row/column (Vertex Names)
    while(num < indexCount){
        print[0][num+1] = (list[num])->getName();
        print[num+1][0] = (list[num])->getName();
        num++;
    }
    //Creates a display of all the edges
    for(int i = 0; i < indexCount; i++){
        Node* vertex = list[i];
        for(int j = 0; j < indexCount; j++){
            Node* vertex2 = list[j];
            //If the two have a shared edge
            if(vertex->getEdge(vertex2->getIndex()) != 0){
            //Print true
                edgePrint[i][j] = 'T';
            }
            //Otherwise print false
            else{
                edgePrint[i][j] = 'F';
            }
        }
    }
    //Place the matrix in the main array
    for(int i = 0; i < indexCount; i++){
        for(int j = 0; j < indexCount; j++){
            //Insert 
            print[i+1][j+1] = edgePrint[i][j];
        }
    }
    //Print out the whole thing
    for(int i = 0; i < 21; i++){
        for(int j = 0; j < 21; i++){
            //If true print in blue (except for node names)
            if(print[i][j] == 'T' && i != 0 && j != 0){
                cout << BLUE << print[i][j] << RESET << '\t';
            }
            //If false print in false
            else if(print[i][j] == 'F' && i != 0 && j != 0){
                cout << RED << print[i][j] << RESET << '\t';
            }
            else{
                cout << print[i][j] << '\t';
            }
        }
    cout << endl;
    if(print[i+1][0] == ' '){
        break;
    }
    }
}