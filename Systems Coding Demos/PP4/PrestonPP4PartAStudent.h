//Matthew Preston
//PP4 due 26 March 2018
//CSCI 2271

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct student {
   int id;
   char* name;
}student_t;

char *toString(void *any);
