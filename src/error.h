#pragma once
#define ERRSTAMP __DATE__, __TIME__, __FILE__, __LINE__

//meant for errors, but will be used for general purposes as well
void msg(char *imsg, char *date, char *time,
	 char *file, unsigned int line);
