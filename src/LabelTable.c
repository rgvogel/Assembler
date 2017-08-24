/*
 * Label Table: functions to access and manipulate a label table
 *
 * This file provides the definitions of a set of functions for
 * creating, maintaining, and using a table of assembly language
 * instruction labels and the memory addresses associated with them.
 *
 * Author: Alyce Brady
 *
 * 	 Creation Date:   2/16/99
 *   Modified:  12/20/2000   Updated postcondition information.
 *   Modified:  4/19/2013    Modernized call to fprintf for errors.
 *   Modified:  5/25/2015    Updated to use printError function.
 *   Modified:	4/29/1994 	Updated addlabel, and find label (roderick Vogel

*/

#include "assembler.h"

// internal global variables (global to this file only)
static const char * ERROR0 = "Error: no label table exists.\n";
static const char * ERROR1 = "Error: a duplicate label was found.\n";
static const char * ERROR2 = "Error: cannot allocate space in memory.\n";

// internal function (visible to this file only)
static int verifyTableExists(LabelTable * table);

void tableInit (LabelTable * table)
  /* Postcondition: table is initialized to indicate that there
   *       are no label entries in it.
   */
{
        /* verify that current table exists */
        if ( ! verifyTableExists (table) )
        {
        	printError("%s", ERROR0);
            return;           /* fatal error: table doesn't exist */
        }
        table->capacity=0;
        LabelEntry*entries;
        entries = malloc(sizeof(LabelEntry));
        table->entries = entries;
        table->nbrLabels =0;
}

void printLabels (LabelTable * table)
  /* Postcondition: all the labels in the table, with their
   *      associated addresses, have been printed to the standard
   *      output.
   */
{

        if ( table == NULL )
            (void) printf ("Label Table is a NULL pointer.\n");
        else
        {

            (void) printf ("There are %d labels in the table:\n",
                                    table->nbrLabels);

            for ( int i = 0; i<table->nbrLabels; i++)
            {
            	printf("table name: %s                     Address: %d\n", table->entries[i].label,table->entries[i].address);
            }
        }
}

int findLabel (LabelTable * table, char * label)
  /* Returns the address associated with the label; -1 if label is
   *      not in the table or table doesn't exist
   */
{
	if ( ! verifyTableExists (table))
			{
				return -1;
			}
	else
	{

        for (int i=0; i<table->nbrLabels; i++)
        {
        	if(strcmp(table->entries[i].label,label)== SAME)
        	{
        		return table->entries[i].address;
        	}
        }
       return -1;
	}
}

int addLabel (LabelTable * table, char * label, int PC)
  /* Postcondition: if label was already in table, the table is
   *      unchanged; otherwise a new entry has been added to the
   *      table with the specified label name and instruction address
   *      (memory location) and the table has been resized if necessary.
   * Returns 1 if no fatal errors occurred; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
        char * labelDuplicate;


        /* verify that current table exists */
        if ( ! verifyTableExists (table) )
            return 0;           /* fatal error: table doesn't exist */
        /* Create a dynamically allocated version of label that will persist. */
        /*   NOTE: on some machines you may need to make this _strdup !  */
        if ((labelDuplicate = strdup (label)) == NULL)
        {
            printError ("%s", ERROR1);
            return 0;           /* fatal error: couldn't allocate memory */
        }

        /* Was the label already in the table? */
        if ( findLabel(table, label) != -1 )  /* REAL CODE MISSING ! */
        {
            /* This is an error (ERROR1), but not a fatal one.
             * Report error; don't add the label to the table again.
             */
            printError("%s", ERROR2);
            free(labelDuplicate);
            return 1;
        }


        /* Resize the table if necessary. */
        if ( table->nbrLabels >= table->capacity )
        {
           tableResize(table, 2*(table->nbrLabels+1));
        }

        	table->entries[table->nbrLabels].label = label;
        	table->entries[table->nbrLabels].address = PC;
        	table->nbrLabels++;

        return 1;               /* everything worked great! */
}

int tableResize (LabelTable * table, int newSize)
  /* Postcondition: table now has the capacity to hold newSize
   *      label entries.  If the new size is smaller than the
   *      old size, the table is truncated after the first
   *      newSize entries.
   * Returns 1 if everything went OK; 0 if memory allocation error
   *      or table doesn't exist.
   */
{
        char * ptr;               /* points to any byte in memory */
        LabelEntry * newEntryList;
        int          smaller;

        /* verify that current table exists */
        if ( ! verifyTableExists (table) )
            return 0;           /* fatal error: table doesn't exist */

        /* create a new internal table of the specified size */
        if ((newEntryList = malloc (newSize * sizeof(LabelEntry))) == NULL)
        {
            printError ("%s", ERROR2);
            return 0;           /* fatal error: couldn't allocate memory */
        }

        if ( table->entries )           /* if there were entries */
        {
            /* move contents of internal table to new internal table */
            smaller = table->nbrLabels < newSize ? table->nbrLabels : newSize;
            (void) memcpy (newEntryList, table->entries,
                           smaller * sizeof(LabelEntry));

            /* free the space taken up by the old internal table */
            free (table->entries);
            table->nbrLabels = smaller;
        }

        table->entries = newEntryList;
        table->capacity = newSize;
        return 1;
}

static int verifyTableExists(LabelTable * table)
 /* Returns true (1) if table exists; prints an error and returns
  * false (0) otherwise.
  */
{
        /* verify that current table exists */
        if ( ! table )
        {
            printError ("%s", ERROR0);
            return 0;
        }

        return 1;
}
