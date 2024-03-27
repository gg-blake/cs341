

/******************************************************************
*
*   file:     cmds.c
*   author:   betty o'neil
*   date:     ?
*
*   semantic actions for commands called by tutor (cs341, mp1)
*
*   revisions:
*      9/90  eb   cleanup, convert function declarations to ansi
*      9/91  eb   changes so that this can be used for hw1
*      9/02  re   minor changes to quit command
*/
/* the Makefile arranges that #include <..> searches in the right
   places for these headers-- 200920*/

#include <stdio.h>
#include "slex.h"
/*===================================================================*
*
*   Command table for tutor program -- an array of structures of type
*   cmd -- for each command provide the token, the function to call when
*   that token is found, and the help message.
*
*   slex.h contains the typdef for struct cmd, and declares the
*   cmds array as extern to all the other parts of the program.
*   Code in slex.c parses user input command line and calls the
*   requested semantic action, passing a pointer to the cmd struct
*   and any arguments the user may have entered.
*
*===================================================================*/

PROTOTYPE int stop(Cmd *cp, char *arguments);
PROTOTYPE int mem_display(Cmd *cp, char *arguments);
PROTOTYPE int mem_set(Cmd *cp, char *arguments);
PROTOTYPE int help(Cmd *cp, char *arguments);

/* command table */

Cmd cmds[] = {{"md",  mem_display, "Memory display: MD <addr>"},
              {"s",   stop,        "Stop" },
              {"ms",  mem_set, "Memory set: MS <addr> <value>"},
              {"h",   help,        "Help: H <command>"},
              {NULL,  NULL,        NULL}};  /* null cmd to flag end of table */

char xyz = 6;  /* test global variable  */
char *pxyz = &xyz;  /* test pointer to xyz */
/*===================================================================*
*		command			routines
*
*   Each command routine is called with 2 args, the remaining
*   part of the line to parse and a pointer to the struct cmd for this
*   command. Each returns 0 for continue or 1 for all-done.
*
*===================================================================*/

int stop(Cmd *cp, char *arguments)
{
  return 1;			/* all done flag */
}

/*===================================================================*
*
*   mem_display: display contents of 16 bytes in hex
*
*/


int mem_display(Cmd *cp, char *arguments) {
  unsigned int addr; // Initialize address input
  int result = sscanf(arguments, "%x", &addr); 
  
  // Return if user input is invalid
  if (result != 1) {
    printf("Invalid Address!");
    return 0;
  }
  
  printf("%08x ", addr); // Print the input hex address with zeroes as padding
  for (int i = 0; i < 16; i++) {
    // Print each byte, incrementing by one
    printf("%02x ", *((unsigned char*)(addr + i)));
  }
  
  printf(" ");
  
  /* Convert the 16 bytes into ascii characters and omit the out of range hex values
     as '.' */
  for (int i = 0; i < 16; i++) {
    unsigned char value = *((unsigned char*)(addr + i));

    printf("%c", (value >= 32 && value < 127) ? value : '.');
  }
  

  printf("\n");
  return 0;
}

int mem_set(Cmd *cp, char *arguments)
{
  // Initialize variables for user input
  unsigned int addr;
  unsigned int val;
  // Scan user input
  int result = sscanf(arguments, "%x %x", &addr, &val);  
  // Return if user input is invalid
  if (result != 2) {
    printf("Invalid Arguments!");
    return 0;
  }
  
  // Set the value at the inputted address to the address provided by user
  *((unsigned char*)(addr)) = (unsigned char)val;

  return 0;
}



int help(Cmd *cp, char *arguments) {
  char string[MAXTOKENLEN]; // Adjusted size to MAXTOKENLEN
  int num = 0;
  int length = sizeof(cmds) / sizeof(Cmd);

  // If the arguments are blank, print all commands and descriptions
  if (sscanf(arguments, "%s", string) != 1)
  {
    for (num = 0; num < length - 1; num++)
    {
      printf(" %s   %s\n", cmds[num].cmdtoken, cmds[num].help);
    }
    return 0;
  }

  // Print specific command and it's corresponding description
  for (num = 0; num < length - 1; num++)
  {
    if ((strcmp(cmds[num].cmdtoken, string)) == 0)
    {
      printf(" %s   %s\n", cmds[num].cmdtoken, cmds[num].help);
      return 0; // Return success
    }
  }

  // If the loop completes without finding a matching command
  printf("Command not found: %s\n", string);
  return -1; // Return an error code to indicate the issue
}
