#ifndef DENSE_LAYER_H
#define DENSE_LAYER_H

#include "ndarray.h"
#include "activation.h"
typedef struct Dense_layer{
    int neurons;
    NdArray (*relu)(NdArray);
    NdArray (*softmax)(NdArray);
    NdArray* (*backward)(NdArray,NdArray,NdArray,NdArray,char*);
    NdArray* (*forward)(NdArray,NdArray,NdArray,char*);
}Dense_layer;


NdArray* backward(NdArray dA_curr,NdArray W_curr,NdArray Z_curr,NdArray A_prev,char *activation);
NdArray* forward(NdArray inputs,NdArray weights,NdArray bias,char *activation);
Dense_layer Dense_layer__init__(int neurons);
#endif