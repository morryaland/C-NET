#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "include/mlp.h"

#define LEARN_DIR "/home/muly/code/C-NET/bin/teach"

int main()
{
  PERCEPTRON *p;
  float *in, *o;
  FILE *rav;
  int num = 0;
  struct dirent *ent;
  char pach[255];
  char *c;
  DIR *dir;

  p = malloc(sizeof(PERCEPTRON));

  in = calloc(INLEN, sizeof(float));
  o = calloc(OUTLEN, sizeof(float));

  perceptron_create(&p);

  for (int itr = 0; itr < 10; itr++) {
    dir = opendir(LEARN_DIR);
    for (; (ent = readdir(dir)) != NULL ;) {
      if (ent->d_name[0] == '.')
        continue;
      strcpy(pach, LEARN_DIR);
      strcat(pach, "/");
      strcat(pach, ent->d_name);
      printf("%s\n", pach);
      rav = fopen(pach, "r");
      if (!rav)
        puts("ERROR: file open");
      for (int i = 0; i < INLEN; i++) {
        c = (char*)in;
        *(c + i * 4 + 0) = getc(rav);
        *(c + i * 4 + 1) = getc(rav);
        *(c + i * 4 + 2) = getc(rav);
        *(c + i * 4 + 3) = getc(rav);
      }
      num = strtol( ent->d_name, NULL, 10);
    
      perceptron_set_inputs(p, in);
      perceptron_start(p, o);

      /* вывод аутпутов в консось*/
      for (int i = 0; i < OUTLEN; i++) {
        printf("%d ", (int)o[i]);
      }
      putchar('\n');
      fclose(rav);
    }
    closedir(dir);
  }
  return 0;
}
