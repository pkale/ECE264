#include <stdio.h>
#include <stdlib.h>

#include "answer03.h"
/**
 * Append the C-string 'src' to the end of the C-string '*dest'.
 *
 * strcat_ex(...) will append the C-string 'src' to the end of the string
 * at '*dest'. The parameter 'n' is the address of a int that specifies how
 * many characters can safely be stored in '*dest'. 
 *
 * If '*dest' is NULL, or if '*dest' is not large enough to contain the result
 * (that is, the sum of the lengths of *dest, src, and the null byte), then
 * strcat_ex will:
 * (1) malloc a new buffer of size 1 + 2 * (strlen(*dest) + strlen(src))
 * (2) set '*n' to the size of the new buffer
 * (3) copy '*dest' into the beginning of the new buffer
 * (4) free the memory '*dest', and then set '*dest' to point to the new buffer
 * (5) concatenate 'src' onto the end of '*dest'.
 *
 * Always returns *dest.
 *
 * Why do we need to pass dest as char * *, and n as int *? 
 * Please see the FAQ for an answer.
 *
 * Hint: These <string.h> functions will help: strcat, strcpy, strlen.
 * Hint: Leak no memory.
 */
char * strcat_ex(char * * dest, int * n, const char * src)
{ 
  char * temp;
  int lengthNeeded = 0; 
  int dstlen;
  // Work out when I need to create a new buffer...
  if(*dest == NULL || strlen(*dest) + strlen(src) + 1 > *n)
    {
      // Okay, create a new buffer, and do stuff
       dstlen = (*dest) == NULL ? 0 : strlen(*dest);
      lengthNeeded = 2 * (dstlen + strlen(src)) + 1;
      *n = lengthNeeded;
      temp = malloc(sizeof(char) * lengthNeeded);      
      temp[0] = '\0';
      if(*dest != NULL)	
          strcpy(temp, *dest);
      free(*dest);
      *dest = temp;      
    }
  strcat(*dest, src);    
  return *dest;

  if(0)
    {
      lengthNeeded = 1 + 2 * (strlen(*dest) + strlen(src));
      if(*n < lengthNeeded)
	{
          *n = lengthNeeded;
          temp = malloc(sizeof(char)*(lengthNeeded)); 
          temp[0] = '\0';
          strcpy(temp, *dest);
          free(*dest); 
          *dest = temp;
        }
      strcat(*dest,src);      
    }
  // free(temp);
  // return *dest;
}

/**
 * Takes a string and splits it into an array of strings according to delimiter.
 * The memory location '*arrLen' is initialized to the length of the returned
 * array.
 *
 * str: A string to split
 * delims: a string that contains a set of delimiter characters. explode(...) 
 *         will split the string at any character that appears in 'delims'.
 * arrLen: pointer to an int that is used to store the resultant length of the
 *         returned array.
 *
 * For example, if delimiter is white space " \t\v\n\r\f", then,
 * int len;
 * char * * strArr = explode("The\nTuring test", " \t\v\n\r\f", &len);
 * // len = 3, strArr[0] is "The", strArr[1] is "Turing", strArr[2] is "test"
 *
 * Hint: you can use <string.h> functions "memcpy" and "strchr"
 *       "memcpy" copies blocks of memory.
 *       "strchr" can be used to tell if a specific character is in delims.
 * Hint: this question is hard; it will help to draw out your algorithm.
 * Hint: read the FAQ...
 */

char * * explode(const char * str, const char * delims, int * arrLen)
{
  int ind; 
  * arrLen = 1;
  char * temp;
  int index1 = 0; // array index
  for(ind = 0; ind < strlen(str) ; ind++)
    {
      if(strchr(delims,str[ind]) != NULL)
	{
          (*arrLen)++;
	}
    }
  char * * arr1; // 2D array 
  arr1 = malloc(sizeof(char *) * (*arrLen));
  int row; 
  ind = 0; 
  int strlength = 0;
  int startLeft = 0; 
  int startRight = 0;
  for( row = 0; row < (*arrLen); row++) 
    {
      while((strchr(delims,str[ind]) == NULL)&& (str[ind] != '\0'))
	{
          strlength++;
          ind++;
	}
          temp = malloc(sizeof(char) * (strlength+1));
          temp[0] = '\0';
            startLeft = startRight;
           startRight = ind + 1;  
	   strncpy(temp,&(str[startLeft]),strlength);
          temp[strlength] = '\0';
          arr1[index1] = temp; 
          index1++; 
          strlength = 0; 
          ind++;
	
    }
  /* while( strchr(delims,str[ind]) == NULL)
	{
          strlength++;
          ind++;
	}
  
          temp = malloc(sizeof(char) * (strlength+1));
          temp[0] = '\0';
           startLeft = startRight;
           startRight = ind + 1;  
	   strncpy(temp,&(str[startLeft]),strlength);
          temp[strlength] = '\0';
          arr1[index1] = temp; 
          index1++; 
          strlength = 0; 
          ind++;
  */
	  // free(temp);
  return (char * *)(arr1);
}


/**
 * Takes an array of strings, and concatenates the elements into a single
 * string, placing 'glue' between each successive element.
 *
 * strArr: an array of strings
 * len: the length of the array 'strArr'
 * glue: string to concatenate between each element of 'strArr'
 *
 * For example:
 * int len;
 * char * * strArr = explode("100 224 147 80", " ", &len);
 * char * str = implode(strArr, len, ", ");
 * printf("(%s)\n", str); // (100, 224, 147, 80)
 *
 * Hint: use strcat_ex in a for loop.
 */
char * implode(char * * strArr, int len, const char * glue)
{ 
  char * str;
  int row = 1;
  int number = 0;  
  // str = strArr[0];
  int r = 0;
  int c = 0;
  for(r = 0; r < len ; r++)
    {
      for(c = 0; c < strlen(strArr[r]); c++) 
	{
	  number++; 
	}
      number = number + strlen(glue);
    }
  str = malloc(sizeof(char)*(number+1));
  str[0] = '\0';
    for(row = 0; row < len-1; row++)
  {
    str = strcat(str, strArr[row]);
    str = strcat(str, glue); 
  }
   str = strcat(str,strArr[row]);

  return str;
}

/**
 * Takes an array of C-strings, and sorts them alphabetically, ascending.
 *
 * arrString: an array of strings
 * len: length of the array 'arrString'
 *
 * For example, 
 * int len;
 * char * * strArr = explode("lady beatle brew", " ", &len);
 * sortStringArray(strArr, len);
 * char * str = implode(strArr, len, " ");
 * printf("%s\n"); // beatle brew lady
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_ understand the typecasts.
 */
 int compare(const void *a, const void *b){

    const char* a1 = *(const char**)a;
    const char* b1 = *(const char**)b;
    return strcmp(a1,b1);
}  
void sortStringArray(char * * arrString, int len)
{
  
  if(arrString != NULL)
    {
      qsort(arrString, len,sizeof(char *),compare);
    }
}
/**
 * Sorts the characters in a string.
 *
 * str: string whose characters are to be sorted
 *
 * For example, 
 * char * s1 = strdup("How did it get so late so soon?");
 * sortStringCharacters(s1)
 * // s1 is now "       ?Haddeegiilnooooossstttw"
 *
 * Hint: use the <stdlib.h> function "qsort"
 * Hint: you must _clearly_  understand the typecasts.
 */


int cmpChar(const void * arg1, const void * arg2) 
{
  const char  *ptr1 = (const char*)arg1; 
  const char  *ptr2 = (const char*)arg2; 
  const char val1 = * ptr1; 
  const char val2 = * ptr2;

  if(val1 < val2)
  {
    return -1;
  }
  if(val1 == val2) 
  {
    return 0;  
  }
  return 1; 
}

void sortStringCharacters(char * str)
{


  int len = strlen(str); 
  
  if(str != NULL)
    {
      qsort(str, len,sizeof(char),cmpChar);
    }

}
/**
 * Safely frees all memory associated with strArr, and then strArr itself.
 * Passing NULL as the first parameter has no effect.
 *
 * strArr: an array of strings
 * len: the length of 'strArr'
 *
 * int len;
 * const char * abe = "Give me six hours to chop down a tree and I will spend\n"
 *                    "the first four sharpening the axe.";
 * char * * strArr = explode(abe, "\n ");
 * destroyStringArray(strArr, len); // cleans memory -- no memory leaks
 * destroyStringArray(NULL, 0); // does nothing, does not crash.
 */
void destroyStringArray(char * * strArr, int len)
{
   int ind = 0;
if( strArr != NULL)
  {
    for(ind = 0; ind < len; ind++)
    {
      free(strArr[ind]);
    }
    free(strArr);
  }
}
