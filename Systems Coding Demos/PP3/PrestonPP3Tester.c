//Matthew Preston
//CSCI 2271
//PP2, due 2/20/2018

#ifndef _PRESTONPP3_H
#define _PRESTONPP3_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "PrestonPP3.c"
#include "PrestonPP3.h"

int main()
{
  //printf("Reading in chunks of data...\n");

  lLab_t firstLine;
  lLab_t *firstL = &firstLine;

  //firstLine.firstChar = getchar();
  //printf("%c, \n\n", firstLine.firstChar);

  firstLine.firstChar = readLine(firstLine.firstChar);

  //printLine(firstLine.firstChar);

  lLab_t nextLine;

  firstLine.next1 = NULL;

  int place = 80;

  char *whereAreWe = firstLine.firstChar;

  while(1)
  {
    //next 80 chars:
    whereAreWe = readLine(firstLine.firstChar+place);

    addToLinkedList(firstL, whereAreWe);

    //we see a '\n':
    if(endingLine(whereAreWe)){ break; }

    place += 80;
  }

  printLines(firstL);

  return(EXIT_SUCCESS);
}

#endif
