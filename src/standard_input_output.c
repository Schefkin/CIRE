#include "standard_input_output.h"
#include <regex.h>
#include <stdio.h>
#include <string.h>

// return the amount by which I have to move
int is_standard_input_output(char *s, int i, FILE *fptr) {
  // check if Say
  if (memcmp("Say", s + i, 3) == 0) {
    // TODO creation of substring should be handeled by a helper tool

    // Say
    char *start = s + i;

    // .
    char *end = strchr(s + i + 1, '.');

    // +1 to include the dot at the end, because indexing of string begins at 0
    // but initialisation of array has to be one +1 element
    int extracted_str_len = end - start + 1;

    // initialise string with the length os len
    // "Hi" would need 3 bytes in this case H + i + '\0'
    char ss[extracted_str_len + 1];

    strncpy(ss, start, extracted_str_len);
    ss[extracted_str_len] = '\0';

    return write_say(ss, fptr);
  }

  return 0;
}

int write_say(char *ss, FILE *fptr) {
  // grammar checks

  // Variable to store initial regex()
  regex_t regex;

  // Variable for return type
  int regex_value;

  // Creation of regEx
  // POSIX values are used in regcomp
  regex_value =
      regcomp(&regex, "Say, \"[^\"]*\"\\(, \\?[[:alnum:]]\\+\\)\\?[.]", 0);

  // Comparing pattern above with string in reg
  regex_value = regexec(&regex, ss, 0, NULL, 0);

  if (regex_value != 0) {
    printf("Syntax error\n");
    printf("Correct usage:\n\n");
    printf("Say, \"Hello world!\".\n");
    printf("or\n");
    printf("Say, \"Hello %%s\", [varName].\n\n");
    return -1;
  }

  // Free compiled regex
  regfree(&regex);

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
