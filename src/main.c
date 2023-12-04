#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_bytes_for_file(char *filename) {
  FILE* file_pointer;
  int bytes;

  file_pointer = fopen(filename, "r");

  for (bytes = 0; getc(file_pointer) != EOF; ++bytes);

  printf("File size in bytes: %d\n", bytes);

  fclose(file_pointer);

  return bytes;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("Please, pass an argument.\n");

    return 1;
  }

  if (strcmp(argv[2], "-c")) {
    count_bytes_for_file(argv[2]);
  }

  return 0;
}
