//Matthew Preston
//CSCI2271
//PP6 Due 4/27/2018

#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"

int Scycle, connectCycles;
int coasterC, Scoaster, St;
int passN, carN;
pthread_mutex_t mutLock;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;
pthread_cond_t q = PTHREAD_COND_INITIALIZER;
pthread_cond_t cq = PTHREAD_COND_INITIALIZER;
void ontoC();
void offC();
void riding(int *ticket);
void addToList(int ticket);
void waiting_man();
void finishOffCar();
void theRide();
void pLasts();
void waiting_last_man();
void cycleController();
//Do I need this:
void extras();
void kill_off_extras();
