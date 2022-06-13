#include <iostream>
#include <cstring>
#include "Node.h"

void addNode(char newName, char* vertices[20]);
void PRINT(char* vertices[20], int* edges[20][20]);
void PATH(char firstNode, char secondNode, char* vertices[20], int* edges[20][20]);

using namespace std;

int main(){
Node **list = new Node*[20];
int IndexCounter = 0;
for(int i = 0; i < 20; i++){
arr2[i] = '\0';
}
char input[100];
bool running = true;
while(running == true){
cout << "Welcome to Graph Creator! To add a vertex, type 'ADD'. To search for the shortest path type 'PATH'. To print, type 'PRINT'." << endl;
cin >> input;
if(strcmp(input, "ADD") == 0){
    char nodeName;
    int vertexLength = 0;
    cout << "What do you want to call the new node?" << endl;
    cin >> nodeName;
    addNode(nodeName, arr2);
    }
if(strcmp(input, "PATH") == 0){
    char firstNode;
    
}
}
}
