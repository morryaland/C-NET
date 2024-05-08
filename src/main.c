#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/mlp.h"
#include "include/spng.h"

int main()
{
  PERCEPTRON *p;
  float *in, *o;

  spng_ctx *ctx = spng_ctx_new(0);

  p = malloc(sizeof(PERCEPTRON));

  in = calloc(INLEN, sizeof(float));
  o = calloc(OUTLEN, sizeof(float));

  /* вырезать когда будет метод заполнения инпута */
  for (int i = 0; i < INLEN; i++)
    in[i] = (float)(rand()%2);
  /*#####*/

  perceptron_create(&p, in);

  for (int lol = 0; lol < 10; lol++) {
    perceptron_start(p, o);

    /* вывод аутпутов в консось*/
    for (int i = 0; i < OUTLEN; i++) {
      printf("%d ", (int)o[i]);
    }
    putchar('\n');
  }

  spng_ctx_free(ctx);
  return 0;
}
