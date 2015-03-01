/**
* Do not modify this file
*/
#ifndef PA05_H
#define PA05_H
/**
* Prints all the partitions of a positive integer value.
*
* Example:
* partitionAll(3); // prints the following: (line order not important)
* = 1 + 1 + 1
* = 1 + 2
* = 2 + 1
* = 3
*
* Note: Order does not matter, and neither does white-space.
* Hint: look at file: expected/partitionAll.output
*/
void partitionAll(int value)
{
  int arr[MAXLEN];
  partitionHelper(arr,0,value,showAll);
}
//show all the valid partitions
int showAll()
{
  return 1;
}
/**
* Prints all partitions that have strictly increasing values.
*
* Example:
* partitionIncreasing(5); // prints the following: (line order not important)
* = 1 + 4
* = 2 + 3
* = 5
*
* These partitions are excluded because they are not _strictly_ increasing
* 1 + 1 + 3
* 2 + 1 + 2
* 3 + 2
*
* Note:
* The program should generate only valid partitions. Do not
* generates all partitions and then filter for validity. If you
* do this, you will almost certainly have trouble understanding the exam.
*
* Hint: look at file: expected/partitionIncreasing.output
*/
void partitionIncreasing(int value){
  int arr[MAXLEN];
  partionHelper(arr,0,value,isIncreasing);

}

int isIncreasing(int value, int * arr, int ind) 
{
  if (ind == 0) 
    return 1; 
  return (value > arr[ind-1]; 
}

void partionHelper(int * buffer, int ind, int values, int (*testFun))
    {
      if (value == 0)
	{ 
	printPartion();
      return;
	}
      int nextVal; 
      for(nextVal = 1; nextVal <= value; ++nextVal) 
	{
	  if(testFun(nextVal,buffer,ind) 
	    {
	      buffer[ind] = nextVal; 
	      partitionHelper(buffer,ind +1, value - nextVal,testFun); 
            }
	} 
   return;
    }
/**
* Prints all partitions that have strictly decreasing values.
*
* Example:
* partitionDecreasing(5); // prints the following: (line order not important)
* = 3 + 2
* = 4 + 1
* = 5
*
* These partitions are excluded because they are not _strictly_ decreasing
* 1 + 1 + 3
* 2 + 1 + 2
*
* See: note on partitionIncreasing(...)
* Hint: look at file: expected/partitionDecreasing.output
*/
int isDecreasing(int value, int * arr, int ind) 
{
  if (ind == 0) 
    return 1; 
  return (value < arr[ind-1]; 
}
void partitionDecreasing(int value)
    {
      int arr[MAXLEN];
      partitionHelper(arr, 0, value, isDecreasing); 
    }

/**
* Prints all partitions comprised solely of odd numbers.
*
* Example:
* partitionOdd(5); // prints the following (line order not important)
* = 1 + 1 + 1 + 1 + 1
* = 1 + 1 + 3
* = 1 + 3 + 1
* = 3 + 1 + 1
* = 5
*
* See: note on partitionIncreasing(...)
* Hint: for odd numbers, (value % 2 != 0)
* Hint: look at file: expected/partitionOdd.output
*/
void partitionOdd(int value);
 {
   int arr[value]; 
   partitionHelper(arr,0,value,isOdd);
 }

 int isOdd(int value, int *arr,int ind) 
 {
   return (value %2 != 0);
 }
/**
* Prints all partitions comprised solely of even numbers.
*
* Example:
* partitionEven(6); // prints the following (line order not important)
* = 2 + 2 + 2
* = 2 + 4
* = 4 + 2
* = 6
*
* See: note on partitionIncreasing(...)
* Hint: for even numbers, (value % 2 == 0)
* Hint: you can never partition an odd number with even numbers alone.
* Hint: look at file: expected/partitionEven.output
*/
 int isEven(int value, int * arr,int ind) 
 {
   return (value % 2 ==0);
 }
void partitionEven(int value)
{
  int arr[value]; 
  partitionHelper(arr,0,value,isEven);
}

/**
* Prints all partitions that do not have consecutive odd or even numbers.
* In other words, it only prints partitions that have alternating odd and
* even numbers.
*
* Example:
* partitionOddAndEven(5); // prints the following (line order not important)
* = 1 + 4
* = 2 + 1 + 2
* = 2 + 3
* = 3 + 2
* = 4 + 1
* = 5
*
* See: note on partitionIncreasing(...)
* Hint: look at file: expected/partitionOddAndEven.output
*/

 void printPartition(int *arr, int length)
 {
   int ind;
   for(ind = 0; ind < 
 }
void partitionOddAndEven(int value)
 {
   
 }
/**
* Prints all partitions that comprise solely of prime numbers.
*
* Example:
* partitionPrime(5); // prints the following (line order not important)
* = 2 + 3
* = 3 + 2
* = 5
*
* See: note on partitionIncreasing(...)
* Hint: you will need to write a function that checks if a number is prime.
* Hint: 1 is not a prime number.
* Hint: look at file: expected/partitionPrime.output
*/
void partitionPrime(int value){
 
}
#endif
