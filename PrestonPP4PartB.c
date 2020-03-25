//Matthew Preston
//CSCI 2271
//PP4, due 3/26/2018

#ifndef _PRESTONPP4PARTA_H
#define _PRESTONPP4PARTA_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include "PrestonPP4PartA.h"
#include "PrestonPP4PartA.c"

typedef struct square{
char * color;    // the color of the space. either red, blue, orange or green;
char * special;  // the special space. There are four values for special spaces: GOBACK, GOFORWARD
                 // WIN and NONE (i.e. nothing special)
int x;           // if you land on a special space, this is how many spaces to move.
                 //If you land on WIN, the game is over and you win.
}square_t;

typedef struct player{
  node_t *pos; //where the player is on the board.
  int win_condition;
}player_t;

int randomNumber(int upperBound);
square_t* createBoardSpace(FILE *myFile);
char* toString(void *b);
node_t* putNodeInBoard(square_t* board);
char* convertToColor(int x);
square_t *takeTurn(node_t *space);
node_t * move(char* lookingForColor, node_t* currentSpace);
node_t * specials(node_t* currentSpace);

int main()
{
  srand((unsigned)time(NULL));
  //printf("My program is slow because I need to wait every second for a new seed to get a different roll.\n");
  //printf("Please bear with it for 5 games. Thank you! :) \n\n");

  typedef char* (*printMe)(void*);
  printMe strFunc = &toString;

  //read in board;
  square_t* board;
  FILE *fp;
  fp = fopen("board.txt","r");

  node_t first;
  first.item = NULL;
  first.next = NULL;
  first.prev = NULL;
  node_t *f = &first;

  printf("Board:\n\n");

  while(1)
  {
    board = createBoardSpace(fp);
    if(board == NULL)
    {
      break;
    }
    //toString(board);
    f = add(f, board);
  }
  //puts("All done.");
  fclose(fp);

  //test:
  printAll(f, strFunc);

  float turnsAvg = 0.0;

  for(int j = 0; j < 5; j++)
  {
    printf("\n");
    printf("Game #%d:\n\n", j+1);

    //place player at pos = 0 or first position.
    player_t p1;
    p1.pos = f;
    p1.win_condition = 1;

    int numTurns = 0;

    while(p1.win_condition)
    {
      //sleep(1);
      numTurns++;
      //print space and roll:
      node_t* newSpace = p1.pos;
      square_t *aSpace = newSpace->item;
      printf("On %s and ", toString(aSpace));
      int rn = randomNumber(4);
      char* spinnedColor = convertToColor(rn);
      printf("spinned a %s,\n", spinnedColor);//"%d, aka %s\n", rn, spinnedColor);

      node_t*check = p1.pos;

      //move:
      p1.pos = move(spinnedColor, newSpace);
      newSpace = p1.pos;

      //follow special instructions (sans winning) on board:
      p1.pos = specials(newSpace);
      //if(check != newSpace){ printf("On %s and ", toString(aSpace)); }

      //check if the space you're on is winning;
      p1.win_condition = checkWin(p1.pos);
      //printf("%d win\n", p1.win_condition);

    }
    printf("You Won!\n");
    turnsAvg += (float)numTurns;
  }
  printf("\n");
  printf("The average number of turns it takes for 5 games is: %f\n", (turnsAvg/5.0));

  return(EXIT_SUCCESS);
}

/*
node_t* putNodeInBoard(square_t* board)
{
  //printf("Adding Board Space to List.\n");
  typedef char* (*printMe)(void*);
  printMe strFunc = &toString;

  node_t *n = (node_t*)malloc(sizeof(node_t)*1);
  n->item = board;
  n->next = NULL;
  n->prev = NULL;

  //printNode(n, strFunc);

  return n;
}
*/

node_t * specials(node_t* currentSpace)
{
  typedef char* (*printMe)(void*);
  printMe strFunc = &toString;

  node_t *thisSpace = (node_t*)malloc(sizeof(node_t)*1);
  thisSpace = currentSpace;
  square_t *t_Space = (square_t*)malloc(sizeof(square_t)*1);
  t_Space = thisSpace->item;

  int x = t_Space->x;
  char* spe = t_Space->special;

  //printf("%d %s\n", t_Space->x,t_Space->special);
  char* forward = "GOFORWARD";
  char* forwardTypo = "GOFOWARD";
  char* back = "GOBACK";

  if(strcmp(spe, forward) == 0 || strcmp(spe, forwardTypo) == 0)
  {
    printf("On %s and need to move", toString(t_Space));
    printf(" FORWARD %d space(s).\n", x);
    for(int i = 0; i < x; i++)
    {
      //printf("MOVING...\n");
      thisSpace = next(thisSpace, strFunc);
      t_Space = thisSpace->item;

      if(t_Space == NULL)// && strcmp(lookingForColor, n_Space->color))
      {
        printf("Invalid Game Board. Ignoring Special.\n");
        return currentSpace;
      }
    }
    return thisSpace;
  }
  else if(strcmp(spe, back) == 0)
  {
    printf("On %s and need to move", toString(t_Space));
    printf(" BACK %d space(s).\n", x);
    for(int i = 0; i < x; i++)
    {
      //printf("MOVING...2...\n");
      thisSpace = prev(thisSpace, strFunc);
      t_Space = thisSpace->item;

      if(prev(thisSpace, strFunc) == NULL)// && strcmp(lookingForColor, n_Space->color))
      {
        printf("Invalid Game Board. Ignoring Special.\n");
        return currentSpace;
      }
    }
    return thisSpace;
  }
  else { return currentSpace; }
}

int checkWin(node_t* b)
{
  square_t *space = b->item;
  char* spe = space->special;
  char* w = "WIN";
  //printf("%d, win1", strcmp(spe, w));
  return strcmp(spe, w);
}

node_t * move(char* lookingForColor, node_t* currentSpace)
{
  typedef char* (*printMe)(void*);
  printMe strFunc = &toString;

  node_t *nextSpace = (node_t*)malloc(sizeof(node_t)*1);
  nextSpace = next(currentSpace, strFunc);
  square_t *n_Space = (square_t*)malloc(sizeof(square_t)*1);
  n_Space = nextSpace->item;

  while(strcmp(n_Space->color, lookingForColor))
  {
    if(next(nextSpace, strFunc) == NULL)// && strcmp(lookingForColor, n_Space->color))
    {
      printf("Need to roll again, didn't roll the winning space.\n");
      return currentSpace;
    }

    nextSpace = next(nextSpace, strFunc);
    n_Space = nextSpace->item;
  }
  return nextSpace;
}

char* convertToColor(int x)
{
  char* r = (char*)malloc(sizeof(char)*3);
  r = "RED";
  char* b = (char*)malloc(sizeof(char)*4);
  b = "BLUE";
  char* o = (char*)malloc(sizeof(char)*6);
  o = "ORANGE";
  char* g = (char*)malloc(sizeof(char)*5);
  g = "GREEN";
  char* i = (char*)malloc(sizeof(char)*7);
  i = "INVALID";

  if(x == 1){ return r; }
  if(x == 2){ return b; }
  if(x == 3){ return o; }
  if(x == 4){ return g; }
  if(x != 1 || x != 2 || x != 3 || x != 4)
  {
    printf("Invalid data.\n");
    return i;
  }
}

int randomNumber(int upperBound)
{
  //srand(time(NULL));
  //srand((unsigned)time(NULL));
  //this is the simple rn generator that generates a random number between 1 and upperBound
  int j;
  j=1+(rand() % upperBound);
  return j;
}

square_t * createBoardSpace(FILE *myFile)
{
  char dummy;
  int tempInt;
  square_t *board;

  board = (square_t*)malloc(sizeof(square_t));
  board->color = (char*)malloc(sizeof(char) *10);
  board->special = (char*)malloc(sizeof(char) *10);
  fscanf(myFile, "%s%s%d%c", board->color, board->special, &tempInt, &dummy);

  if(feof(myFile)){ return NULL; }

  board->x = tempInt;
  return board;
}

char* toString(void *b)
{
  char * buffer;
  square_t *s;
  s = (square_t *)b;
	buffer = (char *)malloc(sizeof(char)*200);

  //char* color = s->color;
  //char* special = s->special;
  //int x = s->x;

  //printf("the board space: %s %s %d\n",s->color, s->special, s->x);

	sprintf(buffer, "the board space: %s %s %d",
  s->color, s->special, s->x);
  return buffer;
}

#endif
