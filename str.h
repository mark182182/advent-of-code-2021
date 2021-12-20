#ifndef STR_H
#define STR_H

#include <stdlib.h>
#include <stdio.h>

/* The size of the string should always contain at least a null termination
 * charater, if the memory allocation was possible. */
typedef struct {
  size_t size;
  size_t buf;
  char *chars;
} str;

str *str_new(char *chars, size_t buf) {
  /* We should use a smaller buffer for str, because char* is a pointer, so its size is only the size of the pointer and not the whole string it is pointing to */
  str *s = (str *)malloc(buf * 3);
  s->buf = buf * sizeof(char);
  s->chars = (char *)malloc(buf);
  int isNull = 0;
  size_t i = 0;
  while (isNull == 0) {
    s->chars[i] = chars[i];
    if (chars[i] == '\0') {
      isNull = 1;
    }
    i++;
  }
  s->size = i;
  if (s->chars == NULL) {
    perror("Failed to allocate memory");
  }
  return s;
}

void str_dest(str *s) {
  free(s->chars);
  free(s);
}

void str_realloc(str *dest, long dif) {
  if (dif < 0) {
    size_t new_buf = dest->buf + (size_t)labs(dif) - 1;
    dest->buf = new_buf;
    dest->chars = (char *)realloc(dest->chars, dest->buf);
    if (dest->chars == NULL) {
      perror("Failed to reallocate memory");
    }
  }
}

void str_empty(str *src) {
  free(src->chars);
  src->chars = (char *)malloc(src->buf);
  src->chars[0] = '\0';
  src->size = 1;
}

void str_append(str *dest, char c) {
  if (dest->size + 1 > dest->buf) {
    str_realloc(dest, (long)dest->buf + 1);
  }
  if (dest->size == 1) {
    dest->chars[0] = c;
    dest->chars[1] = '\0';
  } else {
    dest->chars[dest->size - 1] = c;
    dest->chars[dest->size] = '\0';
  }
  dest->size++;
}

void str_cat(str *dest, str *src) {
  long dif = (long)dest->buf - (long)dest->size - (long)src->size;
  size_t old_size = dest->size;
  str_realloc(dest, dif);
  size_t j;
  for (j = 0; j < src->size; j++) {
    dest->chars[old_size - 1 + j] = src->chars[j];
  }
  dest->size = old_size - 1 + j;
}

#endif
