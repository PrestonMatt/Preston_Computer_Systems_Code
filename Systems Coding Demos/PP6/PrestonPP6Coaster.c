//Matthew Preston
//CSCI2271
//PP6 Due 4/27/2018

#ifndef __PRESTONPP6COASTER_H
#define __PRESTONPP6COASTER_H

#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "PrestonPP6Coaster.h"
#include <unistd.h>

void riding(int *ticket)
{
  int passengerNum = *ticket + 1;

  waiting_man();
  addToList(passengerNum);
  finishOffCar();

  printf("Unloading passengers, %d off\n", passengerNum);

  pLasts();

  pthread_exit(NULL);
}

void waiting_man()
{
  pthread_mutex_lock(&mutLock);

  while (coasterC == 1){ pthread_cond_wait(&q, &mutLock); }

  pthread_mutex_unlock(&mutLock);
}

void addToList(int ticket)
{
  pthread_mutex_lock(&mutLock);

  printf("Loading passengers; %d on ride number: %d\n", ticket, Scycle);
  Scoaster += 1;
  St += 1;

  if((Scoaster == carN)||(St == passN))
  {
    if(St == passN) { puts("\nLAST CUSTOMER! No more business :( "); }

    else if(Scoaster == carN) { puts("\nFull coaster, and riding"); }

    coasterC = 1;

    pthread_cond_signal(&c);
  }

  if(Scoaster == 1) { connectCycles = 1; }

  pthread_mutex_unlock(&mutLock);
}

void finishOffCar()
{
  pthread_mutex_lock(&mutLock);

  while (connectCycles == 1) { pthread_cond_wait(&cq, &mutLock); }

  pthread_mutex_unlock(&mutLock);
}

void theRide()
{
  while (Scycle <= (passN/carN) + 1)
  {
    ontoC();

    sleep(1);
    puts("Whee!\n");
    puts("=== [ :) ]> === \t =============== \t =============== \t =============== \t");

    sleep(1);
    puts("=============== \t === [ :) ]> === \t =============== \t =============== \t");

    sleep(1);
    puts("=============== \t =============== \t === [ :) ]> === \t =============== \t");

    sleep(1);
    puts("=============== \t =============== \t =============== \t === [ :) ]> === \t");

    offC();
  }
  waiting_last_man();
  printf("Coaster done. \n");

  pthread_exit(NULL);
}

void pLasts()
{
  pthread_mutex_lock(&mutLock);

  Scoaster -= 1;
  if(Scoaster == 0)
  {
    //LAST PASSENGER
    coasterC = 0;
    puts("\nlast pass, empty car");

    for(int i = 0; i < carN; i++) { pthread_cond_signal(&q); }

  }

  pthread_mutex_unlock(&mutLock);
}

void ontoC()
{
  pthread_mutex_lock(&mutLock);

  while (Scoaster != carN && St != passN){ pthread_cond_wait(&c, &mutLock); }

  pthread_mutex_unlock(&mutLock);
}

void offC()
{
  pthread_mutex_lock(&mutLock);

  printf("Ride no.%d complete.\n\n", Scycle);
  connectCycles = 0;
  Scycle += 1;

  //wake up sheeple
  pthread_cond_broadcast(&cq);
  pthread_mutex_unlock(&mutLock);
}

void waiting_last_man()
{
  pthread_mutex_lock(&mutLock);

  while (coasterC == 1) { pthread_cond_wait(&q, &mutLock); }

  pthread_mutex_unlock(&mutLock);
}

void cycleController()
{
  coasterC, Scoaster, St, connectCycles = 0;
  Scycle = 1;
}

int main(int argc, char *argv[])
{
  //They put in wrong stuff
  if(argc > 3 || argc < 3)
  {
    puts("The arguements given don't work.");
    puts("Example: ./exe_name passenger capacity");
    exit(EXIT_SUCCESS);
  }

  //You've got the right stuff
  passN = atoi(argv[1]);
  carN = atoi(argv[2]);

  //printf("Test: Number of passengers:\t %d\nCar capacity:\t\t %d\n", passN, carN);

  pthread_t s[passN];
  pthread_t c;

  pthread_mutex_init(&mutLock, NULL);
  cycleController();
  pthread_create(&(c), NULL, (void*)theRide, NULL);

  puts("\nThe thread-mobile-coaster will go for 4 seconds, see the animation.\n");

  int *on;
  int count = 0;

  while(count < passN)
  {
    on = (int *)malloc(sizeof(int));
    *on = count;

    pthread_create(&(s[count]), NULL, (void*)riding, on);

    count += 1;
  }

  pthread_join(c, NULL);
  exit(EXIT_SUCCESS);
}

#endif
