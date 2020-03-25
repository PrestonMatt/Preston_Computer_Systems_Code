//Matthew Preston
//CSCI 2271
//PP0, due 1/29/2018

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

//reads in a line of characters and spits out the line reversed

int main()
{
  char inputStr[80];
  int i,size = 0;
  printf("Please enter an input line of length less than 80 characters. \n");
  printf("Input : \t");
  size = getLine(inputStr);
  if(size>=81)
  {
    printf("You ignored this instructions and inputed a line too long. \n");
    printf("Terminating program. \n");
    return(EXIT_FAILURE);
  }
  reverseMe(inputStr,size);
  printf("Output: \t");
  printLine(inputStr,size);
  printf("All done! \n");
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

void reverseMe(char *line, int size)
{
  char *firstChar, *lastChar;
  char tempChar;
  firstChar = line;
  lastChar = line;

  //actually point to end of array:
  for(int j = 0; j < size - 1; j++){ lastChar++; }

  //make a copy
  /*char *a;
  a = line;
  char copy[size];
  char *b;
  b = copy;
  for(int k = 1; k <= size; k++)
  {
    *b++ = *a++;
  }*/

  for(int i = 0; i < size/2; i++)
  {
      tempChar = *lastChar;
      *lastChar = *firstChar;
      *firstChar = tempChar;

      lastChar--;
      firstChar++;
  }
}
