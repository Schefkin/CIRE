#include "standard_input_output.h"
#include <stdio.h>
#include <string.h>

// return the amount by which I have to move
int is_standard_input_output(char *s, int i, FILE *fptr) {
  // check if Say
  // char ss_say[4];
  // strncpy(ss_say, s + i, 3);
  // ss_say[3] = '\0';
  //
  // if (strcmp("Say", ss_say) == 0) {
  //   return write_say(fptr, s, i);
  // }
	
	if (memcmp("Say", s + i, 3) == 0) {
		return write_say(fptr);
	}

  return 0;
}

int write_say(FILE *fptr) {
  // write to the c file
  printf("write Say");

  fprintf(fptr, "printf(\"Hello World\");\n");
  // return the amount of chars eaten
  return 20;
}
