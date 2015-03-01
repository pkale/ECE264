#include <stdlib.h> 
#include <stdlib.h> 
#include "answer08.h" 
#include <string.h>

int main(int argc, char * * argv)
{
   List * node1 = List_createNode("a");
   List * node2 = List_createNode("c"); 
   List * node3 = List_createNode("b");
   List * node4 = List_createNode("d");
   

   node1-> next = node2;
   node2->next = node3;
   node3->next = node4;
   List_sort(node1,strcmp);
   
  List_destroy(node1);
return 0;  
}
