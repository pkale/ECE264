#include "answer06.h" 
#include <stdio.h> 

enum {ORIGIN, EAST, SOUTH, WEST, NORTH}; 
enum {FORWARD, BACKWARD, DONE}; 

int canMove(char * * mzptr, int row, int col, int dir) 
{
  int counter = 0;    
	if ( mzptr[row -1][col] == ' ') 
	{
          counter++;  
        }
	if(mzptr[row + 1] [col] == ' ')  
	{
          counter++; 
        }   
	if( mzptr[row] [col -1] == ' ')
	{
          counter++;
	}
        if( mzptr [row] [col -1] == ' ') 
	{
          counter++;  
        }
	
        if ( counter > 1) 
          return 1;
return 0;   
}
void print_directions(char ** maze, int w, int h) 
{ 
  int i; 
  int j; 
  i = 0;
  for ( i = 0; i < strlen(maze[0]); i ++ ) 
  {
    if ( maze[0][i] == ' ') 
      getDirection(maze, 0, i, SOUTH, FORWARD);  
  } 
}
void getDirection( char * * mzptr, int row, int col, int dir, int * mode ) 
{
   if(dir == NORTH) 
     printf("N %d", 1);
   if(dir ==SOUTH) 
     printf("S %d", 1);
   if(dir == EAST) 
     printf("E %d", 1);
   if(dir == WEST) 
     printf("W %d", 1); 

   if(mzptr[row][col] == 'X') 
   {
      (*mode) = DONE;  
   }
   
   if(((*mode) != DONE) && canMove(mzptr,row,col,EAST) && (dir != WEST)) 
   { 
      (*mode) = FORWARD; 
      getDirection(mzptr, row, col +1, EAST, mode); 
      if((*mode) == BACKWARD) 
      { 
        printf("W %d", 1);
      }
   } 
   if(((*mode) != DONE) && canMove(mzptr, row, col, SOUTH) && (dir != NORTH))
   {
     (*mode) = FORWARD; 
     getDirection(mzptr, row +1, col, SOUTH, mode); 
     if((*mode) == BACKWARD) 
     {
       printf("N %d",1);
     } 
   }
   if(((*mode) != DONE) && canMove(mzptr, row, col, WEST) && (dir != EAST)) 
   {
      (*mode) = FORWARD; 
      getDirection(mzptr, row, col-1,WEST, mode);
      if((*mode) == BACKWARD)
      {
        printf("E %d", 1); 
      } 
   }
   if(((*mode) != DONE) && canMove(mzptr, row, col, NORTH) && (dir != SOUTH)) 
    {
      (*mode) = FORWARD; 
      getDirection(mzptr, row -1, col, NORTH, mode); 
      if((*mode) == BACKWARD) 
      {
        printf("S %d", 1); 
      } 
    } 
   if((*mode) != DONE) 
   {
     mzptr[row][col] = 'Y';
     (*mode) = BACKWARD;  
   }     
}

