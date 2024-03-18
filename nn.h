#ifndef NN_H
#define NN_H
#include "dense_layer.h"
#include "ndarray.h"
#include "metric.h"
#include "loss.h"
typedef struct{
    int input_dim;
    int output_dim;
    char *activation;
} Connection;

typedef struct {
    NdArray W;
    NdArray b;
}Param;

typedef struct {
    NdArray A;
    NdArray Z;
}Memory;

typedef struct {
    NdArray dW;
    NdArray db;
}Gradient;




typedef struct  {
    int i;
    Dense_layer *layers;
    Connection *architecture;
    Param *params;
    Memory *memory;
    Gradient *gradient_tape;
    double (*loss)(NdArray,NdArray);
    double (*metric)(NdArray,NdArray);
}Network;

Network *Network__init__(int layers);
void nn_add(Network *nn,int neurons);
void _compile(Network *nn,NdArray data);
void __init_weights(Network *nn,NdArray data);
void _backward_prop(Network *nn,NdArray predicted,NdArray actual);
NdArray _forward_prop(Network *nn,NdArray data);
void _update(Network *nn,double lr);
void train(Network *nn,NdArray X_train,NdArray y_train,int epochs);
#endif