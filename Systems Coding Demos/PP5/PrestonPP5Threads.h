//Matthew Preston
//CSCI 2271
//PP5, due 4/14/2018

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct sensor{
  int temp;
  int number;
  int cycle;
  struct sensor * next;
}sensor_t;

void sensors(void *t);
void addToList(int t, int cycles);
sensor_t *addToRear(sensor_t *head, sensor_t *newNode);
void waitForCycleToFinish(int t, int cycles);
int test(int t, int cycles);
void lastSensorInCycle(int t);
