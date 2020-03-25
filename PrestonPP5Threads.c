//Matthew Preston
//CSCI 2271
//PP5, due 4/14/2018

#ifndef _PRESTONPP5THREADS_H
#define _PRESTONPP5THREADS_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "PrestonPP5Threads.h"
#include "pthread.h"

int NUM_OF_CYCLES = 10;

pthread_mutex_t lock;
pthread_cond_t self;
sensor_t *head1;
//pthread_mutex_init(&lock, NULL);
//pthread_cond_init(&cond, NULL);

void sensors(void *t)
{
  int *t1 = (int *)t;
  int sensorNum, cycles = 1;
  sensorNum = *t1 + 1;
  while (cycles <= NUM_OF_CYCLES) {
    addToList(sensorNum, cycles);
    //printf("test1\n");
    lastSensorInCycle(sensorNum);
    //printf("test2\n");
    waitForCycleToFinish(sensorNum,cycles);
    cycles++;
    head1 = NULL;
  }
  printf("all cycles completed %d is done\n", sensorNum);
  printf("\n");
  pthread_exit(NULL);
}

sensor_t *addToRear(sensor_t *head, sensor_t *newNode)
{
  //figure this out
  if(head == NULL)
  {
    return newNode;
  }

  sensor_t *traverse = (sensor_t *)malloc(1*sizeof(sensor_t));
  traverse = head;
  traverse->next = head->next;

  while(traverse->next != NULL)
  {
    printf("Going to next sensor!\n");
    traverse = traverse->next;
  }
  //so now traverse->next == NULL
  traverse->next = newNode;
  return head;
}

void addToList(int t, int cycles)
{
  sensor_t *s = (sensor_t *)malloc(1*sizeof(sensor_t));
  pthread_mutex_lock(&lock);
  //this is the critical section, creating a new node to insert into the linked list
  //figure this out
  s->next = NULL;
  s->number = t;
  s->cycle = cycles;
  s->temp = 1 + rand() % 100;
  head1 = addToRear(head1, s);
  pthread_mutex_unlock(&lock);
}

void waitForCycleToFinish(int t, int cycles) {
  pthread_mutex_lock(&lock);
  while (test(t, cycles)  /*i can't go*/) {
    //figure this out
    pthread_cond_wait(&self, &lock);
  }
  pthread_mutex_unlock(&lock);
}

int test(int t, int cycles)
{
  sensor_t *s = head1;
  while(s->next != NULL)
  {
    if(s->cycle != cycles){ return 1; }
    s = s->next;
  }
  return 0;
}

void lastSensorInCycle(int t) {
  pthread_mutex_lock(&lock);
  //figure this out
  sensor_t *search = head1;
  if(head1 == NULL){ return; }
  while(search->number != t)
  {
    search = search->next;
  }
  int temper = search->temp;
  int name = search->number;
  int cycle = search->cycle;
	printf("Sensor Temperature: %d,\t Sensor Name: %d,\t Cycle: %d\n", temper, name, cycle);
  //printf("Kicking off next cycle\n");
  //head1 = NULL;
  pthread_cond_broadcast(&self);

  pthread_mutex_unlock(&lock);
}

#endif
