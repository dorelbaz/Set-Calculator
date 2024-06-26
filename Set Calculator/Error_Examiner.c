#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

/* Note: The following functions recieve the part of input that comes after the
   command has been verfied by the strncmp functions in main. */

/* Examine errors for read_set only. */

    int examine_Errors_For_Read(char *in, int len)
{
   int i = 0;

   char *temp;

   long num;

   /* The following 4 if statements check for potential errors before the numerical
      part of the input. */

   if (len <= 5) 
   {
      puts("Missing parameter(s)."); 

      return FAIL;
   }

   if (in[0] == ',' || in[1] == ',' || in[2] == ',' || in[3] == ',')
   {
      puts("Illegal comma.");

      return FAIL;
   }

   if(in[0] != 'S' || in[1] != 'E' || in[2] != 'T' || !('A' <= in[3] && in[3] <= 'F'))
   {
      puts("Undefined set name.");

      return FAIL;
   }
	
   if (in[4] != ',')
   {
      puts("Missing comma.");

      return FAIL;
   }

   /* Checks for double commas. */

   for (i = 0; i < len-1; i++)
   {
      if (in[i] == ',' && in[i+1] == ',')
      {
	 puts("Multiple consecutive commas.");

	 return FAIL;
      }
   }

   /* The loop checks for the validity of the numerical part of the input. */

   num = strtol(in+5, &temp, 10);

   while (*temp != '\0')
   {
      /* Checks to see if the number is within the given range. */

      if (!(-1 <= num && num <= 127))
      {
	 puts("Invalid set member - value out of range.");

	 return FAIL;
      }

      /* If after detecting -1, temp doesn't point at null it means that the input
         continues after termination. */

      if (*temp != '\0' && num == -1)
      {
	 puts("Extraneous input after termination.");

	 return FAIL;
      }

      /* If the number is valid, the temp pointer from strtol needs to point at either
	 a comma or null else we are dealing with a non integer. */

      if (*temp != ',' && *temp != '\0')
      {
	 puts("Invalid set member - not an integer.");

	 return FAIL;
      }

      num = strtol(temp+1, &temp, 10);
   }

   if (num != -1)
   {
      puts("List of set members is not terminated correctly.");

      return FAIL;
   }

   return SUCCESS;
}

/* Examine errors for print_set only. */

    int examine_Errors_For_Print(char *in, int len)
{
   /* Since we know that when it comes to print, the input needs to follow this 
      syntax: SETX and these if statements check just that. */

   if (len == 0)
   {
      puts("Missing parameter.");

      return FAIL;
   }

   if (in[0] == ',' || in[1] == ',' || in[2] == ',' || in[3] == ',')
   {
      puts("Illegal comma.");

      return FAIL;
   }

   if (len > MIN_COMMAND_LEN )
   {
      puts("Extraneous text after end of command.");

      return FAIL;
   }

   if(in[0] != 'S' && in[1] != 'E' && in[2] != 'T' && !('A' <= in[3] && in[3] <= 'F'))
   {
      puts("Undefined set name.");

      return FAIL;
   }

   return SUCCESS;

}

/* Examine errors for union/sub/intersects/symdiff_set. */

    int examine_Errors_For_Others(char *in, int len)
{
   int i = 0, commas = 0, set_counter = 0;

   /* This loop counts how much commas and sets the input contains and checks for
      potential errors. */

   for (i = 0; i < len; i++)
   {
      if (in[i] == ',' && in[i+1] == ',') 
      {
	 puts("Multiple consecutive commas.");

	 return FAIL;
      }

      /* If the length is longer than 14 because of an additional illegal comma,
         this if statement will detect this. */ 

      if (i == MAX_COMMAND_LEN && commas > 2) 
      {
         puts("Illegal comma.");

         return FAIL;
      }

      if (in[i] == ',')
      {
	 commas++;
      }

      if(!('A' <= in[i] && in[i] <= 'F') && in[i] != 'S' && in[i] != 'T')
      {
	 if (in[i] != ',')
	 {
	    puts("Undefined set name.");

	    return FAIL;
	 }
      }

      if (strncmp(in+i, "SET", 3) == 0)
      {
	 if (i+3 <= len && ('A' <= in[i+3] && in[i+3] <= 'F'))
	 {
	    set_counter++;
	 }
      }

   }

   /* Now that an illegal comma is negated, if the length of the input is longer than
      14 it means the following error. */

   if (len > MAX_COMMAND_LEN)
   {
      puts("Extraneous text after end of command.");

      return FAIL;
   }

   if (set_counter != 3)
   {
      puts("Missing parameter(s).");

      return FAIL;
   }

   if (commas < 2) 
   {
      puts("Missing comma(s)."); 

      return FAIL;
   }

   return SUCCESS;
}
