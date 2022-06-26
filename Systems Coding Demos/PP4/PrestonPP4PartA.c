//Matthew Preston
//CSCI 2271
//PP4, due 3/26/2018

#ifndef _PRESTONPP4PARTA_H
#define _PRESTONPP4PARTA_H

//#ifndef _PRESTONPP4PARTASTUDENT_H
//#define _PRESTONPP4PARTASTUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "PrestonPP4PartA.h"
//#include "PrestonPP4PartAStudent.h"
//#include "PrestonPP4PartAStudent.c"

//Adds a node to the end of the list, and returns the pointer to the first node in the list
node_t* add(node_t* first, void* toAdd)
{
  if(toAdd == NULL)
  {
    printf("Invalid input.\n");
    return;
  }

  node_t *addMe = (node_t *)malloc(sizeof(node_t));
  node_t *previous = first;

  addMe->item = toAdd;
  addMe->next = NULL;

  //The linked list is empty:
  if(previous->item == NULL)
  {
    //printf("You passed me an empty list, dummy!\n");
    addMe->prev = NULL;
    return addMe;
  }

  while(previous->next != NULL)
  {
    previous = previous->next;
  }

  previous->next = addMe;
  addMe->prev = previous;

  //printf("%p %p\n", addMe->prev, addMe->next);
  //printf("Data:%p added.\n", addMe->item);

  return first;
}

//Returns next node's data:
node_t* next(node_t* previous, char *(*toString)(void *))
{
  if(previous->next == NULL)
  {
    printf("You've reached the end of the list.\n");
    return NULL;
  }
  //printf("Next Node: ");
  //printNode(previous->next, toString);
  return previous->next;
}

node_t* prev(node_t* next, char *(*toString)(void *))
{
  if(next->prev == NULL)
  {
    printf("You've reached the beginning of the list.\n");
    return NULL;
  }
  //printf("Previous Node: ");
  //printNode(next->prev, toString);
  return next->prev;
}

//delete's a node:
node_t* delet(node_t *first, node_t* deleteMe)
{
  node_t *current = first;

  if(first == deleteMe)
  {
    (deleteMe->next)->prev = NULL;
    return deleteMe->next;
  }

  while(current != deleteMe)
  {
    current = current->next;
  }

  if(current->next != NULL)
  {
    (current->next)->prev = current->prev;
  }

  if(current->prev != NULL)
  {
    (current->prev)->next = current->next;
  }

  return first;

  /*printf("Today I am deleting\n");
  printNode(deleteMe);

  if(deleteMe == NULL)
  {
    return;
  }

  //printNode(deleteMe);

  //it's the first one:
  if(deleteMe->prev == NULL || first == deleteMe)// || first == deleteMe)
  {
    deleteMe->next->prev = NULL;
    return;
  }
  else if(deleteMe->next == NULL)
  {
    deleteMe->prev->next = NULL;
    return;
  }

  //if it's in the list and not the first one:
  if(deleteMe->prev != NULL)
  {
    deleteMe->prev = deleteMe->next->prev;
  }

  //if it's in the list and not the last one:
  if(deleteMe->next != NULL)
  {
    deleteMe->next = deleteMe->prev->next;
  }
  //So I basically glued the next and previous nodes together! lol*/
}

//prints the payload for the 3rd node:
void* printNodeThree(node_t* firstNode, char *(*toString)(void *))
{
  node_t *n = firstNode;
  node_t *n1 = firstNode->next;
  if(n->next == NULL || n1->next == NULL)
  {
    printf("No third node in list!\n");
    return NULL;
  }

  printNode(n1->next, toString);
  node_t *three = n1->next;
  return three;
}

//given int n and the first node in the list this function prints data of node at index n, and returns that data
void* printNodeN(int n, node_t* first, char *(*toString)(void *))
{
  node_t *current = first;

  n--;

  for(int x = 0; x < n; x++)
  {
    if(current->next == NULL)
    {
      printf("No node at given index.\n");
      return NULL;
    }
    current = current->next;
  }

  //We're at index n:
  printNode(current, toString);
  return current->item;
}

void printAll(node_t *firstNode, char *(*toString)(void *))
{
  printf("First:\t");
  node_t *nextN = firstNode;
  while(printNode(nextN, toString)!=1)
  {
    printf("Next:\t");
    nextN = nextN->next;
  }
  //printf("Last:\t");
  //printNode(nextN);
}

int printNode(node_t *any, char* (*toStr)(void *))
{
  //printf("%d\n", (int)toStr);
  //printf("%d\n", (any->item > 0));
  if(any == NULL || any->item == NULL)
  {
    printf("There is no data for this node!\n");
  }
  else
  {
    //printf("Test!\n");
    printf("Node's data: %s\n", (*toStr)(any->item));
  }
  if(any->next == NULL)
  {
    return 1;
  }
  return 0;
}

/*
char *toString(void *any)
{
  char * buffer;
  node_t *s;
  s = (node_t *)any;
	buffer = (char *) malloc(sizeof(char)*200);

  if((char*)s->item == NULL)
  {
    student_t *st = s->item;
    char* c = st->id;
    c += st->name;

    sprintf(buffer,"ITEM: %s,\t Next node: %d,\t Previous Node: %d",
    c, (int)s->next, (int)s->prev);

    return buffer;
  }

  //test:
  //printf("%s\n", s->item);

	sprintf(buffer,"ITEM: %s,\t Next node: %d,\t Previous Node: %d",
  (char*)s->item, (int)s->next, (int)s->prev);
  return buffer;
}
*/

#endif
//#endif
