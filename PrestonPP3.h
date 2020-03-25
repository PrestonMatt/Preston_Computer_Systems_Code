//Matthew Preston
//PP3 due 2 March 2018
//CSCI 2271

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct lLab{
  char *firstChar;
  struct lLab *next1;
}lLab_t;

char *readLine(char *first);
void printLine(char *first);
int endingLine(char *sample);
void addToLinkedList(lLab_t *linkedChars, char *head);
void printLines(lLab_t *begin);
