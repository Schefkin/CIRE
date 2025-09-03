#include "compiler.h"
#include "standard_input_output.h"
#include <stdio.h>

void compile(char *program) {
  int c = 0;
  // temporary
  FILE *fptr;
  // Open a file in writing mode
  fptr = fopen("somename.c", "w");

  // Write some text to the file
  fprintf(fptr, "#include <stdio.h>\nint main() {\n");

  // while end of program is not reached continue
  while (program[c] != '\0') {
    // check if it's in the stdio
    c += is_standard_input_output(program, c, fptr);

    // check if it's a keyword

    // printf("%c", program[c]);
    c++;
  }

  // temporary
  fprintf(fptr, "return 0;\n}");
  // Close the file
  fclose(fptr);
}
