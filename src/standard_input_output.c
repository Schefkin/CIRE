#include "standard_input_output.h"
#include "helper_tools.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// return the amount by which I have to move
int is_standard_input_output(char *s, int i, FILE *fptr) {

  // check if Say
  if (memcmp("Say", s + i, 3) == 0) {

    // grammar check
    char *regex = "Say, \"[^\"]*\"\\(, \\?[[:alnum:]]\\+\\)\\?[.]";

    char *error_message = "Syntax error\n"
                          "Correct usage:\n\n"
                          "Say, \"Hello world!\".\n"
                          "or\n"
                          "Say, \"Hello %s\", [varName].\n\n";

    int vc = vibe_check(s + i, regex);
    if (vc == -1) {
      printf("%s", error_message);
      return -1;
    }

    // generate substring from Say to .
    char *ss = generate_substring(s + i);

    int chars_eaten = write_say(ss, fptr);

    free(ss);

    return chars_eaten;
  }

  return 0;
}

int write_say(char *ss, FILE *fptr) {
  // extract the value between first " and .
  // char after first quote
  char *start = strchr(ss, '"');

  // .
  char *end = strchr(start + 1, '.');

  // from after first quote to end excluding .
  int extracted_str_len = end - start - 1;

  // initialise string with the given length
  // "Hi" would need the length of 3 in this case H + i + '\0'
  char str[extracted_str_len + 1];

  // chars starting from start + 1(the first char after quote) to .
  strncpy(str, start + 1, extracted_str_len);
  str[extracted_str_len] = '\0';

  // write to the c file
  fprintf(fptr, "printf(\"%s);\n", str);

  // calculate the amount of chars that were used for the current line
  // gets a string that equals to (closest . + remaining s)
  char *result = strstr(ss, ".");

  // gets the length of the current string + 1(dot at the end)
  int line_length = strlen(ss) - strlen(result) + 1;

  // returns the amount of chars eaten - last char which is incremented at the
  // end of the main while loop
  return line_length;
}
