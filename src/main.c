#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "include/mlp.h"
#include "include/rav.h"

#define RESET "\033[0m"
#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"

int main()
{
  PERCEPTRON *p;
  float *in, *o;
  float error = 0;
  int real_num = 0;
  int net_num = 0;
  struct dirent *ent;
  DIR *dir;

  p = malloc(sizeof(PERCEPTRON));

  in = calloc(INLEN, sizeof(float));
  o = calloc(OUTLEN, sizeof(float));

  perceptron_create(&p);

  for (int itr = 0; itr < 100; itr++) {
    dir = opendir(LEARN_DIR);
    for (; (ent = readdir(dir)) != NULL ;) {
      if (ent->d_name[0] == '.')
        continue;
      
      rav_read_file(ent->d_name, in, &real_num);
    
      perceptron_set_inputs(p, in);
      perceptron_start(p, o);
      net_num = out_max(o);
      error = error_find(o, net_num, real_num); 
      weight_correct(p, in, net_num, error);

      if (real_num == net_num) {
        printf("%s%d == %d%s\n",
               GREEN, real_num, net_num, RESET);
      }
      else {
        printf("%s%d != %d%s\n",
               RED, real_num, net_num, RESET);
      }
    }
    closedir(dir);
  }
  for (int n = 0; n < 10; n++)
    for (int i = 0; i < 16; i++) {
      for (int j = 0; j < 16; j++) {
        printf("%d\t", (int)(p->n[n].w[j + i * 16]* 100));
      }
      putchar('\n');
    }
  return 0;
}
