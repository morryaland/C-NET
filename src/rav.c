#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "include/rav.h"
#include "include/mlp.h"


int rav_read_file( char *file_name, float *in, int *num)
{
  char pach[255];
  char *c;

  strcpy(pach, LEARN_DIR);
  strcat(pach, "/");
  strcat(pach, file_name);
  FILE *rav = fopen(pach, "r");
  if (!rav)
    puts("ERROR: file open");
  for (int i = 0; i < INLEN; i++) {
    c = (char*)in;
    *(c + i * 4 + 0) = getc(rav);
    *(c + i * 4 + 1) = getc(rav);
    *(c + i * 4 + 2) = getc(rav);
    *(c + i * 4 + 3) = getc(rav);
  }
  *num = strtol( file_name, NULL, 10);
  fclose(rav);
  return 0;
}
