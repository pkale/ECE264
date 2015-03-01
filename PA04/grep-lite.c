#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 

#define BUFSIZE 2001

int main(int argc, char * * argv) 
{
  char * pattern;
  char line[BUFSIZE];
   int i;
  int quit = 0; 
  int invert = 0; 
  int match = 1; 
  int lineN = 0; 
  int matched = 0;
   for(i = 0; i < argc; i++)
     {
       if(strcmp(argv[i],"--help") == 0)
	 {
           printf("Usage: grep-lite [OPTION]... PATTERN\nSearch for PATTERN in standard input. PATTERN is a\nstring. grep-lite will search standard input line by\nline, and (by default) print out those lines which\ncontain pattern as a substring.\n  -v, --invert-match     print non-matching lines\n  -n, --line-number      print line numbers with output  -q, --quiet            suppress all output\nExit status is 0 if any line is selected, 1 otherwise; if any error occurs, then the exit status is 2.");
           printf("\n");
           return EXIT_SUCCESS;
	 }
     }
   if(argc ==1) 
     {
       fputs("Error.",stderr);
       return 2;
     }
   pattern = argv[argc-1];
   if(pattern[0] == '-')
     {
       fputs("Error in reading the pattern.",stderr);
       return 2;
     }
for(i = 1; i < argc-1; i++)
 { 
   if((strcmp(argv[i],"-q") == 0) || (strcmp(argv[i], "--quiet") == 0)) 
   {
     quit = 1; 
   }
   if((strcmp(argv[i],"-v") == 0) || (strcmp(argv[i],"--invert-match") == 0))
   {
     invert = 1;
     match = 0;
   } 
   if((strcmp(argv[i],"--line-number") == 0) || (strcmp(argv[i],"-n")== 0))
   {
     lineN = 1; 
   }
   if((quit == 0) && (invert == 0) && (lineN == 0)) 
     {
       return 2;
     }  
 }
 int lineNumber = 0; 
   while(fgets(line,BUFSIZE,stdin) != NULL)
       {
         lineNumber++;
       if(quit) 
         {
           return EXIT_SUCCESS;
         }
      
       if(invert) 
       {
          if(strstr(line,pattern) == NULL)
          {
              if(lineN) 
		(              {
                fprintf(stdout,"%d:",lineNumber);
              }
             fprintf(stdout,"%s",line);
             matched = 1;
          } 
       }
      if(match)
      {
       
         if(strstr(line,pattern) != NULL) 
         {
          if(lineN) 
          {
           fprintf(stdout,"%d:",lineNumber);
          }
          fprintf(stdout,"%s",line);
          matched = 1;
         }
      }
       }
   if(matched==1) 
     {
       return 0; 
     }
   else 
     {
       return 1;
     }
 return 0;
}

