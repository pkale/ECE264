#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
    int counter = 0;
    int sum = 0;
    
    for(counter = 0; counter < len ; counter++)
    {
      sum = sum + array[counter];
    }
    return sum;
}

int arrayCountNegative(int * array, int len)
{
    int counter = 0;
    int count = 0;

    for(counter = 0; counter < len ; counter++)
    {
      if(array[counter] < 0)
        count++;
    }

    return count;
}

int arrayIsIncreasing(int * array, int len)
{
    int counter = 0;
    if(len <= 1)
      return 1;
    else
    {
       for(counter = 1; counter < len; counter++)
       {
        if(array[counter - 1] > array[counter])
          return 0;
       }
    }
    return 1;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
    int counter = 0;
    int index = -1;

    if(len == 0)
       return -1;

    for(counter = 0; counter < len ; counter++)
    {
       if(haystack[counter] == needle)
         index = counter;
    }
    return index;
}

int arrayFindSmallest(int * array, int len)
{

    int counter = 0;
    int smallest = 0;
    int index = 0;

    if(len == 0)
       return 0;

    for(counter = len - 1; counter >= 0 ; counter--)
    {
       if(array[counter] <= smallest)
       {
         index = counter;
         smallest = array[counter];
       }
    }
    return index;
}
