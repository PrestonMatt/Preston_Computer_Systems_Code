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

  int size = 0;

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

  int numPatterns = findmatch(anchorF, anchorP, size);
  if(numPatterns >= 1)
  {
    printf("Match(es) Has Been Found!!!!\n");
    printf("There are %d match(es)\n", numPatterns);
    //printRemains(anchorP,numPatterns,size);
  }
  else
  {
    //numPatterns = -1 or 0
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

int findmatch(char *pat, char *line, int sizeL)
{
  int numPats = 0;

  char *gcagPat = pat;
  char *inputData = line;
  int sizeL1 = sizeL;

  //while there are still patterns inside
  while(findmatch2(gcagPat, inputData, sizeL1) > -1)
  {
    numPats++;
    //printf("Found one pattern.");
  }
  return numPats;

  //Ok let me explain what I am doing here.
  //I already solved how to find one pattern in a function
  //so why not call that function until I see no more patterns?
  //I blot out the CA in GCAG so it doesn't recognize repeats
  //i.e. => GCAG --> GNNG
}

int findmatch2(char *pat, char *line, int sizeL)
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
  int g2Bool = 0;

  int foundIt = 0;

  int intPlaceRet = 0;

  //int permutations = 0;
  for(int permutations = 0; permutations <= sizeL; permutations++)
  {

    char temp1 = *a;
    char temp2 = *b;

    if(*a==*b)
    {
      //find G1
      if(g1Bool == 0)
      {
        a++;
        g1Bool = 1;
        intPlaceRet = permutations;
        //printf("Found the first G!\n");
      }
      else if(g1Bool == 1 && cBool == 0)
      {
        a++;
        cBool = 1;
        *b='N';
        //printf("Found the C!\n");
      }
      else if(g1Bool == 1 && cBool == 1 && aBool == 0)
      {
        a++;
        aBool = 1;
        *b='N';
        //printf("Found the A!\n");
      }
      else if(g1Bool == 1 && cBool == 1 && aBool == 1)// && g2Bool == 0)
      {
        //printf("Found the second G!\n");
        //printf("Found the pattern!!\n");
        foundIt++;
        break;
        //gonna return intPlaceRet;
      }
    }
    else if(g1Bool == 1 && cBool == 1 && aBool == 1 && permutations >= sizeL && endC2 == endC1)
    {
      //hopefully this works for the end?
      foundIt++;
      break;
    }
    else
    {
      a = anchor;
      g1Bool = 0;
      cBool = 0;
      aBool = 0;
      g2Bool = 0;
      if(foundIt == 1)
      {
        break;
      }
      else
      {
        intPlaceRet = -1;
      }
      //printf("Reset pattern find :(\n");
    }
    //keep going up the input
    b++;

    //printf("We just checked from the pattern, %c\n", temp1);
    //printf("%c", temp1);
    //printf("\n");
    //printf("and text, %c\n", temp2);
    //printf("%c", temp2);
    //printf("\n");

  }
  //printLine(line,sizeL);
  //char *blotMe = line + intPlaceRet;
  //printf("%c\n", blotMe);
  //*blotMe = 'N'
  return intPlaceRet;
}

//First attempt:

/*//returns number of patterns found
int findmatch(char *pat, char *line, int sizeL)
{
  char *a = pat;
  char *anchor = pat;
  char *b = line;

  //int geeCountBool = 0;
  //int ceeCountBool = 0;
  //int ayyCountBool = 0;

  int numMatches = 0;

  //find number of matches:
  for(int index = 0; index <= sizeL; index++)
  {
    if(*b == 'G')
    {
      //Check if end of pattern:
      if(a != anchor)
      {
        numMatches++;
        //reset a pointer back to the beginning to find another match
        a = anchor;
      }
      //Otherwise we're at the beginning of the pattern:
      else
      {
        a++;
      }
    }

    //now let's see what to do when we find G
    if(*b == 'C' && a != anchor && *a == 'C')
    {
      //if we're at the begginning of the pattern,
      //then we just found a random 'C'
      //that is a == anchor
      //if a is still at anchor, it's still at the 'G' state

      //but this checks:
      //didn't find rancom 'C'
      //rather we found the pattern
      //move from 'C' state to 'A' state
      a++;
    }

    if(*b == 'A' && a != anchor && *a == 'A')
    {
      //we find an 'A' at the A state
      a++;
    }

    //if the pattern is interrupted, reset
    if(*b != *a)
    {
      a = anchor;
    }

    //scroll through the input data each time
    b++;
  }
  return numMatches;
}*/
