/* 
 * Do not modify this file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "answer03.h"

#define BUFFER_LEN 1024

void test01()
{
  const char * z2 = "How did it get so late so soon?";
  char * s1 = NULL;
  int n;
  char * s2 = strcat_ex(&s1, &n, z2);
	printf("This is the combined string: %s \n",s2);  
free(s2);
}

int main(int argc, char * * argv)
{
    test01();
//  return 0;


  const char * s1 = "This is the tester"; 
  const char * s2 = "program." ;
  const char * delims = " ";
   char * * ans;
  int n = 50; 
  int f = 0;

  char * dest = malloc( sizeof(char) * n); 
  char * src = malloc( sizeof(char)* n); 
  
  strcpy(dest,s1); 
  strcpy(src,s2); 
  
  
  strcat_ex(&dest, &n, src); 

  printf("This is the combined string : %s \n", dest); 
  
  printf("This is the string sent to explode : %s \n", s1); 
 ans = explode(s1,delims,&n);
 for(f = 0; f < 4; f++)
   {
     printf("This is the exploded string : %s \n", ans[f]); 
   }
  free(dest); 
  free(src); 
  destroyStringArray (ans, 4);

  return(0); 
}


