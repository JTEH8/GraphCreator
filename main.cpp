#include "bst.h"

int main()
{
    bst object;
    object.build(); 	//builds a BST
    object.display();	//displays a BST

    /*  PLACE YOUR FUNCTION CALL HERE */
    object.deleteNonRoot(object.getRoot(), object.getRoot(), object.getRoot());


    object.display();	//displays again after!
   
    return 0;
}
