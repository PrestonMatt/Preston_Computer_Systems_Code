//Matthew Preston
//CSCI 2271
//PP2, due 2/20/2018

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//Let's use Realloc to read in a line, pattern and see if that line has the pattern

char* readLine(char* beginMe, int size);
int findMatch(char* inputStream, char* pattStream);
int fsmExicute(char* inputStream, char* pattStream, int nT);

typedef struct states
{
  int IN_OUT;// = 0 if IN, 1 if OUT;
}states_t;

int main()
{
  char *inputStart;//endMe1, endMe2;

  printf("Enter a line to parse:\n");
  printf("TEXT   :\t");

  inputStart = readLine(inputStart, 100);
  //printf("%s\n", inputStart);

  printf("Enter a pattern to search for:\n");
  printf("PATTERN:\t");

  char * pattStart;

  pattStart = readLine(pattStart, 100);
  //printf("%s\n", pattStart);

  int numTimes = findMatch(inputStart, pattStart);
  if(numTimes)
  {
    printf("We found %d matches!\n", numTimes);
  }
  else
  {
    printf("We found nothing\n");
  }

  //free(inputStart);
  //free(pattStart);
  return(EXIT_SUCCESS);
}

//Inspiration for this here: https://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length
char* readLine(char* beginMe, int size)
{
  char *bgn, thisCh;
  bgn = beginMe;
  //int endOfLine;
  int length = 0;
  bgn = realloc(NULL, sizeof(char)*size);

  if(!bgn)return bgn;
  while(thisCh != '\n') //EOF != (thisCh = getchar())
  {
    thisCh = getchar();
    *(bgn + length++) = thisCh;
    if(length==size)
    {
      size+=16;
      bgn = realloc(bgn, sizeof(char)*size);
      if(!bgn)return bgn;
    }
  }
  *(bgn+length++) = '\0'; //end of string

  //char *r = (char*)realloc(bgn, sizeof(char)*length);
  char *y = (bgn);

  return y;
}

int findMatch(char* inputStream, char* pattStream)
{
  int numTim = 0;
  char *p = inputStream;
  char *q = pattStream;
  //while we keep finding patterns:
  while(fsmExicute(p, q, numTim) > 0)
  {
    numTim++;
    //printf("One Match Found!\n");
  }
  return numTim;
}

int fsmExicute(char* inputStream, char* pattStream, int nT)
{


  //printf("On pattern %d\n", nT);

  char* anc1 = inputStream;
  char* anc2 = pattStream;

  states_t fsm;
  fsm.IN_OUT = 0;

  while(*anc1 != '\0')
  {
    //printf("Beginning Search...\n");

    //first char of pattern
    if(fsm.IN_OUT == 0 && *anc1 == *anc2)
    {
      fsm.IN_OUT = 1;
      anc2++;
      //we're in bois!
      //So we can see if there are other patterns:
      if(*anc1 == 'R'){ *anc1 = 'N'; }
      else{ *anc1 = 'R'; }
      //printf("First!\n");
    }
    else if(fsm.IN_OUT > 0 && *anc1 != *anc2)
    {
      //We're out of the pattern:
      anc2 = pattStream;
      fsm.IN_OUT = 0;
    }
    else if(fsm.IN_OUT > 0 && *anc1 == *anc2)
    {
      anc2++;
    }

    if(*anc2=='\0' || *anc2 == '\n')
    {
      //printf("Do I ever get to this state?");
      return 1;
    }
    //printf("State: %d, Char: %c, Patt: %c\n", fsm.IN_OUT, (char)*anc1, (char)*anc2);
    anc1++;
  }
  return 0;
}
