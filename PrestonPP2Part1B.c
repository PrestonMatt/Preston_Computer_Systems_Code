//Matthew Preston
//CSCI 2271
//PP2, due 2/20/2018

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct word
{
  char *firstChar;    //pointer to the first char in a word
  int count;      //number of times this word appears
  //struct lineNum *l;        //the linked list of lines this appears
  //int numLines;       //number of lines this appears
  //struct word *next;  //Next word
}word_t;

typedef struct states
{
  int IN_OUT;// = 1 if IN, 0 if OUT;
}states_t;

//Functions:
//char * readInString(char *lineBeginning);
char* readLine(char* beginMe, int size);
int findMatch(char* inputStream, char* pattStream);
int fsmExicute(char* inputStream, char* pattStream, int nT);

int main()
{
  int lineCount = 1;

  printf("Enter lines to parse:\n");
  printf("LINE %d   :\t", lineCount);

  char *line = (char*)malloc(1*sizeof(char));
  line = readLine(line, 10);
  printf("Last line was: %s\n", line);

  char *s = realloc(NULL, sizeof(char)*4); //4 chars in STOP
  (*(s+0) = 'S');
  (*(s+1) = 'T');
  (*(s+2) = 'O');
  (*(s+3) = 'P');
  printf("Last line was: %s\n", s);

  while(1)
  {
    printf("LINE %d   :\t", lineCount);
    char *lineNext = (char*)malloc(1*sizeof(char));
    lineNext = readLine(line, 10);
    printf("Last line was: %s\n", lineNext);

    if(lineCount >= 5)
    {
      printf("AAAAAAAAAAAAA\n");
      break;
    }

    lineCount++;
    free(lineNext);
  }

  printf("Stopping...\n");

  free(line);
  return(EXIT_SUCCESS);
}

char* readLine(char* beginMe, int size)
{
  char *bgn, thisCh;
  bgn = beginMe;
  //int endOfLine;
  int length = 0;
  bgn = realloc(NULL, sizeof(char)*size);

  if(!bgn)return bgn;
  while(thisCh != '\n') //EOF != (thisCh = getchar()) ||
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

/*char * readInString(char *lineBeginning)
{
  int len =0;
  char n;
  char *cB = lineBeginning;

  while((n = getchar() != '\n'))// && (n != EOF))
  {
    n = getchar();
    printf("%c\t", n);
    *(cB + (len++)) = n;
    cB = realloc(cB, len + 1);
  }
  *(cB+len) = '\0';

  return cB;
}*/

//Inspiration for this here: https://stackoverflow.com/questions/16870485/how-can-i-read-an-input-string-of-unknown-length

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

/*
void lookForWords(char *startOfLine, struct word *wordList, int size, int lineNum);
void checkForDups(char *inputStart, struct word *words, int numWords, int lineCount);

typedef struct lineNum
{
  int lineN;
  struct lineNum *next;
}lineNum_t;

int main()
{
  char *inputStart;

  //word_t *word = (word*)malloc(n*sizeof());

  printf("Enter lines to parse:\n");
  printf("TEXT   :\t");
  inputStart = readLine(inputStart, 100);

  int number_of_words = 10;
  word_t *words = realloc(NULL, sizeof(word_t)*number_of_words);

  //char p = 'S';
  char *s = realloc(NULL, sizeof(char)*4); //4 chars in STOP
  (*(s+0) = 'S');
  (*(s+1) = 'T');
  (*(s+2) = 'O');
  (*(s+3) = 'P');
  //printf("%s\n", s);

  //int numTimes = findMatch(inputStart, pattStart);

  int lineCount = 1;
  char *n = inputStart;

  while(1)
  {

    //first check for duplicates:
    //checkForDups(inputStart, words, numWords, lineCount);
    //lookForWords(inputStart, words, numWords, lineCount);
    printf("TEXT   :\t");
    n = readLine(n, 50);
    lineCount++;

    if(findMatch(n, s) >= 1)
    {
      free(n);
      break;
    }
    //free(n);
  }

  free(inputStart);
  free(s);
  free(words);

  return(EXIT_SUCCESS);
}

/*checkForDups(char *inputStart, struct word *words, int numWords, int lineCount)
{
  char *a = inputStart;
  struct word *w = words;
  //for each word in list words
  for(int i = 0; i < numWords; i++)
  {
    //The count += how many matches are in this
    *(w+i).count += findMatch(a,w);
    //record the line number
    int *lC = (int*)malloc(1*sizeof(int));
    *lC = lineCount;
    *(w.l.next)=lC);

    //cut out the duplicates
    //while(findMatch(a,w)>1)
    //{
    //  while()
    //  {
    //    *b = ' ';
    //    b++;
    //  }
    //}
    //b = a;

    a++;
    w++;
  }
  free(lC);
}

lookForWords(char *startOfLine, struct word *wordList, int size, int lineNum)
{
  char *a = startOfLine;

  int wordListLength = 0;

  states_t newFSM;
  newFSM.IN_OUT = 0;

  //until the next line
  while(*a != '\n')
  {
    //if what's at a is a space then we've just ended a word.
    if(newFSM.IN_OUT == 0 && *a != ' ')
    {
      newFSM.IN_OUT = 1;
      word_t w;
      w.firstChar = a;
      if(w.count <= 1)
      { w.count = 1; }
      else
      { w.count += 1; }
      //w.l.lineN = lineNum;
    }
    else if(newFSM.IN_OUT == 1 && *a != ' ')
    {
      //newFSM.IN_OUT = 1;
    }
    else //if(*a == ' ')
    {
      newFSM.IN_OUT = 0;
    }

    if(wordListLength == size)
    {
      size+=16;
      wordList = realloc(wordList, sizeof(word_t)*size);
    }

    a++;
  }
}
*/
