#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

    int main()
{
   char ch;

   int i = 0, realloc_Counter = 2, encountered_Stop = 0;

   /* Defining a set array. 0th position is for SETA and 5th position for SETF. */ 

   setptr SETS[TOTAL_SETS];

   /* Using malloc so as to not waste memory when reciving input. */

   char *input = malloc(realloc_Factor);

   if (!input)
   {
      puts("Could not allocate any more memory for input.");

      exit(1);
   }

   /* Allocating memory for set array. */

   for (i = 0; i < TOTAL_SETS; i++)
   {
      SETS[i] = calloc(1,sizeof(set));

      if (!SETS[i])
      {
	 puts("Could not allocate any more memory for the sets.");

	 exit(1);
      }

      reset(&SETS[i]);
   }

   i = 0;

   puts("\nThis program performs operations on 6 sets, SETA through SETF.");
   puts("The available operations are:\n\n1. read_set\n2. print_set\n3. union_set");
   puts("4. sub_set\n5. intersect_set\n6. symdiff_set\n");
   puts("Enter the 'stop' command to end the program.\n");

   while (encountered_Stop != 1)
   {
      puts("Enter a command:");

      /* Assigning to input, one char at a time so as to filter out tabs and spaces.*/

      while((ch = getchar()) != '\n')
      {
         /* If ctrl d has been entered. */

         if (ch == EOF) 
	 {
	    printf("\nError: Program abruptly terminated.\n"); 

	    exit(1);
 	 }

	 if (ch != ' ' && ch != '\t')
	 {
	     input[i] = ch;

	     i++;
	 }
	 
	 /* Every 5 bytes, the program will attempt to enlarge the memory block. */

	 if (i%realloc_Factor == 0)
	 {
	    input = realloc(input, realloc_Counter * realloc_Factor);
	    if (!input)
	    {
	       puts("Could not allocate any more memory for input.");

	       exit(1);
	    }

	    realloc_Counter++;
	 }

      }

      input[i] = '\0';

      printf("\n");

      puts(input);

      /* If else ladder for each available command. The input's validity will be 
	 checked first. If it is valid, the program will proceed to execute the 	 command, otherwise, the program will print an error message and await
	 further instructions untill it encounters the 'stop' command or EOF. */

    if (strncmp(input,"stop",4) == 0)
      {

	 if (strlen(input) == 4)
	 {
	    encountered_Stop++;
	 }
	 else 
	 {
	    puts("Extraneous text after end of command.");
	 }

      }
      else if (strncmp(input,"read_set",8) == 0) 
      {
	 if (examine_Errors_For_Read(input+8, strlen(input+8)) == SUCCESS)
	 {
	    reset(&SETS[input[11] - 65]);

	    /* 8+4 as to skip read_set SETX... part. */
	    read_set(&SETS[input[11] - 65],input+8+4);
	 }

      }
      else if (strncmp(input,"print_set",9) == 0) 
      {
         if (examine_Errors_For_Print(input+9, strlen(input+9)) == SUCCESS)
	 {
	    print_set(SETS[input[12] - 65]);
	 }
      } 
      else if (strncmp(input,"union_set",9) == 0)
      {
         if (examine_Errors_For_Others(input+9, strlen(input+9)) == SUCCESS)
	 {
	   union_set(SETS[input[12] - 65],SETS[input[17] - 65],&SETS[input[22] - 65]);
	 }
      }
      else if (strncmp(input,"sub_set",7) == 0)
      {
	 if (examine_Errors_For_Others(input+7, strlen(input+7)) == SUCCESS)
         {
	    sub_set(SETS[input[10] - 65],SETS[input[15] - 65],&SETS[input[20] - 65]);
	 }
      }
      else if (strncmp(input,"intersect_set",13) == 0)
      {
       if (examine_Errors_For_Others(input+13, strlen(input+13)) == SUCCESS)
       {
       intersect_set(SETS[input[16] - 65],SETS[input[21] - 65],&SETS[input[26] - 65]);
       }
      }
      else if (strncmp(input,"symdiff_set",11) == 0)
      {
	if (examine_Errors_For_Others(input+11, strlen(input+11)) == SUCCESS)
	{
	 symdiff_set(SETS[input[14] - 65],SETS[input[19] - 65],&SETS[input[24] - 65]);
	}
      }
      else 
      {
	 puts("Undefined command name.");
      }

      free(input);

      input = malloc(5);

      if (!input)
      {
	 puts("Could not allocate any more memory for input.");

	 exit(1);
      }

      realloc_Counter = 2;

      i = 0;

  }

   /* Frees the input string and set array. */

   free(input);

   input = NULL;

   for (i = 0; i < TOTAL_SETS; i++)
   {
      free(SETS[i]);

      SETS[i] = NULL;
   }

   return 0;
}
