#include "standard_input_output.h"
#include <regex.h>
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
    // TODO create a substring from Say ... to "."
    // pass the substring into write_say

    return write_say(s, i, fptr);
  }

  return 0;
}

int write_say(char *s, int i, FILE *fptr) {
  // grammar checks

  // Variable to store initial regex()
  regex_t regex;

  // Variable for return type
  int regex_value;

  // Creation of regEx
  // later improve the regex maybe, groups did not work for some reason, check
  // if dot is really being read value = regcomp(&reegex, "Say, \"[
  // a-zA-Z%\\]*\"(, [a-zA-Z0-9]+)?\\.", 0);
  // Say, "[^"]*"(, [a-zA-Z\d]+)?\.
  regex_value = regcomp(&regex, "Say, \"[^\"]*\".", 0);

  // Comparing pattern above with string in reg
  regex_value = regexec(&regex, s + i, 0, NULL, 0);

  if (regex_value != 0) {
    // TODO display on which line the error occurred
    // TODO return and error check for -1 in compiler.c, create error check
    // helper func in compiler.c and let each function/keyword handle its error
    // handling

    // create a line counter in compiler.c that
    // increments each time "\n" is passed and pass that value into this func
    // for error checking purpose
    printf("Syntax error\n");
    printf("Correct usage: Say, \"Hello world!\".");
    return 0;
  }

  // Free compiled regex
  regfree(&regex);

  // extract the value between quotes
  // char after first quote
  char *start = strchr(s + i, '"');

  // second quote
  char *end = strchr(start + 1, '"');

  // from after first quote to end excluding last quote
  int extracted_str_len = end - start - 1;

  // initialise string with the length os len
  // "Hi" would need 3 bytes in this case H + i + '\0'
  char str[extracted_str_len + 1];

  // Copy extrctd_str_len - 1(because last char will be " which I want to avoid)
  // chars starting from start + 1(the first char after quote) to str
  strncpy(str, start + 1, extracted_str_len);
  str[extracted_str_len] = '\0';

  // write to the c file
  fprintf(fptr, "printf(\"%s\");\n", str);

  // calculate the amount of chars that were used for the current line
  // gets a string that equals to (closest . + remaining s)
  char *result = strstr(s + i, ".");

  // gets the length of the current string + 1(dot at the end)
  int line_length = strlen(s + i) - strlen(result) + 1;
  // returns the amount of chars eaten
  return line_length;
}
