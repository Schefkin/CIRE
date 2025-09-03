#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

int main(int argc, char *argv[]) {

  // error checks
  if (argc != 2) {
    printf("Usage: cirec xxx.cire");
    return 0;
  }

  FILE *fp;
  char *buffer = NULL;
  size_t len;

  fp = fopen(argv[1], "rb");

  // check if file exists
  if (!fp) {
    printf("file %s does not exist", argv[1]);
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

  // buffer now contains the content of your file; do what you want with it
  compile(buffer);

  free(buffer);
  buffer = NULL;

  return 0;
}
