#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "main.h"


void failure(char *format, ...)
{
   va_list va;
   
   fprintf (stderr, "ERROR: ");
   va_start (va, format);
   vfprintf (stderr, format, va);
   va_end (va);
   fprintf (stderr, "\n(errno is %d)\n", errno);
   
   exit (-1);
}


void debug_printf(char *format, ...)
{
   va_list va;
   
   if (!debug_mode)
      return;
      
   fprintf (stderr, "DEBUG: ");
   va_start (va, format);
   vfprintf (stderr, format, va);
   va_end (va);
   fflush (stdout);
   
   return;
}


void *xmalloc(unsigned int size)
{
   void *ptr = NULL;
   
   if ( (ptr = (void *)malloc(size)) == NULL)
   {
      fprintf (stderr, "WARNING: Out of memory, buy more RAM!\n");
      return (NULL);
   }

   return (ptr);
}


char *xstrdup(char *string)
{
   char *ptr = NULL;
   
   if ( (ptr = (char *)malloc(strlen(string)+1)) == NULL)
   {
      fprintf (stderr, "WARNING: Out of memory, buy more RAM!\n");
      return (NULL);
   }
   
   strcpy ((char *)ptr, string); /* secure */

   return (ptr);
}
