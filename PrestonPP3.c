//Matthew Preston
//CSCI 2271
//PP2, due 2/20/2018

#ifndef _PRESTONPP3_H
#define _PRESTONPP3_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "PrestonPP3.h"

char* readLine(char* beginMe)
{
  //printf("Reading in chunks of data...\n");

  char *bgn, thisCh;
  bgn = beginMe;

  int length = 0;
  bgn = realloc(NULL, sizeof(char)*80);

  if(!bgn)return bgn;
  for(int i = 0; i < 80; i++)
  {
    //test:
    //printf("Len: %d, Char: %c\t", length, thisCh);

    thisCh = getchar();
    *(bgn + length++) = thisCh;

    if(thisCh == '\n')
    {
      //printf("...end of chunk.");
      break;
    }
  }
  //test:
  //printf("Done reading in line\n.");

  *(bgn+length++) = '\0'; //end of string

  char *y = (bgn);

  return y;
}

void printLine(char *first)
{
  printf("Chunk: ");
  char *n = first;
  for(int i = 0; i < 80; i++)
  {
    if(*n == '\n' || *n == '\0') {break;}
    printf("%c", *n++);
  }
  printf("\n");
}

int endingLine(char *sample)
{
  char *n = sample;
  for(int i = 0; i < 80; i++)
  {
    if(*n == '\n')
    {
      //printf("Last Line!\n");
      return 1;
    }
    n++;
  }
  return 0;
}

void addToLinkedList(lLab_t *linkedChars, char *head)
{
  //printf("adding this to a linked list...\n");

  lLab_t *current = linkedChars->next1;
  lLab_t *previous;
  //char *charsCopy;

  //printf("%d", current);

  //on second element:
  if(current == NULL)
  {
    current = (lLab_t *)malloc(1*sizeof(lLab_t));
    //current->next1 = malloc()
    current->next1 = NULL;
    current->firstChar = head;

    linkedChars->next1 = current;

    //printf("Added Second Link\n");
  }

  else
  {
    while(current != NULL)
    {
      previous = current;
      current = current->next1;
      //printf("Moving down the list.\n");
    }
    //printf("Error?\n");

    current = (lLab_t *)malloc(1*sizeof(lLab_t));
    current->firstChar = head;
    previous->next1 = current;

    current->next1 = NULL;

    //printf("Added another element on the list!");
  }
}

void printLines(lLab_t *begin)
{
  lLab_t *current = begin;
  while(current != NULL)
  {
    printLine(current->firstChar);
    current = current->next1;
  }
  printf("All Done!\n");
}

#endif
