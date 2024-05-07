#include <stdlib.h>
#include <string.h>

#include "include/mlp.h"
#include "include/af.h"

void neuron_adder( NEURON *n, uint16_t inlen )
{
  n->o = 0;
  for (int i = 0; i < inlen; i++)
    n->o += n->i[i] * n->w[i];
}

int perceptron_create(PERCEPTRON **p, const float *in )
{
  (*p)->i = malloc(INLEN * sizeof(float)); 
  (*p)->o = malloc(HIDLEN * sizeof(float)); 
  memcpy((*p)->i, in, INLEN * sizeof(float));
  if (perceptron_neuron_create(*p) < 0)
    return -1; 
  return 0;
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
          p->n[i][j].w[m] = 0.5f + (rand()%2)/10.0f;
      }
    }
    return 0;
}

int perceptron_start( PERCEPTRON *p, float *o )
{
  memset(p->o, 0,HIDLEN * sizeof(float));
  for (int i = 0; i < LAYERS; i++) {
    if (i == LAYERS - 1)
      for (int j = 0; j < OUTLEN; j++) {
        p->n[i][j].i = p->o;
        neuron_adder(&(p->n[i][j]), HIDLEN);
        o[j] += activation_function(ReLU, p->n[i][j].o);
      }
    else if (!i) 
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
  if (x > 0)
    return 1;
  return 0;
}

float sigmoid( float x ) {
  return 1.0f / (1 + 1 / expf( x ));
}

float ReLU( float x ) {
  if (x > 0)
    return x;
  return 0;
}
