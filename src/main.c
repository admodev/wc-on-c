#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void helper_function() {
  printf("todo...");
}

int count_bytes_in_file(char *filename) {
  FILE* file_pointer;
  int bytes;

  file_pointer = fopen(filename, "r");

  for (bytes = 0; getc(file_pointer) != EOF; ++bytes);

  printf("File size in bytes: %d\n", bytes);

  fclose(file_pointer);

  return 0;
}

int count_lines_in_file(char *filename) {
  FILE* file_pointer;
  int newline_count;
  char file_char;

  file_pointer = fopen(filename, "r");
  file_char = fgetc(file_pointer);

  while(file_char != EOF) {
    if (file_char == '\n') {
      newline_count += 1;
    }
  }

  fclose(file_pointer);

  printf("Total lines in file: %d", newline_count);

  return 0;
}

int main(int argc, char *argv[]) {
  int c;

  if (argc < 2) {
    printf("Please, pass an argument.\n");

    return 1;
  }

  while ((c = getopt(argc, argv, ":cl:h:")) != -1) {
    switch (c) {
    case 'c':
      count_bytes_in_file(argv[2]);
      break;
    case 'l':
      count_lines_in_file(argv[2]);
      break;
    default:
      helper_function();
      break;
    }
  }

  return 0;
}
