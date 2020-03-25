//Matthew Preston
//PP4 due 26 March 2018
//CSCI 2271

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct node{
   void * item;
   struct node * next;
   struct node * prev;
}node_t;

typedef struct student {
   int id;
   char* name;
}student_t;

//Adds a node to the end of the list given data of what to add
node_t* add(node_t* first, void* toAdd);
//Returns next node's data:
node_t* next(node_t* previous, char *(*toString)(void *));
//returns the previous node:
node_t* prev(node_t* next, char *(*toString)(void *));
//delete's a node:
node_t* delet(node_t *first, node_t* deleteMe);
//prints the payload for the 3rd node:
void* printNodeThree(node_t* firstNode, char *(*toString)(void *));
//Anything else?
//print nth node:
void* printNodeN(int n, node_t *first, char *(*toString)(void *));
//prints the linked list:
void printAll(node_t *firstNode, char *(*toString)(void *));
//prints a single node's item, given pointer to that node
//returns 1 if there is a next node, 0 otherwise
int printNode(node_t *any, char* (*toStr)(void *));
//converts node's item to data:
//char *toString(void *any);
