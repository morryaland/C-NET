#ifndef AF_H
#define AF_H

/* step, sigmoid, ReLU */
float activation_function( float (*op)(float), float in );

float step   ( float x );
float sigmoid( float x );
float ReLU   ( float x );

#endif
