#include <stdio.h>
#include <string.h>

static int usage(const char *argv0)
{
  fprintf(stderr, "Usage: %s <key> <e|d>\n", argv0);
  return 1;
}

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
  int key, inputkey;
  char buffer[BUFFER_SIZE];
  char *ptr = buffer;
  char low, high, old, new;
  size_t len;

  /* Check and parse arguments */

  if (argc < 3) {
    return usage(argv[0]);
  }

  if (sscanf(argv[1], "%i", &inputkey) < 1) {
    return usage(argv[0]);
  }
  key = inputkey;

  if (strlen(argv[2]) != 1) {
    return usage(argv[0]);
  }

  if (*argv[2] == 'd') {
    key = -key;
  } else if (*argv[2] != 'e') {
    return usage(argv[0]);
  }

  /* Log key and get input from user */

  printf("Substitution key is set to %i\n", inputkey);

  fgets(buffer, BUFFER_SIZE, stdin);
  len = strlen(buffer);
  if (buffer[len - 1] == '\n') {
    buffer[len - 1] = 0;
  }

  printf("Input text supplied is: %s\n", buffer);

  /* Start doing the Caesar cipher and print as we go along */

  while (*ptr) {
    old = *ptr;
    if (*ptr >= 'A' && *ptr <= 'Z') {
      low = 'A';
      high = 'Z';
    } else if (*ptr >= 'a' && *ptr <= 'z') {
      low = 'a';
      high = 'z';
    } else {
      low = 0;
    }

    if (low) {
      *ptr += key;
      if (*ptr > high) {
        *ptr -= 26;
      } else if (*ptr < low) {
        *ptr += 26;
      }
    }
    new = *ptr;

    if (*argv[2] == 'e') {
      printf("unencrypted letter: %c | encrypted to letter: %c\n", old, new);
    } else {
      printf("encrypted letter: %c | unencrypted to letter: %c\n", old, new);
    }

    ptr++;
  }

  /* Print the finished result and peace out */

  printf("Output text: %s\n", buffer);

  return 0;
}
