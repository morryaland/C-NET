#include <stdlib.h>
#include <string.h>

#include "include/mlp.h"
#include "include/af.h"

void neuron_adder( NEURON *n, uint16_t inlen )
{
  for (int i = 0; i < inlen; i++)
    n->o += n->i[i] * n->w[i];
}

int perceptron_neuron_create( PERCEPTRON *p )
{
    p->n = calloc(LAYERS, sizeof(NEURON*));
    if (p->n == NULL)
      return -1;
    for (int i = 0; i < LAYERS; i++) {
      p->n[i] = calloc(HIDLEN, sizeof(NEURON));
      for (int j = 0; j < HIDLEN; j++) {
        p->n[i][j].w = malloc(INLEN * sizeof(float));
        for (int m = 0; m < INLEN; m++)
          p->n[i][j].w[m] = 0.5f;
      }
    }
    return 0;
}

int perceptron_start( PERCEPTRON *p, float *o )
{
  if (perceptron_neuron_create(p) < 0) {
    return -1;
  }
  for (int i = 0; i < LAYERS; i++) {
    if (i == LAYERS - 1)
      for (int j = 0; j < OUTLEN; j++) {
        if (!i) { 
          p->n[i][j].i = p->o;
          neuron_adder(&(p->n[i][j]), HIDLEN);
          o[j] += activation_function(ReLU, p->n[i][j].o);
        }
      }
    if (!i) 
      for (int j = 0; j < HIDLEN; j++) {
        p->n[i][j].i = p->i;
        neuron_adder(&(p->n[i][j]), INLEN);
        p->o[j] += activation_function(ReLU, p->n[i][j].o);
      }
    else {
      for (int j = 0; j < HIDLEN; j++) {
        p->n[i][j].i = p->o;
        neuron_adder(&(p->n[i][j]), HIDLEN);
        p->o[j] += activation_function(ReLU, p->n[i][j].o);
      }
    }
  }
  return 0;
}

float activation_function( float (*op)(float), float in ) {
    return op(in);
}

float step( float x ) { 
  return x < 0 ?: 0, 1; 
}

float sigmoid( float x ) {
  return 1.0f / (1 + 1 / expf( x ));
}

float ReLU( float x ) {
  return x < 0 ?: 0, x; 
}
