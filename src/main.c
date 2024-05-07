#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/mlp.h"

int main()
{
    PERCEPTRON *p = malloc(sizeof(PERCEPTRON));
    float *in = malloc(INLEN * sizeof(float));
    memset(in, 1, INLEN * sizeof(float));
    float *outbuff = calloc(HIDLEN, sizeof(float));
    p->i = in;
    p->o = outbuff;
    float *o = calloc(OUTLEN, sizeof(float));
    perceptron_start(p, o);
    for (int i = 0; i < OUTLEN; i++) {
        printf("%f ", o[i]);
    }
    return 0;
}
