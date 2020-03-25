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
#include "PrestonPP4PartA.h"
#include "PrestonPP4PartA.c"
//#include "PrestonPP4PartAStudent.c"
//#include "PrestonPP4PartAStudent.h"

void testAll();

int main()
{
  testAll();

  return(EXIT_SUCCESS);
}

char* toString(void *any)
{
  char * buffer;
  student_t *s;
  s = (student_t *)any;
	buffer = (char *) malloc(sizeof(char)*200);

  int id = s->id;
  char* name = (char*)s->name;

  //printf(id);
  //printf(name);

  //test:
  //printf("%s\n", s->name);

	sprintf(buffer,"Student ID: %d,\t Student Name: %s",
  id, name);
  return buffer;
}

void testAll()
{
  //create pointer to toString function to pass along.
  typedef char* (*printMe)(void*);
  printMe strFunc = &toString;

  printf("Step One: Build the list.\n");

  //Data (items):
  student_t matt;
  matt.id = 10000;
  char *myName = "Matthew Preston";
  matt.name = myName;

  student_t alex;
  alex.id = 10001;
  char *hisName = "Alexander DeGeorge";
  alex.name = hisName;

  student_t dan;
  dan.id = 10002;
  char *himName = "Daniel Garvey";
  dan.name = himName;

  student_t melly;
  melly.id = 10003;
  char *herName = "Melina Gilenberg";
  melly.name = herName;

  //nodes:
  /*node_t first;
  first.item = (student_t*)&matt;
  first.next = NULL; //should be second
  first.prev = NULL;

  node_t second;
  second.item = (student_t*)&alex;
  second.next = NULL;
  second.prev = NULL;

  node_t third;
  third.item = (student_t*)&dan;
  third.next = NULL;
  third.prev = NULL;

  node_t fourth;
  fourth.item = (student_t*)&melly;
  fourth.next = NULL;
  fourth.prev = NULL;

  node_t *f = &first;
  node_t *s = &second;
  node_t *t = &third;
  node_t *four = &fourth;*/

  //Addition:
  printf("Adding...\n");
  node_t first;
  first.item = NULL;
  first.next = NULL;
  first.prev = NULL;

  node_t* f = &first;

  f = add(f, &matt);
  f = add(f, &alex);
  f = add(f, &dan);
  f = add(f, &melly);
  printAll(f, strFunc);
  printf("\n");

  printf("Traversals...\n");
  prev(f, strFunc);
  node_t *s = next(f, strFunc);

  prev(s, strFunc);
  node_t *t = next(s, strFunc);

  prev(t, strFunc);
  node_t *w = next(t, strFunc);

  prev(w, strFunc);
  next(w, strFunc);
  printf("\n");

  printf("Calling and getting nth/third node...\n");
  printNodeN(1, f, strFunc);
  printNodeN(2, f, strFunc);
  printNodeThree(f, strFunc);
  printNodeN(4, f, strFunc);
  printNodeN(5, f, strFunc);
  printf("\n");

  printf("Deleting...\n");
  f = delet(f, s);
  printAll(f, strFunc);
  printf("\n");

  f = delet(f, w);
  printAll(f, strFunc);
  printf("\n");

  f = delet(f, f);
  printAll(f, strFunc);
  printf("\n");
}

#endif
//#endif
