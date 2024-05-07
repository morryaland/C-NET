#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/mlp.h"

int main()
{
  PERCEPTRON *p = malloc(sizeof(PERCEPTRON));
  float *in = calloc(INLEN, sizeof(float));
  float *o = calloc(OUTLEN, sizeof(float));
  for (int i = 0; i < INLEN; i++)
    in[i] = (float)(rand()%2);
  perceptron_create(&p, in);
  for (int lol = 0; lol < 10; lol++)
  {
    perceptron_start(p, o);
    for (int i = 0; i < OUTLEN; i++) {
      printf("%d ", (int)o[i]);
    }
    putchar('\n');
    memset(o, 0, OUTLEN * sizeof(float));
  }
  return 0;
}
