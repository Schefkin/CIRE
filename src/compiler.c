#include "compiler.h"
#include "standard_input_output.h"
#include <stdio.h>
#include <stdlib.h>

// main logic here
// this function parses .cire file and generates the .c extention exuivalent
void ciretoc(char *program, char *filename) {
  int c = 0;
  int line_number = 1;
  // temporary
  FILE *fptr;

  int chars_eaten = 0;

  // Open a file in writing mode
  char buffer[256];
  snprintf(buffer, sizeof(buffer), "%s.c", filename);

  fptr = fopen(buffer, "w");

  // Write some text to the file
  fprintf(fptr, "#include <stdio.h>\nint main() {\n");

  // while end of program is not reached continue
  while (program[c] != '\0') {

    // skip the whitespace
    if (program[c] == ' ') {
      c++;
      continue;
    }

    // check if it's in the stdio
    chars_eaten = is_standard_input_output(program, c, fptr);
    if (chars_eaten == -1) {
      error_checker(line_number, fptr);
      return;
    }
    c += chars_eaten;

    // check if it's a keyword
    // TODO create a compile_keywords.c file that has compileXXX routines in a
    // similar way to is_stdio function

    // increment the line if '\n is hit'
    if (program[c] == '\n') {
      line_number++;
      c++;
      continue;
    }

    // goto next char
    // later do sth about this logic, it shouldn't just increment, it should
    // enforce language grammar
    c++;
  }

  // temporary
  fprintf(fptr, "return 0;\n}");
  // Close the file
  fclose(fptr);
}

void compile(char *program, char *filename) {
  ciretoc(program, filename);
  // compile the c file and delete the .c file
  char buffer[256];
  snprintf(buffer, sizeof(buffer), "gcc %s.c -o %s", filename, filename);
  system(buffer);

  snprintf(buffer, sizeof(buffer), "rm -f %s.c", filename);
  system(buffer);
}

void error_checker(int line, FILE *fptr) {
  // print error msg
  printf("Error occurred at line %d", line);

  // close the file
  fprintf(fptr, "// error occurred around here");
  fclose(fptr);

  return;
}
