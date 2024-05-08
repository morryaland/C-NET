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
  (*p)->o = malloc(HIDLEN * sizeof(float)); 
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
    /* создаём массив указателей на нейроны (фигурирует в роли слоёв) */
    /*!alloc!*/
    p->n = malloc(LAYERS * sizeof(NEURON*));
    if (p->n == NULL)
      return -1;

    for (int i = 0; i < LAYERS; i++) {
      /* инициализируем слой нейронами */
      /*!alloc!*/
      p->n[i] = malloc(HIDLEN * sizeof(NEURON));

      for (int j = 0; j < HIDLEN; j++) {
        /*!alloc!*/
        p->n[i][j].w = malloc(INLEN * sizeof(float));

        for (int m = 0; m < INLEN; m++) {
          p->n[i][j].w[m] = 0.5f + (rand()%2)/10.0f;
        }
      }
    }
    return 0;
}

int perceptron_start( PERCEPTRON *p, float *o )
{
  /* чистка выходов */
  memset(o, 0, OUTLEN * sizeof(float));
  memset(p->o, 0,HIDLEN * sizeof(float));
  
  for (int i = 0; i < HIDLEN; i++) {
    p->n[0][i].i = p->i;
    neuron_adder(&(p->n[0][i]), INLEN);
    p->o[0] += activation_function(ReLU, p->n[0][i].o);
  }
  
  for (int i = 1; i < LAYERS - 1; i++) {
    for (int j = 0; j < HIDLEN; j++) {
      p->n[i][j].i = p->o;
      neuron_adder(&(p->n[i][j]), HIDLEN);
      p->o[j] += p->n[i][j].o;
    }
  }

  for (int i = 0; i < OUTLEN; i++) {
    p->n[LAYERS - 1][i].i = p->o;
    neuron_adder(&(p->n[LAYERS - 1][i]), HIDLEN);
    o[i] += activation_function(ReLU, p->n[LAYERS - 1][i].o);
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
