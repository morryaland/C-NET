#include "mlp.h"

PERCEPTRON *perceptron;

int main()
{
    // 1 1: 1
    // 0 1: 0
    // 1 0: 0
    // 0 0: 1
    float inputs[] = { 0, 0 };
    float *output;
    perceptron = perceptron_create(2, 2, 1);
    perceptron_set_inputs( perceptron, inputs );
    perceptron_start( perceptron, output );
    return 0;
}