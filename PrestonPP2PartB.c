//Matthew Preston
//CSCI 2271
//PP2, due 2/20/2018

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>
#include <string.h>

typedef struct word {
  char *w;
  int frequency;
  int *lineNumbers;   /* this is a dynamically allocated list of int representing the line numbers in which the word appears */
  int numberOfLines;  /* this is the number of lines in which the word appears (you need this to realloc space for lineNumbers */
  struct word *next;  /* points to next word in the linked list */
} word_t;

signed int IsWordEqualToStop(char *s);
void AddWordToLinkedList(word_t *head, char *wordStr, int lineNumber);
void printResults(word_t *head);
void printMostFrequentWord(word_t *head);

int main()
{
  char ch;
  int lineNumber = 1;
  signed int boolStopNotFound = 1;

  char *wordUnderConstruction;
  char *wordStr;

  word_t *head = NULL;    /* pointer to head of linked list of words */

  printf("Enter sentences with words, followed by carriage return.\r\n");
  printf("Type STOP to stop.\r\n");
  printf("%d: ", lineNumber);

  while (boolStopNotFound)
  {
    /* Parse current word */
    wordUnderConstruction = (char *) malloc(50);    /* limit words to 50 characters */
    wordStr = wordUnderConstruction;

    while ((ch = _getch()) != ' ')
    {
      //if (ch == '\b')
      //{
      //  _putch(ch); /* echo backspace */
      //}
      //if (ch == '\r')
      //{
        //printf("\r\n%d: ", ++lineNumber); /* echo carriage return (& new line number) to screen */
      //  break; /* break out of inner while loop above (for carriage return as well as space) */
      //}
      /*else*/ if (((ch >= 'a') && (ch <= 'z')) || ((ch >= 'A') && (ch <= 'Z')))  /* ignore punctuation */
      {
        //_putch(ch); /* echo character to screen */
        *wordUnderConstruction++ = ch;
      }
    }   /* while _getch() */

    /* We got a space character: terminate word string (and print out the space character) */
    //if (ch != '\r')
      //_putch(ch); /* echo spacebar */
    *wordUnderConstruction = '\0';  /* finish word under construction */
    //printf("Debug: word:: >%s<", wordStr);

    /* Check if current word == STOP */
    /* If so, we're done */
    if (IsWordEqualToStop(wordStr))
    {
      boolStopNotFound = 0;
    }
    else
    {
      /* If it's not the word STOP, add the current word to the linked list */
      if (head == NULL)
      {
        /* no words in linked list yet -- this is the first one to be added */
        head = (word_t *)malloc(sizeof(word_t));  /* allocate memory for a new node */
        head->w = NULL;
      }

      AddWordToLinkedList(head, wordStr, lineNumber);
      free(wordStr);  /* free memory */
    }

    /* Final clean up at end of line */
    if (ch == '\r')
    {
      printf("\r\n%d: ", ++lineNumber); /* echo carriage return (& new line number) to screen */
    }
  }   /* while boolDontStop */

  /* PRINT RESULTS */
  printResults(head);
  printf("\r\n\r\n");
  printMostFrequentWord(head);

  return 0;
}

/* */
signed int IsWordEqualToStop(char *s)
{
  return ((*s == 'S' || *s == 's') &&
  (*(s+1) == 'T' || *(s+1) == 't') &&
  (*(s+2) == 'O' || *(s+2) == 'o') &&
  (*(s+3) == 'P' || *(s+3) == 'p'));
}

/* */
void AddWordToLinkedList(word_t *head, char *wordStr, int currentLineNumber)
{
  int i;
  int ret;    /* used to compare 2 strings */
  char *wordCopy;
  int strLength;

  word_t *current = head; /* point to first node */
  word_t *previous;   /* keep track of last node, when we add new node */

  if (current->w == NULL)
  {
    /* No words are in the linked list yet -- this is the FIRST one to be added */
    current->w = (char *)malloc(sizeof(wordStr));  /* allocate memory for a new word within the node */
    wordCopy = current->w;
    strLength = strlen(wordStr);

    /* copy the word */
    for (i = 1; i <= strLength; i++)
    {
      *wordCopy++ = *wordStr++;
    }

    *wordCopy = '\0';    /* terminate string */

    //for the first word:
    current->frequency = 1;
    current->lineNumbers = (int *)malloc(sizeof(int));
    *current->lineNumbers = currentLineNumber;
    current->numberOfLines = 1;
    current->next = NULL;
  }
  else
  {
    while (current != NULL) /* traverse nodes in linked list */
    {
      /* Check if current linked list node has word that matches current word that we're parsing from the screen */
      ret = strcmp(current->w, wordStr);  /* 'strcmp' is built-in C string compare function; returns 0 if strings match (case sensitive) */
      if (ret == 0)
      {
        //printf("\r\n: found match (%s %s)", current->w, wordStr);
        /* strings match: REPEATED WORD */
        current->frequency++;
        //printf("\r\n: freq: %d", current->frequency);

        /* >>>>>>>>>> EXTRA CREDIT <<<<<<<<< */
        /* >>>>>>>>>> EXTRA CREDIT <<<<<<<<< */
        /* UPDATE LINE NUMBER INFO -- HARDEST PART OF CODE */
        /* GET THE CURRENT NUMBER OF LINES THIS REPEATED WORD IS ON */
        int numberOfLinesThisWordIsAlreadyOn = current->numberOfLines;
        //printf("\r\n: numberOfLinesThisWordIsAlreadyOn: %d", numberOfLinesThisWordIsAlreadyOn);
        /* IS THIS WORD BEING REPEATED ON A LINE NUMBER THAT IT'S ALREADY APPEARED ON? (AND THEREFORE ALREADY ON THIS LIST?) */
        int j;
        unsigned int boolMatchFound = 0;
        for (j = 1; j <= numberOfLinesThisWordIsAlreadyOn; j++)
        {
          if (currentLineNumber == *current->lineNumbers)
          {
            boolMatchFound = 1;
            break;
          }
        }

        //printf("\r\b: boolMatchFound %u", boolMatchFound);
        if (!boolMatchFound)
        {
          /* THIS WORD APPEARS ON A NEW LINE NUMBER IT HASN'T ALREADY APPEARED ON... */
          current->lineNumbers = (int *)realloc(current->lineNumbers, current->numberOfLines + 1);   /* MAKE ROOM FOR NEW LINE NUMBER AT END OF LINE NUMBER LIST */
          //printf("\r\n: line # ptr: 0x%x", (unsigned int)current->lineNumbers);
          current->numberOfLines++;
          //printf("\r\n: # of lines: %d", current->numberOfLines);

          /* NAVIGATE TO END OF LIST TO ADD NEW LINE NUMBER */
          int *p = current->lineNumbers;
          //printf("\r\np: 0x%x", (unsigned int)p);
          int k;
          for (k = 1; k < current->numberOfLines; k++)
          {
            p++;
            //printf("\r\nk: %d   p: 0x%x", k, (unsigned int)p);
          }

          //printf("\r\np: 0x%x", (unsigned int)p);
          *p = currentLineNumber; /* FINALLY, ADD THE NEW LINE NUMBER TO THE NEW END OF THE LINE NUMBER LIST */
          //printf("\r\n *p=%d", *p);
        }

        /* >>>>>>>>>> EXTRA CREDIT <<<<<<<<< */
        /* >>>>>>>>>> EXTRA CREDIT <<<<<<<<< */
        return;     /* <-------- we're done; get out of this function */
      }

      /* strings don't match: try next node */
      previous = current;
      current = current->next;
    }
    /* if we get here, we didn't find a match -- so add new node at the end of the linked list for the new word */
    current = (word_t *)malloc(sizeof(word_t));
    previous->next = current;  /* link previous last node to new node */

    current->w = (char *)malloc(sizeof(wordStr));  /* allocate memory for a new word within the node */
    wordCopy = current->w;
    strLength = strlen(wordStr);

    /* copy the word */
    for (i = 1; i <= strLength; i++)
    {
      *wordCopy++ = *wordStr++;
    }

    *wordCopy = '\0';    /* terminate string */

    current->frequency = 1;
    current->lineNumbers = (int *)malloc(sizeof(int));
    *current->lineNumbers = currentLineNumber;
    current->numberOfLines = 1;
    current->next = NULL;
  }
}

/* */
void printResults(word_t *head)
{
  word_t *current = head; /* point to first node */

  while (current != NULL) /* traverse nodes in linked list */
  {
    printf("\r\n%s:%d, number of lines:%d  ", current->w, current->frequency, current->numberOfLines);

    /* >>>>>>>>>>> EXTRA CREDIT <<<<<<<<<< */
    /* >>>>>>>>>>> EXTRA CREDIT <<<<<<<<<< */
    /* Print list of line numbers this word appeared on */
    int i;
    printf("Line Numbers: ");
    int *p = current->lineNumbers;
    for (i = 1; i <= current->numberOfLines; i++)
    {
      printf ("%d ", *p++);
    }
    printf ("\r\n");
    /* >>>>>>>>>>> EXTRA CREDIT <<<<<<<<<< */
    /* >>>>>>>>>>> EXTRA CREDIT <<<<<<<<<< */

    current = current->next;
  }
}

/* */
void printMostFrequentWord(word_t *head)
{
  int currentWordCount = 0;
  int currentLargestWordCount = 0;

  /* First, find largest word count */
  word_t *current = head; /* point to first node */
  while (current != NULL) /* traverse nodes in linked list */
  {
    currentWordCount = current->frequency;
    if (currentLargestWordCount < currentWordCount)
      currentLargestWordCount = currentWordCount;
    current = current->next;
  }

  /* Next, print all words with this largest word count */
  printf("\r\n");
  current = head; /* point to first node */
  while (current != NULL) /* traverse nodes in linked list */
  {
    if (current->frequency == currentLargestWordCount)
      printf("\r\n%s:%d", current->w, current->frequency);
    current = current->next;
  }
    printf("\r\n");
}
