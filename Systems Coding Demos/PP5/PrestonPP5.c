//Matthew Preston
//CSCI 2271
//PP5, due 4/14/2018

#ifndef _PRESTONPP5THREADS_H
#define _PRESTONPP5THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>
#include "PrestonPP5Threads.h"
#include "PrestonPP5Threads.c"

#define NUM_THREADS	9

void testAll();

int main()
{
  pthread_t threads[NUM_THREADS];

  int t;

  for(t = 0; t < NUM_THREADS; t++)
  {
    pthread_create(&threads[t], NULL, (void*)&sensors, (void*)&t);
  }

  //redundant:
  pthread_exit(NULL);
  return(EXIT_SUCCESS);
}

char* toString(void *any)
{
  char * buffer;
  sensor_t *s;
  s = (sensor_t *)any;
	buffer = (char *) malloc(sizeof(char)*200);

  //Make explicit variables for what's inside sensor.
  int temper = s->temp;
  int name = s->number;
  int cycle = s->cycle;

	sprintf(buffer,"Sensor Temperature: %d,\tSensor Name: %d,\tCycle: %d", temper, name, cycle);
  return buffer;
}

#endif
