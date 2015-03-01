#include "answer12.h"
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 #include <pthread.h>
 #include <math.h>
 
 typedef struct threadData{
     uint128 value;//value to test primality
     uint128 start;//start testing with this value
     uint128 stop;//stop testing with this value
     int * ans;//answer
 }threadData;
 
 uint128 alphaTou128(const char * str)
 {
  
     uint128 val = 0;
     int i = 0;
         while(str[i] != '\0'){
         
	   if((str[i] >= '0') && (str[i] <= '9')){
             val = val*10 + (str[i] - '0');
         }
         else if(str[i] == ' '){
         }
         else if((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')){
         }
         else if(str[i] == '-' && i == 0){
             return 0;
         }
         i++;//update index
     }
 
     return val;
 }
 
 int countNumOfDigits(uint128 value)
 {
     int numDigits = 0;//number of digits in value
 
     while(value != 0){
         value /= 10;
         ++numDigits;
     }
     return numDigits;
 }
 
 
 uint128 myExp(int value, int power)
 {
     uint128 answer = (uint128) value;
     int i = 1;
     if(power == 0)
         return 1;
 
     for(i = 1; i < power; i++){
         answer *= value;
     }
     return answer;
 }
 
 char * u128ToString(uint128 value)
 {
 
     //1.determine number of integers in the uint128
 
     int count = countNumOfDigits(value);//number of digits in value
     int numDigits = count;//copy of num_digits
 
     if(numDigits == 0){//number entered is "0"
         char * num_str = malloc(sizeof(char) * 2);
         num_str[0] = '0';
         num_str[1] = '\0';
         return num_str;
     }
 
     char * num = malloc(sizeof(char) * (count + 1));
 

     int val = 0;
     char digit = 0;
     int i;
 
     for(i = 0; i < count; i++){
         val = value / (myExp(10, numDigits-1));//int value of digit
         digit = val + '0';
         num[i] = digit;
         value = value % (myExp(10, --numDigits));
     }
     num[count] = '\0';//enter null byte
 
     return num;
 }
 
void * isPrime(void  * range) 
{ 
  threadData * thd = (threadData *) range; 
  uint128 n = thd->value;
  uint128 start = thd->start;
  uint128 stop = thd->stop;
  int * check;
  check  = thd->ans;
  if((*check) == 0)
    {
      pthread_exit(0);
    } 
  if ( n == 1) 
    { 
      *check = 0; 
    } 
  if(n == 2) 
    { 
      *check = 0; 
    } 
  if(n%2 == 0) 
    { 
      *check = 0; 
    } 
  int i;
  if (start < 3) 
    start = 3;
  for ( i = start; i <= stop; i++) 
    { 
      if(n%i == 0) 
	{
	  *check = 0; 
	}
    } 
  pthread_exit(0);
} 
 //constructor funcion for primeArgs struct
 
int primalityTestParallel(uint128 value, int n_threads)
{
  if(value == 1) 
    { 
      return 0;
    } 
  if(value == 2 )
    { 
      return 1;
    } 
  
   uint128 squareroot = (uint128)(floor(sqrt(value))); 
   int division = squareroot / n_threads;
   pthread_t  * tid = malloc(sizeof(pthread_t)*n_threads);
   threadData * divisions = malloc(n_threads*(sizeof(threadData)));
   int strt = 1; 
   int ind;

   int flag;
   flag = 1;
   for(ind = 0; ind < n_threads; ind++)
   {
     
     divisions[ind].value = value;      
     divisions[ind].ans= (&flag); 
     divisions[ind].start = strt;
     if((strt + division) < squareroot)
       {
	 divisions[ind].stop = strt + division; 

       }
     else 
       { 
	 // printf("\ncomes here\n");
	 divisions[ind].stop = (int)squareroot;


       } 
     strt = strt + division +1;
   }
     for(ind = 0; ind < n_threads; ind++)
     { 
       int rtv; 
       rtv = pthread_create(&tid[ind], NULL, isPrime, (void *) &divisions[ind]); 
       if(rtv != 0) 
	 { 
	   printf("ERROR: pthread_create() fail \n");
	 } 
     } 
    for(ind = 0; ind < n_threads; ind++) 
    { 
      int rtv; 
      rtv = pthread_join(tid[ind], NULL) ; 
      if(rtv != 0) 
	{ 
	  printf("ERROR ");
	}
    } 
    free(tid);
    free(divisions);
    				  
  return flag;
}

/*
int main(int argc, char *argv[]) {
    
  int ans =  primalityTestParallel(4, 2);
  printf("This is the ans for 4: %d \n\n", ans);
     ans =  primalityTestParallel(39, 3);
  printf("This is the ans for 39: %d \n\n", ans);
   ans =  primalityTestParallel(256, 4);
  printf("This is the ans for 256: %d \n\n", ans);
   ans =  primalityTestParallel(103, 4);
  printf("This is the ans for 103: %d \n\n", ans);
  return 0;
} 
*/
