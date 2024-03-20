#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../header_files/activation.h"
#include "../header_files/num.h"
#include "../header_files/ndarray.h"
#include "../header_files/dense_layer.h"

Dense_layer Dense_layer__init__(int neurons){
    Dense_layer d;
    d.neurons=neurons;
    d.relu=relu;
    d.relu=softmax;
    d.backward=backward;
    d.forward=forward;
    return d;
}


NdArray relu_derivative(NdArray dA,NdArray Z){
    NdArray _dZ=nd_copy(dA);
    NdArray dZ=nd_maximum(_dZ,0);
    nd_free(_dZ);
    return dZ;
}


NdArray* backward(NdArray dA_curr,NdArray W_curr,NdArray Z_curr,NdArray A_prev,char *activation){
    NdArray dW;
    NdArray db;
    NdArray dA;
    NdArray A_prev_T;
    int *t=(int*)malloc(INT_SIZE*2);
    if(strcmp(activation,"softmax")==0){
        A_prev_T=nd_transpose(A_prev);
        dW=nd_product(A_prev_T , dA_curr);
        db=nd_sum(dA_curr,0);
        dA=nd_product(dA_curr,W_curr);
        
    }else if (strcmp(activation,"relu")==0){
        NdArray dZ=relu_derivative(dA_curr,Z_curr);
        A_prev_T=nd_transpose(A_prev);
        dW=nd_product(A_prev_T , dZ);
        db=nd_sum(dZ,0);
        dA=nd_product(dZ,W_curr);

        nd_free(dZ);
    }
    
    NdArray *tuple=(NdArray*)malloc(sizeof(NdArray)*3);
    tuple[0]=dA;
    tuple[1]=dW;
    tuple[2]=db;
    free(t);
    nd_free(A_prev_T);
    return tuple;
}

NdArray* forward(NdArray inputs,NdArray weights,NdArray bias,char *activation){
    int *temp=(int*)malloc(INT_SIZE*2);
    NdArray weights_T=nd_transpose(weights);
    NdArray Z=nd_product(inputs,weights_T);
    NdArray A;
    if(strcmp(activation,"relu")==0)
        A=relu(Z);
    else   A=softmax(Z);

    NdArray *tuple=(NdArray*)calloc(2,sizeof(NdArray));
    tuple[0]=A;
    tuple[1]=Z;
    free(temp);
    nd_free(weights_T);
    return tuple;
}

