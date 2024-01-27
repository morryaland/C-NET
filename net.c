#include <stdlib.h>
#include <string.h>

#include "mlp.h"
#include "af.h"

struct _NEURON{
    float *inputs;
    float  output;
    float *weights;
};
struct _PERCEPTRON{
    float *inputs;
    int input_c;
    NEURON **neurons;
    int hidden_c;
    float *outs;
    int out_c;
};
void neuron_adder( NEURON *neuron )
{
    int n = sizeof(neuron->inputs)/sizeof(neuron->inputs[0]);
    for (int i = 0; i < n; i++)
        neuron->output += neuron->inputs[i] * neuron->weights[i];
}
PERCEPTRON* perceptron_create( int _input_c_, int _hidden_c_, int _out_c_ )
{
    PERCEPTRON *perceptron = (PERCEPTRON*) malloc( sizeof(PERCEPTRON) );
    perceptron->input_c = _input_c_;
    perceptron->hidden_c = _hidden_c_;
    perceptron->out_c = _out_c_;
    perceptron->inputs = NULL;
    perceptron->neurons = NULL;
    perceptron->outs = NULL;
    return perceptron;
}
int perceptron_set_inputs( PERCEPTRON *perceptron, float *inputs )
{
    if ( (sizeof(inputs)/sizeof(inputs[0])) > perceptron->input_c ) {
        perceptron->inputs = NULL;
        return 1;
    }
    memcpy( perceptron->inputs, inputs, sizeof(inputs) );
    return 0;
}
int perceptron_neuron_create( PERCEPTRON *perceptron )
{
    perceptron->neurons = (NEURON**) calloc( perceptron->hidden_c, sizeof(NEURON*) );
    if (perceptron->neurons == NULL)
        return 1;
    for (int i = 0; i < perceptron->hidden_c; i++)
        perceptron->neurons[i] = (NEURON*) malloc( sizeof(NEURON) );
    return 0;
}
int perceptron_start( PERCEPTRON *perceptron, float *output )
{
    if ( perceptron_neuron_create(perceptron) ) {
        return 1;
    }
    output = calloc( perceptron->out_c, sizeof(float) );
    if (output == NULL)
        return 1;
    for (int i = 0; i < perceptron->hidden_c; i++) {
        perceptron->neurons[i]->inputs = perceptron->inputs;
        neuron_adder(perceptron->neurons[i]);
        output[0] += activation_function( ReLU, perceptron->neurons[i]->output );
    }
    return 0;
}
//
float activation_function( float (*op)(float), float in ) {
    return op(in);
}
float step   ( float x ) { 
    return x < 0 ?: 0, 1; 
}
float sigmoid( float x ) {
    1 / (1 + 1 / expf( x ));
}
float ReLU   ( float x ) {
    return x < 0 ?: 0, x; 
}