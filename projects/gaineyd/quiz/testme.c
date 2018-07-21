#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

// strMaxSize based on a natural limit for string size in base 2 system.
int strMaxSize = 255;

char inputChar()
{
  // Max and min ascii based on readable ascii character codes.
  int maxAscii = 128;
  int minAscii = 32;
  int theNum = (rand() % (maxAscii - minAscii)) + minAscii;
  char c;
  if(theNum < 127)
    c = (char) theNum;
  else
    c = '\0';
    
  return c;
}

char *inputString(char* theStr)
{
  // Global variables for theStr and strMaxSize are used to dodge issue of passing address of local variable without altering testme function.
  int i;
  int strLen = rand() % strMaxSize;
    
  memset(theStr,'\0',strMaxSize);
  int minLower = 97;
  int maxLower = 123;
  for(i = 0; i < strLen - 1; i++){
    theStr[i] = (rand() % (maxLower - minLower)) + minLower;
  }
    
    int shortTimer = rand() % 10;
    int charSelector;
    if(shortTimer == 0) {
        memset(theStr,'\0',strMaxSize);
	strLen = rand() % 64;
	for(i = 0; i < strLen; i++){
	  charSelector = rand() % 4;
	  if (charSelector == 0)
	    theStr[i] = 'r';
	  else if (charSelector == 1)
            theStr[i] = 'e';
	  else if (charSelector == 2)
            theStr[i] = 's';
	  else if (charSelector == 3)
            theStr[i] = 't';

	}
    }								
    
    return theStr;
  }

  void testme()
  {
    char theStr[strMaxSize];
    
    int tcCount = 0;
    char *s;
    char c;
    int state = 0;
    while (1)
      {
	tcCount++;
	c = inputChar();
	s = inputString(theStr);
	printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

	if (c == '[' && state == 0) state = 1;
	if (c == '(' && state == 1) state = 2;
	if (c == '{' && state == 2) state = 3;
	if (c == ' '&& state == 3) state = 4;
	if (c == 'a' && state == 4) state = 5;
	if (c == 'x' && state == 5) state = 6;
	if (c == '}' && state == 6) state = 7;
	if (c == ')' && state == 7) state = 8;
	if (c == ']' && state == 8) state = 9;
	if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
	    && state == 9)
	  {
	    printf("error ");
	    exit(200);
	  }
      }
  }

  void thetest() {
      testme();
  }

    int main(int argc, char *argv[])
    {
      srand(time(NULL));
      thetest();
    
      return 0;
    }
