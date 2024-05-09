#ifndef MLP_H
#define MLP_H

#include <math.h>
#include <inttypes.h>

#define INLEN 256
#define OUTLEN 10
#define SMOOTH 1000

typedef struct {
  float  o;
  float *i;
  float *w;
} NEURON;

typedef struct {
  float *i;
  NEURON *n;
} PERCEPTRON;

int perceptron_create( PERCEPTRON **p );

int perceptron_set_inputs( PERCEPTRON *p, const float *in );

void neuron_adder( NEURON *n, uint16_t inlen );

int perceptron_neuron_create( PERCEPTRON *p );

int perceptron_start( PERCEPTRON *p, float *o );

int weight_correct( PERCEPTRON *p, const float *in, int num, float error );

float error_find( float *o, int net_num, int real_num); 

int out_max( float *out );

#endif
