#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "header_files/dense_layer.h"
#include "header_files/activation.h"
#include "header_files/ndarray.h"
#include "header_files/num.h"
#include "header_files/metric.h"
#include "header_files/loss.h"
#include "header_files/nn.h"


int main(){
    clock_t start=clock();


    printf("hi");

    int *temp=(int*)malloc(sizeof(int)*2);
    double ans[][2]={{0.95120179 ,1.91491679},
            { 0.3833075  , 0.91120978},
            {-0.81297494 , 0.55403051},
            {-0.21698998 ,1.38962765}
    };

    int shape_x[]={4,2};
    double labels[]={0,2,2,2};
    int shape_y[]={4};

    NdArray X_train=NdArray__init__((double*)ans,shape_x,2);
    NdArray y_train=NdArray__init__((double*)labels,shape_y,1);
    
    nd_print(y_train,0,temp);



    
    Network *nn=Network__init__(4);
    printf("what the hell\n");


    nn_add(nn,2);
    nn_add(nn,4);
    nn_add(nn,4);
    nn_add(nn,3);

    _compile(nn,X_train);
    train(nn,X_train,y_train,200);


    double time_taken=((double)(clock()-start))/CLOCKS_PER_SEC;
    printf("%f \n",time_taken);

    
    return 0;
}



/*

for(int i=0;i<=nn->i;i++){
        printf("%d %d %s \n",nn->architecture[i].input_dim,nn->architecture[i].output_dim,nn->architecture[i].activation);
    }

    __init_weights(nn,X_train);


    for(int i=0;i<=nn->i;i++){
        nd_print(nn->params[i].W,0,temp);
    }





    NdArray got=_forward_prop(nn,X_train);
    nd_print(got,0,temp);

    _backward_prop(nn,got,y_train);*/