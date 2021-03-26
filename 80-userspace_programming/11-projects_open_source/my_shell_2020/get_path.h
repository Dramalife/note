/* 
  get_path.h
  Ben Miller

*/
#ifndef _GET_PATH_H_
#define _GET_PATH_H_
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

struct pathelement
{
  char *element;			/* a dir in the path */
  struct pathelement *next;		/* pointer to next node */
};

/* function prototype. 
   It returns a pointer to a linked list for the path elements. */
struct pathelement *get_path();

#endif
