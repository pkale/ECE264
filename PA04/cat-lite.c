#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

int main(int argc, char * * argv) 
{
  
  FILE * fin1; 
   char c; 
   int i;
   int n;
   int standardInput = 0;
   for(i = 0; i < argc; i++)
     {
       if(strcmp(argv[i],"--help") == 0)
	 {
           printf("Usage: cat-lite [--help] [FILE]...\nWith no FILE, or when FILE is -, read standard input.\nExamples:\ncat-lite README   Print the file README to standard output.\n cat-lite f - g    Print f's contents, then standard input, \n                    then g's contents.\n  cat-lite          Copy standard input to standard output.");
           printf("\n");
           return EXIT_SUCCESS;
	 }
     }
 for(i = 1; i < argc; i++)
 { 
   n = 0;
   //c = ' ';
   standardInput = 0;
   if(strcmp(argv[i],"-")== 0) 
	 {
           standardInput = 1;
           fin1 = stdin;
	 }
   if(standardInput ==0)
     {
       fin1 = fopen(argv[i], "r") ; 
       if(fin1 == NULL) 
       {
	 printf("fopen fail \n");
         return EXIT_FAILURE; 
       }
     }
   while(!feof(fin1))
       {
         c = fgetc(fin1);
         if(c != EOF)
	   {
	     fprintf(stdout,"%c",c);
           } 
       }
       fclose(fin1);   
 }
 int temp = argc;

 if(temp ==1) 
   {
     while(feof(stdin) == 0) 
       {
         c = fgetc(stdin);
         if(c != EOF) 
	   {
             fprintf(stdout,"%c",c);
 	   }

       }
   }
 return 0;
}
