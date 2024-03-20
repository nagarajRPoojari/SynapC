#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "../header_files/activation.h"
#include "../header_files/ndarray.h"
#include "../header_files/dense_layer.h"
#include "../header_files/num.h"
#include "../header_files/nn.h"
#include "../header_files/metric.h"
#include "../header_files/loss.h"


Network* Network__init__(int layers_count){
    Network *nn=(Network*)calloc(1,sizeof(Network));
    (*nn).i=-1;
    (*nn).layers=(Dense_layer*)calloc(layers_count,sizeof(Dense_layer));
    (*nn).architecture=(Connection*)calloc(layers_count,sizeof(Connection));
    (*nn).params=(Param*)calloc(layers_count,sizeof(Param));
    (*nn).memory=(Memory*)calloc(layers_count,sizeof(Memory));
    (*nn).gradient_tape=(Gradient*)calloc(layers_count,sizeof(Gradient));
    (*nn).metric=accuracy;
    (*nn).loss=cross_entropy;
    return nn;
}


void nn_add(Network *nn,int neurons){
    (*nn).i=(nn->i)+1;
    (*nn).layers[nn->i]=Dense_layer__init__(neurons);
}

void _compile(Network *nn,NdArray data){
    for(int i=0;i<=nn->i;i++){
        if(i==0){
            (*nn).architecture[i].activation="relu";
            (*nn).architecture[i].input_dim=data.shape[1];
            (*nn).architecture[i].output_dim=nn->layers[i].neurons;
        }else if(i>0 && i<nn->i){
            (*nn).architecture[i].activation="relu";
            (*nn).architecture[i].input_dim=nn->layers[i-1].neurons;
            (*nn).architecture[i].output_dim=nn->layers[i].neurons;
        }else{
            (*nn).architecture[i].activation="softmax";
            (*nn).architecture[i].input_dim=nn->layers[i-1].neurons;
            (*nn).architecture[i].output_dim=nn->layers[i].neurons;
        }
    }
}

void __init_weights(Network *nn,NdArray data){
    srand(time(NULL));
    for(int i=0;i<=nn->i;i++){
        int w_shape[]={nn->architecture[i].output_dim,nn->architecture[i].input_dim};
        int b_shape[]={1,nn->architecture[i].output_dim};
        (*nn).params[i].W=nd_uniform(-1,1,w_shape,2);
        (*nn).params[i].b=nd_zeros(b_shape,2);
    }  
}


NdArray _forward_prop(Network *nn,NdArray data){
    NdArray A_curr=data;
    NdArray *A_prev=(NdArray*)malloc(sizeof(NdArray));
    for(int i=0;i<=nn->i;i++){
        (*A_prev)=A_curr;
        NdArray *A_Z=nn->layers[i].forward(
            *A_prev,
            nn->params[i].W,
            nn->params[i].b,
            nn->architecture[i].activation);
        A_curr=A_Z[0];


        (*nn).memory[i].A=*A_prev;
        (*nn).memory[i].Z=A_Z[1];
        free(A_Z);
    }
    return A_curr;
}


void _backward_prop(Network *nn,NdArray predicted,NdArray actual){
    int num_samples=actual.shape[0];
    NdArray dscores=predicted;
    _select_and_add(dscores,actual,-1);
    nd_divide(dscores,num_samples);
    NdArray dA_prev=dscores;
    for(int i=nn->i;i>=0;i--){
        NdArray dA_curr=dA_prev;
        NdArray *ans=nn->layers[i].backward(
            dA_curr,
            nn->params[i].W,
            nn->memory[i].Z,
            nn->memory[i].A,
            nn->architecture[i].activation
        );
        dA_prev=ans[0];
        if(nn->memory[i].Z.data!=NULL) nd_free(nn->memory[i].Z);

    
        (*nn).gradient_tape[i].dW=ans[1];
        (*nn).gradient_tape[i].db=ans[2];

        free(ans);
    }
}


void _update(Network *nn,double lr){
    for(int i=0;i<=nn->i;i++){
        NdArray T=nd_transpose(nn->gradient_tape[i].dW);
        nd_multiply(T,lr);
        nd_multiply(nn->gradient_tape[i].db,lr);
        nd_add_ele(nn->params[i].W , T);
        nd_add_ele(nn->params[i].b, nn->gradient_tape[i].db);
        nd_free(nn->gradient_tape[i].db);
        nd_free(nn->gradient_tape[i].dW);
        nd_free(T);
    }
}

void train(Network *nn,NdArray X_train,NdArray y_train,int epochs){
    __init_weights(nn,X_train);
    double min_loss=__DBL_MAX__;
    for(int i=0;i<epochs;i++){
        NdArray yhat=_forward_prop(nn,X_train);
        double acc=nn->metric(yhat,y_train);
        double loss=nn->loss(yhat,y_train);
        _backward_prop(nn,yhat,y_train);
        _update(nn,0.1);
        if(i%1==0){
            printf("Epoch : %d ,  loss : %.15f\n",i+1,loss);
        }
        min_loss=loss<min_loss ? loss:min_loss;
    }
    printf("MIN LOSS : %.15f\n",min_loss);
}

