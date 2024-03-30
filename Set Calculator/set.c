#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"

/* Note: These following functions recieve valid input. */

/* Assigns the input into set. */

   void read_set(setptr *s, char *nums)
{
   int i = 0;

   char *temp; 

   long num = strtol(nums+1, &temp, 10);

   /* This loop is responsible for assigning the input. */

   while (num != -1)
   {  
      /* The set struct is composed of an array of 4 ints, totaling 128 bits.
	 Each bit represents a number within the given range. This line selects 
	 which of the 4 ints contains the bit that needs to be turned on. */

      i = num / 32;

      /* This line turns on the aforementioned bit. The result of the right part 
	 will be between 0 and 31. */

      (*s)->group[i] |= ( 1 << (31 - (num - 32 * i)) );

      /* Takes the next number from the input, +1 to skip the comma. */

      num = strtol(temp+1, &temp, 10);
   }

   return;
}

/* Prints the given set. */

   void print_set(setptr s)
{
   int i, j, count_bits = 0, empty_Set_Indicator = 0, values_In_Line = 0;

   printf("\n");

   /* This loop goes bit by bit, detects a turned on bit and prints the number the
      bit represents via count_bits. If the function does not detect a turned on bit, 
      empty_Set_Indicator will remain 0 thus printing that the set is empty. */

   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 32; j++)
      {
	 if ((1 << (31-j)) & s->group[i])
	 {
	    values_In_Line++;
	    printf("%d ", count_bits);
	    if (values_In_Line == 16)
	    {
	       values_In_Line = 0;
	       printf("\n");
	    }
	    empty_Set_Indicator++;
	 }
	   
	 count_bits++;
      }

   }

   if (empty_Set_Indicator == 0)
   {
      puts("This set is empty. ");
   }

   printf("\n");

   return;
}

/* Unites 2 sets and stores the result in the third set. */

/* Note: The following 4 functions work similarly. */

   void union_set(setptr s1, setptr s2, setptr *s3)
{
   /* There is a possibility that s3 and s2 or s1 are the same, we'll need a temp set
      to temporarily store the result because we call s3 by reference and later reset
      it so we can store the result.  */
   int i = 0, j = 0;

   setptr temp = calloc(1,sizeof(set));

   if (!temp)
   {
      puts("Could not allocate any more memory for temp set.");

      exit(1);
   }

   /* Detects 1's in either sets and store them in temp. */
	
   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 32; j++)
      {
	 if ((1 << (31-j)) & s1->group[i])
	 {
	    temp->group[i] |= ( 1 << (31 - j) );
	 }
	 if ((1 << (31-j)) & s2->group[i])
	 {
	    temp->group[i] |= ( 1 << (31 - j) );
	 }
      }
   }

   reset(s3);

   /* Copying temp to s3 after reseting s3. */

   for (i = 0; i < 4; i++)
   {
      (*s3)->group[i] = temp->group[i];
   }

   /* Freeing temp. */ 

   free(temp);

   temp = NULL;

   return;
}

/* Subs 2 sets and stores the result in the third set. */

   void sub_set(setptr s1, setptr s2, setptr *s3)
{
   int i = 0, j = 0;

   setptr temp = calloc(1,sizeof(set));

   if (!temp)
   {
      puts("Could not allocate any more memory for temp set.");

      exit(1);
   }

   /* Detects 1's in s1 and corresponding 0's in s2 and stores the 1's of s1 in
      temp. */	
	
   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 32; j++)
      {
	 if(((1 << (31-j)) & s1->group[i]) > 0 && ((1 << (31-j)) & s2->group[i]) == 0)
	 {
	    temp->group[i] |= ( 1 << (31 - j) );
	 }
      }
   }

   reset(s3);

   for (i = 0; i < 4; i++)
   {
      (*s3)->group[i] = temp->group[i];
   }

   free(temp);

   temp = NULL;

   return;
}

/* Intersects 2 sets and stores the result in the third set. */

   void intersect_set(setptr s1, setptr s2, setptr *s3)
{
   int i = 0, j = 0;

   setptr temp = calloc(1,sizeof(set));

   if (!temp)
   {
      puts("Could not allocate any more memory for temp set.");

      exit(1);
   }	

   /* Detects common 1's in both sets and turns the bit on in temp. */
	
   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 32; j++)
      {
	 if (((1 << (31-j)) & s1->group[i]) > 0 && ((1 << (31-j)) & s2->group[i]) > 0)
	 {
	    temp->group[i] |= ( 1 << (31 - j) );
	 }
      }
   }

   reset(s3);

   for (i = 0; i < 4; i++)
   {
      (*s3)->group[i] = temp->group[i];
   }

   free(temp);

   temp = NULL;

   return;
}

/* Symdiff's 2 sets and stores the result in the third set. */

   void symdiff_set(setptr s1, setptr s2, setptr *s3)
{
   int i = 0, j = 0;	

   setptr temp = calloc(1,sizeof(set));

   if (!temp)
   {
      puts("Could not allocate any more memory for temp set.");

      exit(1);
   }
	
   /* Detects 1's in s1 and corresponding 0's in s2 and vice versa then stores the
      result in temp. */

   for (i = 0; i < 4; i++)
   {
      for (j = 0; j < 32; j++)
      {
	 if(((1 << (31-j)) & s1->group[i]) > 0 && ((1 << (31-j)) & s2->group[i]) == 0)
	 {
	    temp->group[i] |= ( 1 << (31 - j) );
	 }
	 if(((1 << (31-j)) & s1->group[i]) == 0 && ((1 << (31-j)) & s2->group[i]) > 0)
	 {
	    temp->group[i] |= ( 1 << (31 - j) );
	 }
      }
   }

   reset(s3);

   for (i = 0; i < 4; i++)
   {
      (*s3)->group[i] = temp->group[i];
   }

   free(temp);

   temp = NULL;

   return;
}

/* Resets the given set's bits to 0. */

   void reset(setptr *s)
{
   int i;

   for (i = 0; i < 4; i++)
   {
      (*s)->group[i] = 0;
   }

   return;
}
