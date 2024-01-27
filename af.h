#ifndef _AF_H_
#define _AF_H_

/* step, sigmoid, ReLU */
float activation_function( float (*op)(float), float in );

float step   ( float x );
float sigmoid( float x );
float ReLU   ( float x );

#endif