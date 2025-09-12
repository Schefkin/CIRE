#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

  // error checks
  if (argc != 3) {
    printf("Usage: cire compile/ciretoc xxx.cire");
    return 0;
  }
  if (strcmp(argv[1], "compile") != 0 && strcmp(argv[1], "ciretoc") != 0) {
    printf("Usage: cire compile/ciretoc xxx.cire");
    return 0;
  }

  FILE *fp;
  char *buffer = NULL;
  size_t len;

  fp = fopen(argv[2], "rb");

  // check if file exists
  if (!fp) {
    printf("file %s does not exist", argv[2]);
    return 0;
  }

  fseek(fp, 0, SEEK_END);
  len = ftell(fp);
  rewind(fp);
  buffer = malloc(len + 1);
  if (NULL == buffer) {
    // Handle malloc failure & exit
    exit(-1);
  }

  fread(buffer, 1, len, fp);
  fclose(fp);
  buffer[len] = '\0';

  // create string that contains simply the filename
  char *filename = strdup(argv[2]);
  int filename_length = strlen(filename);
  for (int i = 0; i < filename_length; i++) {
    if (filename[i] == '.') {
      filename[i] = '\0';
      break;
    }
  }

  // redirect toward the correct function
  if (strcmp(argv[1], "compile") == 0) {
    compile(buffer, filename);
  } else if (strcmp(argv[1], "ciretoc") == 0) {
    ciretoc(buffer, filename);
  }
  // buffer now contains the content of your file; do what you want with it
  // compile(buffer);

  free(buffer);
  buffer = NULL;

  return 0;
}
