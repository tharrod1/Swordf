#include "error.h"
#include <stdio.h>

void msg(char *imsg, char *date, char *time,
	 char *file, unsigned int line){
  printf("On %s, %s:\n- in %s on line %i:\n-  %s\n",
	  date, time, file, line, imsg);
}
