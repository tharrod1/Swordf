#pragma once
#include <stdio.h>
#define ERRSTAMP __DATE__, __TIME__, __FILE__, __LINE__

//meant for errors, but will be used for general purposes as well
void msg(char *msg, char *date, char *time,
	 char *file, unsigned int line){
  printf("On %s, %s:\n- in %s on line %i:\n-  %s\n",
	  date, time, file, line, msg);
}
