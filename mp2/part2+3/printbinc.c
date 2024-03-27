/* printbinc.c: driver for printbin.s 
   bob wilson 01/20/2012 
   modified by Ron Cheung 3/8/2015   */

#include <stdio.h>
extern char *_printbin(unsigned char);

int main(void)
{
  unsigned int x;

  printf("enter the character's ascii value in hex: \n");
  scanf("%x",&x);
  printf("The binary format for character %c is %s\n", 
                                 x,   _printbin((unsigned char)x));
  return 0;
}

