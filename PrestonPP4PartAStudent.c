//Matthew Preston
//CSCI 2271
//PP4, due 3/26/2018

#ifndef _PRESTONPP4PARTASTUDENT_H
#define _PRESTONPP4PARTASTUDENT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "PrestonPP4PartAStudent.h"

char *toString(void *any)
{
  char * buffer;
  student_t *s;
  s = (student_t *)any;
	buffer = (char *) malloc(sizeof(char)*200);

  //test:
  //printf("%s\n", s->item);

	sprintf(buffer,"Student ID: %d,\t Student Name: %s",
  (int)s->id, (char*)s->name);
  return buffer;
}

#endif
