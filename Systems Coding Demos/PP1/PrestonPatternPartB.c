//Matthew Preston
//CSCI 2271
//PP1, due 2/9/2018

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//reads in a line of characters and spits out the line reversed

int main()
{
  //get our initial ars
  //char patterns[80];
  //char patternFind[4];
  char *patterns = (char*)malloc(80*sizeof(char));
  char *patternFind = (char*)malloc(4*sizeof(char));
  char *anchorP = patterns;

  char *anchorF = patternFind;
  char *aP = anchorF;

  *aP++ = 'G';
  *aP++ = 'C';
  *aP++ = 'A';
  *aP++ = 'G';

  aP = anchorF;

  //test:
  //printLine(patternFind,4);
  //for(int x = 0; x < 4; x++) { printf("%c\n", *aP++); }

  int i,size = 0;

  printf("Please enter patterns of length less than 80 characters. \n");
  printf("TEXT   : \t");
  size = getLine(patterns);

  if(size>=81)
  {
    printf("You ignored this instructions and inputed a line too long. \n");
    printf("Terminating program. \n");
    return(EXIT_FAILURE);
  }

  //printLine(patterns,size);
  printf("PATTERN: \t");
  printLine(patternFind,4);

  int place = findmatch(anchorF, anchorP, size);
  if(place >= 0)
  {
    printf("A Match Has Been Found!!!!\n");
    printf("And It Starts At location %d (starting from the left at 0).\n", place);
    printRemains(anchorP,place,size);
  }
  else
  {
    //place = -1
    printf("No Matches found.\n");
  }

  free(patterns);
  free(patternFind);

  return(EXIT_SUCCESS);
}

int getLine(char *line)
{
  char *a,b;
  int i,size = 0;
  a = line;
  b = getchar();
  while(b != '\n') //&& size < 80)
  {
    *(a+size) = b;
    size++;
    //exceed the character limit:
    if(size == 80){return 100;}
    b = getchar();
  }
  return size;
}

void printLine(char *line, int size)
{
  char *a;
  int i;
  a = line;
  for (i=0; i<size; i++)
  {
  //printf("a = %c\n",*(a+i));
  printf("%c",*(a+i)); //no end of lineprintf("\n");
  }
  printf("\n");
}

//returns index if pattern found
//returns -1 if pattern isn't found
int findmatch(char *pat, char *line, int sizeL)
{
  char *a = pat;
  char *anchor = pat;
  char *b = line;

  char *endC2 = pat+3;//&pat[3];
  char *endC1 = line+sizeL-1;//&line[sizeL-1];

  //printf("Data: %c,%c\n", endC2,endC1);

  //printf("First Chars of pat: %c\n", *a);
  //printf("First Chars of input: %c\n", *b);

  int g1Bool = 0;
  int cBool = 0;
  int aBool = 0;
  int gcaBool = 0;

  int intPlaceRet = -1;

  int g1Places[80];
  int *g1Pl = g1Places;
  int *g1Anc = g1Pl;
  //int sz = 0;

  for(int permutations = 0; permutations <= sizeL; permutations++)
  {
    //if we find a 'G':
    if(*b=='G')
    {
      g1Bool++; //= g1Bool + 1;
      //record where the 'G' is:
      //intPlaceRet = permutations;
      *g1Pl = permutations;
      //get to the next spot
      g1Pl++;
      //sz++;

      //move up if first stop
      if(a == anchor)
      {
        *a++;
      }

      if(g1Bool >= 1 && cBool == 1 && aBool == 1)
      {
        //We found the last G out of G C A G:
        gcaBool = 1;
        //The first G of the thing we found is the second to last g:
        //intPlaceRet = *g1Pl;
        //printLine(g1Places, sz);
        //free(g1Anc);
        break;
      }
    }

    //Look for the C and A
    if(*a==*b && *b != 'G')
    {
      //find C and A

      //If we've passed G, we're now onto C:
      if(g1Bool >= 1 && cBool == 0)
      {
        //move up:
        a++;
        cBool = 1;
      }

      else if(g1Bool >= 1 && cBool == 1 && aBool == 0)
      {
        //move up:
        a++;
        aBool = 1;
      }
    }
    /*else if(g1Bool == 1 && cBool == 1 && aBool == 1 && permutations >= sizeL && endC2 == endC1)
    {
      //hopefully this works for the end?
      g2Bool++;
      break;
    }*/

    //keep going up the input
    b++;
  }

  if(g1Bool >= 1 && cBool >= 1 && aBool >= 1 && gcaBool >= 1){ intPlaceRet = *g1Anc; }
  else { intPlaceRet = -1; }

  return intPlaceRet;
}

void printRemains(char *line, int indexOfMatch, int size)
{
  printf("(after the first 'G'...)\n");
  char *aP1 = line + indexOfMatch;
  for(int x = 0; x < size - indexOfMatch; x++) { printf("%c ", *aP1++); }
  printf("\n");
}
