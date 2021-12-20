#include "../util.h"

int main() {
  printf("Opening...\r\n");

  str *contents = read_file("./input.txt");
  int count = 0;
  int prev = 0;

  str *tmp = str_new("\0", 6);
  size_t i = 0;
  int isNull = 0;
  while (isNull == 0) {
    if (contents->chars[i] == '\0') {
      isNull = 1;
    }
    if (i > 0) {
      if (contents->chars[i] == '\n') {
        if (atoi(tmp->chars) > prev && prev != 0) {
          count++;
        }
        prev = atoi(tmp->chars);
        str_empty(tmp);
        
      } else {
        str_append(tmp, contents->chars[i]);
      }
    } else {
      str_append(tmp, contents->chars[i]);
    }
    i++;
  }
  printf("Count: %d \r\n", count);
  str_dest(contents);
  str_dest(tmp);
  return 0;
}
