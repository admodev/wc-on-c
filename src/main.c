#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

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
  FILE *file_pointer;
  int c, newline_count = 0;
  size_t n = 0, buffer_size = 1000;
  char *file_char = malloc(buffer_size);

  if (file_char == NULL) {
    perror("Memory allocation failed");
    return 1;
  }

  file_pointer = fopen(filename, "r");

  if (file_pointer == NULL) {
    perror("Error opening file");
    free(file_char);
    return 1;
  }

  while ((c = fgetc(file_pointer)) != EOF) {
    file_char[n++] = (char)c;

    if (c == '\n') {
      newline_count++;
    }

    if (n == buffer_size - 1) {
      buffer_size *= 2;
      char *temp = realloc(file_char, buffer_size);
      if (temp == NULL) {
        perror("Memory reallocation failed");
        free(file_char);
        fclose(file_pointer);
        return 1;
      }
      file_char = temp;
    }
  }

  file_char[n] = '\0';
  fclose(file_pointer);

  printf("Total lines in file: %d\n", newline_count);

  free(file_char);

  return 0;
}

int count_words_in_file(char *filename) {
  FILE *file_pointer;
  int c;
  int word_count = 0;
  int in_word = 0;
  size_t n = 0, buffer_size = 1000;
  char *file_char = malloc(buffer_size);

  if (file_char == NULL) {
    perror("Memory allocation failed");
    return 1;
  }

  file_pointer = fopen(filename, "r");

  if (file_pointer == NULL) {
    perror("Error opening file");
    free(file_char);
    return 1;
  }

  while ((c = fgetc(file_pointer)) != EOF) {
    if (isalnum(c)) {
      if (!in_word) {
        in_word = 1;
        word_count++;
      }
    } else {
      in_word = 0;
    }

    if (n == buffer_size - 1) {
      buffer_size *= 2;
      char *temp = realloc(file_char, buffer_size);
      if (temp == NULL) {
        perror("Memory reallocation failed");
        free(file_char);
        fclose(file_pointer);
        return 1;
      }
      file_char = temp;
    }
  }

  fclose(file_pointer);

  printf("Total words in file: %d\n", word_count);

  free(file_char);

  return 0;
}

int main(int argc, char *argv[]) {
  int c;

  if (argc < 2) {
    printf("Please, pass an argument.\n");

    return 1;
  }

  while ((c = getopt(argc, argv, ":clw:h:")) != -1) {
    switch (c) {
    case 'c':
      count_bytes_in_file(argv[2]);
      break;
    case 'l':
      count_lines_in_file(argv[2]);
      break;
    case 'w':
      count_words_in_file(argv[2]);
      break;
    default:
      helper_function();
      break;
    }
  }

  return 0;
}
