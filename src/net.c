#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/mlp.h"
#include "include/af.h"

void neuron_adder( NEURON *n, uint16_t inlen )
{
  n->o = 0;
  /* умножаем входные данные на веса нейрона и суммируем в выход */
  for (int i = 0; i < inlen; i++)
    n->o += n->i[i] * n->w[i];
}

int perceptron_create( PERCEPTRON **p )
{
  /*!alloc!*/
  (*p)->i = malloc(INLEN * sizeof(float)); 
  if (perceptron_neuron_create(*p) < 0)
    return -1; 
  return 0;
}

int perceptron_set_inputs( PERCEPTRON *p, const float *in )
{
  memcpy(p->i, in, INLEN * sizeof(float));
  return 0;
}

int perceptron_neuron_create( PERCEPTRON *p )
{
  /* инициализируем слой нейронами */
  /*!alloc!*/
  p->n = malloc(OUTLEN * sizeof(NEURON));
  if (p->n == NULL)
    return -1;
  for (int i = 0; i < OUTLEN; i++) {
    /*!alloc!*/
    p->n[i].w = malloc(INLEN * sizeof(float));
    if (p->n[i].w == NULL)
      return -1;

    for (int j = 0; j < INLEN; j++) {
      p->n[i].w[j] = 0.5f;
    }
  }
  return 0;
}

int perceptron_start( PERCEPTRON *p, float *o )
{
  /* чистка выходов */
  memset(o, 0, OUTLEN * sizeof(float));
  
  for (int i = 0; i < OUTLEN; i++) {
    p->n[i].i = p->i;
    neuron_adder(&(p->n[i]), INLEN);
    o[i] += activation_function(ReLU, p->n[i].o);
  }
  return 0;
}

int weight_correct( PERCEPTRON *p, const float *in, int num, float error )
{
  for (int i = 0; i < INLEN; i++) {
    if (in[i] > 0.0f) {
      p->n[num].w[i] += error;
    }
  }
  return 0;
}

int out_max( float *out )
{
  int res = -1;
  float max = 0;
  for (int i = 0; i < OUTLEN; i++) {
    if (max < out[i]) {
      max = out[i];
      res = i;
    }
  }
  for (int i = 0; i < OUTLEN; i++)
    printf("%d:%d%% ", i, (int)(out[i] / max * 100));
  return res;
}

float error_find( float *o, int net_num, int real_num )
{
  //return -(1 + o[real_num] - o[net_num]) / SMOOTH;
  if (net_num == real_num)
    return 1.0f / SMOOTH;
  else
    return -1.0f / SMOOTH;
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
