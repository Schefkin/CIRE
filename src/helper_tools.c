#include <regex.h>
#include <stdlib.h>
#include <string.h>

char *generate_substring(char *start) {
  // .
  char *end = strchr(start + 1, '.');

  // +1 to include the dot at the end, because indexing of string begins at 0
  // but initialisation of array has to be one +1 element
  int extracted_str_len = end - start + 1;

  // initialise string with the length os len
  // "Hi" would need 3 bytes in this case H + i + '\0'
  // char ss[extracted_str_len + 1];
  char *ss = malloc(extracted_str_len + 1);

  strncpy(ss, start, extracted_str_len);
  ss[extracted_str_len] = '\0';

  return ss;
}

// check for grammar using regex
int vibe_check(char *str, char *regex_str) {

  // Variable to store initial regex()
  regex_t compiled_regex;

  // Variable for return type
  int regex_value;

  // Creation of regEx
  // POSIX values are used in regcomp
  regex_value = regcomp(&compiled_regex, regex_str, 0);

  // Comparing pattern above with string in reg
  regex_value = regexec(&compiled_regex, str, 0, NULL, 0);

  regfree(&compiled_regex);

  if (regex_value != 0) {
    return -1;
  } else {
    return 0;
  }
}
