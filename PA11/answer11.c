
#include <stdio.h>
#include<stdlib.h> 
#include "answer11.h"
// -------------------------------------------------------------------- HuffNode

/**
 * A Huffman coding tree. We must implement two small functions... 
 *
 * (1) HuffNode_create(value);         // create a new HuffNode
 * (2) HuffNode_destroy(tree);         // free all memory safely
 */

/**
 * Create a new, properly intialized HuffNode
 */
HuffNode * HuffNode_create(int value)
{
  HuffNode * node = malloc(sizeof(HuffNode)); 
  node->value = value; 
  node->left = NULL; 
  node->right = NULL; 
  return node; 
}

/**
 * Destroy a tree, including all sub-children. Must handle NULL values safely.
 */
void HuffNode_destroy(HuffNode * tree)
{
  if (tree == NULL) 
    { 
      return; 
    } 
  HuffNode_destroy(tree->left); 
  HuffNode_destroy(tree->right); 
  free(tree); 
}

// ----------------------------------------------------------------------- Stack

/**
 * We need a "Stack" to build the tree structure that is used to decode
 * a Huffman encoding. Stacks are very simple to implement with linked lists.
 * We must implement the following functions (given below). Each of these 
 * functions should only be a few lines of code.
 *
 * (1) Stack_create();              // Allocate a brand new stack.
 * (2) Stack_destroy(stack);        // Clean up memory for the stack.
 * (3) Stack_isEmpty(stack);    // TRUE iff (if and only if) the stack is empty.
 * (4) Stack_pushFront(stack, tree); // Push a tree onto the stack.
 * (6) Stack_popFront(stack);  // Remove a tree from the stack and return it.
 *
 * Altogether, these six functions should be around 40 lines of code.
 */

/**
 * Returns a pointer to a new empty stack struct
 */
Stack * Stack_create()
{
  Stack * st = malloc(sizeof(Stack)) ; 
  st ->head = NULL; 
  return st; 
}

/**
 * Frees all memory associated with the stack. 
 * Don't forget that you must free the entire contained linked-list.
 * Also, you must safely do nothing if stack == NULL. 
 */
void Stack_destroy(Stack * stack)
{
  if(stack == NULL) 
    { 
      return; 
    } 
  StackNode* head = stack->head;
  StackNode * temp = head; 
  while(head != NULL) 
    {
      temp = head->next;
      HuffNode_destroy(head->tree); 
      free(head); 
      head = temp; 
    }
  free(stack); 
}

/**
 * Returns TRUE (something other than zero) if the stack is empty.
 */
int Stack_isEmpty(Stack * stack)
{
  if(( stack->head) == NULL) 
    {
      return 1;
    }  
  return 0; 
}

/**
 * Pop the front (top) 'value' (i.e. Huffman tree) from the stack.
 *
 * More precisely, this function must do three things:
 * (1) Save the value (i.e. Huffman tree) of the head node of the stack's list
 * (2) Remove the head node of the stack's list, freeing it.
 * (3) Return the value (i.e. Huffman tree) saved in (1).
 */
HuffNode * Stack_popFront(Stack * stack)
{ 
  if(stack == NULL) 
    { 
      return NULL;
    }
  HuffNode * node = stack->head->tree;
  StackNode * temp = stack->head->next; 
  free(stack->head); 
  stack->head = temp; 
  return node; 
}

/**
 * Push a 'value' (i.e. Huffman tree) onto the front (top) of the stack.
 *
 * More precisely, this function must do two things:
 * (1) Create a new StackNode with 'tree' for its tree.
 * (2) Push that new StackNode onto the front of the stack's list.
 */
void Stack_pushFront(Stack * stack, HuffNode * tree)
{
  StackNode * node  = malloc(sizeof(StackNode)); 
  node-> tree = tree; 
  node->next = stack->head; 
  stack->head = node;
}

// -------------------------------------------------------- Pop Pop combine Push

/**
 * This function helps simplify building a Huffman Coding Tree from the header
 * information. It takes a stack as input. As a precondition, you can assume 
 * that the stack has at least two nodes. This function pops the front (top) 
 * two nodes, combines them into a single node, and pushes the new node back 
 * onto the stack. See Huffman_Coding.pdf to understand conceptually how this
 * should be done.
 */
void Stack_popPopCombinePush(Stack * stack)
{
  HuffNode * tree1 = Stack_popFront(stack); 
  HuffNode * tree2 = Stack_popFront(stack); 
  
  HuffNode * tree3 = HuffNode_create(0);
  tree3->left = tree2; 
  tree3->right = tree1; 

  Stack_pushFront(stack, tree3); 
}

// ---------------------------------------------------- Reading HuffTree headers

/**
 * Read a Huffman Coding Tree (in text format) from 'fp'.
 */
HuffNode * HuffTree_readTextHeader(FILE * fp)
{
  int iter = 0;
  int c; 
  if( fp == NULL) 
    { 
      return NULL; 
    } 
  Stack * stack = Stack_create(); 
  while(iter != -1)
    { 
      if(fgetc(fp) == '1')
	{ 
	  c = fgetc(fp);
	 HuffNode * tree  =  HuffNode_create(c);  
	 Stack_pushFront(stack,tree);
	} 
      else 
	{
	  if(stack->head->next != NULL) 
	    {
	      Stack_popPopCombinePush(stack);
	    }
          else 
            { 
	      iter = -1;
	    }
	}
    } 
  HuffNode * trees = stack->head->tree;
  free(stack-> head); 
  free(stack);
  return trees;
}

/**
 * Read a Huffman Coding Tree (in binary format) from 'fp'.
 * You will need to (conceptually) read a file a bit at a time. See the README
 * for hints on how to do this.
 */
// Code used from Pr. Lu's online textbook. 
int readBit(FILE * fptr, unsigned char * bit, unsigned char * whichbit, unsigned char * curbyte) 
{
  int ret = 1; 
  if((*whichbit) == 0) 
    { 
      // read a byte from a file
      ret = fread(curbyte, sizeof(unsigned char), 1, fptr); 
    } 
  if(ret != 1) 
    { 
      return -1; 
    } 
  unsigned char temp = (*curbyte) >> (7-(*whichbit));
  temp = temp & 0X01; 
  *whichbit = ((*whichbit) + 1) % 8; 
  *bit = temp; 
  return 1; 
 
}
// Code used from Pr. Lu's online textbook. 
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
 int iter = 0;
  unsigned char whichbit = 0;
  unsigned char curbyte = 0;
  unsigned char onebit = 0;
  Stack * stack = Stack_create() ;
  // decreasing to ensure the list is a stack
  while (iter == 0)
  {
    readBit (fp ,& onebit ,& whichbit ,& curbyte );
    if (onebit == 1)
    {
      int bitcount ;
      unsigned char value = 0;
      for (bitcount = 0; bitcount < 8; bitcount ++)
      {
        value <<= 1; // shift left by one
        readBit (fp, & onebit, & whichbit, &curbyte );
        value |= onebit ;
      }
      HuffNode * tn = HuffNode_create(value);
      Stack_pushFront(stack, tn);
    }
    else
    {
      if (stack->head->next != NULL)
      {        
	Stack_popPopCombinePush(stack);
      }
      else
      {    
	iter = 1;
      }
    }
  }
  HuffNode * root = stack->head->tree;
  free (stack->head );
  free(stack);
  return root ;
}
