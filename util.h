#ifndef UTIL_H
#define UTIL_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include "str.h"

/* Alternative to strlen, so we can pass the size of a char * as the buffer value to construct a str */
size_t chars_size(char * chars) {
  int isNull = 0;
  size_t i = 0;
  while (isNull == 0) {
    if (chars[i] == '\0') {
      isNull = 1;
    }
    i++;
  }
  return i;
}

str * read_file(char * path) {
  FILE * file = NULL;
  int err = fopen_s(&file, path, "r");
  if (err != 0 || file == NULL) {
    perror("Error opening file");
    return NULL;
  }
  
  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);
  
  str * contents = str_new("\0", (size_t)size);
  int code;
  long i;
  for (i = 0; i < size; i++) {
    if ((code = fgetc(file)) != EOF) {
      contents->chars[i] = (char)code;
    }
  }
  contents->size = (size_t) i;
  if (ferror(file)) {
    perror("I/O error");
  }
  fclose(file);
  return contents;
}

#endif
