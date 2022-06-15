#include <iostream>
#include <cstring>
#include "Node.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define BLUE "\033[34m"

Node* findNode(Node** list, char input, int indexCount);
void addNode(char newName, Node **list, int indexCount);
void addEdge(char node1, char node2, int edgeValue, Node ** list, int indexCount);
void PRINT(Node **list, int indexCount);
void PATH(char firstNode, char secondNode, char* vertices[20], int* edges[20][20]);
void deleteNode(char name, Node **list, int indexCount);
void deleteEdge(char node1, char node2, Node **list, int indexCount);

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
cout << "To print, type 'PRINT'." << endl;
cout << "To quit type QUIT." << endl;
cin >> input;
if(strcmp(input, "VADD") == 0){
    char temp;
    cout << "Enter the  character name for the new vertex." << endl;
    cin >> temp; 
    addNode(temp, list, IndexCounter);
    IndexCounter++;
    }
else if(strcmp(input, "EADD") == 0){
    char node1;
    char node2;
    int num = 0;
    cout << "What is the first vertex you want to add an edge to?" << endl;
    cin >> node1; 
    cout << "What is the second vertex you want to add an edge to?" << endl;
    cin >> node2; 
    cout << "What do you want to set the value of the edge as?" << endl;
    cin >> num;
    addEdge(node1, node2, num, list, IndexCounter);
    cout << "Edge successfully added." << endl;
    }
else if(strcmp(input, "VREMOVE") == 0){
    char name;
    cout << "What is the name of the vertex you want to delete?" << endl;
    cin >> name;
    deleteNode(name, list, IndexCounter);
    IndexCounter--;
}
else if(strcmp(input, "PRINT") == 0){
    PRINT(list, IndexCounter);
    cout << endl;
}
else if(strcmp(input, "QUIT") == 0){
    cout << "Thanks for using graph creator!" << endl;
    running = false;
}
else{
    cout << "Invalid input, please enter something else." << endl;
        }
    }
}

//Finds the node in the list
Node* findNode(Node** list, char input, int indexCount){
    for(int i = 0; i < indexCount; i++){
        if((list[i])->getName() == input){
            return (list[i]);
            break;
            }
    }
    return NULL;
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

void deleteNode(char name, Node **list, int indexCount){
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

void addEdge(char node1, char node2, int edgeValue, Node ** list, int indexCount){
//If there's not two vertices in the graph
if(list[0] == NULL || list[1] == NULL){
    cout << "Sorry, but you're going to have to add more than one vertex before you can add an edge." << endl;
    return;
}
else{
//Find the two nodes
Node* vertex1 = findNode(list, node1, indexCount);
Node* vertex2 = findNode(list, node2, indexCount);
//If one of them doesn't exist
if(vertex1 == NULL || vertex2 == NULL){
    cout << "Unable to find the vertices you're looking for." << endl;
    return;
}
else{
    //Connect the two vertices
     vertex1->setEdge(vertex2->getIndex(), edgeValue);
     vertex2->setEdge(vertex1->getIndex(), edgeValue);
}
}
}

void deleteEdge(char node1, char node2, Node **list, int indexCount){
    //Same as in addEdge, make sure that two or more vertices actually exist
if(list[0] == NULL || list[1] == NULL){
    cout << "Sorry, but you're going to have to add more than one vertex before you can delete an edge." << endl;
    return;
}   
else{
    //Find the two nodes
    Node* vertex1 = findNode(list, node1, indexCount);
    Node* vertex2 = findNode(list, node2, indexCount);
    if(vertex1 == NULL || vertex2 == NULL){
    cout << "Unable to find the vertices you're looking for." << endl;
    return;
}
else{
    //Instead of connecting the vertices, set the edge between them to 0.
     vertex1->setEdge(vertex2->getIndex(), 0);
     vertex2->setEdge(vertex1->getIndex(), 0);
}
}
}