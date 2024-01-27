#ifndef _MLP_H_
#define _MLP_H_

#ifndef NULL
#define NULL ((void *)0)
#endif

#include <math.h>

struct _NEURON;
typedef struct _NEURON NEURON;

struct _PERCEPTRON;
typedef struct _PERCEPTRON PERCEPTRON;
void neuron_adder( NEURON *neuron );
PERCEPTRON* perceptron_create( int _input_c_, int _hidden_c_, int _out_c_ );
int perceptron_set_inputs( PERCEPTRON *perceptron, float *inputs );
int perceptron_neuron_create( PERCEPTRON *perceptron );
int perceptron_start( PERCEPTRON *perceptron, float *output );

#endif