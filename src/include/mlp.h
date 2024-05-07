#ifndef MLP_H
#define MLP_H

#include <math.h>
#include <inttypes.h>

#define INLEN 256
#define OUTLEN 10
#define HIDLEN 32
#define LAYERS 2

typedef struct {
  float  o;
  float *i;
  float *w;
} NEURON;

typedef struct {
  float *i;
  float *o;
  NEURON **n;
} PERCEPTRON;

void neuron_adder( NEURON *n, uint16_t inlen );

int perceptron_neuron_create( PERCEPTRON *p );

int perceptron_start( PERCEPTRON *p, float *o );

#endif
