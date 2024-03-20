#include <stdio.h>
#include <stdlib.h>
#include "../header_files/ndarray.h"



NdArray NdArray__init__(double *data,int *shape,int ndim){
    NdArray arr;
    arr.data=data;
    arr.shape=shape;
    arr.ndim=ndim;
    long size=1;
    for(int i=0;i<ndim;i++) size*=shape[i];
    arr.size=size;
    return arr;
}


void nd_free(NdArray A){
    if(A.shape!=NULL)
        free(A.shape);
    if(A.data!=NULL)
        free(A.data);
    
}


void nd_print(NdArray arr,int depth,int *index){
    if (depth == arr.ndim) {
        int flat_index = 0;
        for (int i = 0; i < arr.ndim; i++) {
            flat_index = flat_index * arr.shape[i] + index[i];
        }
        printf("%f ", arr.data[flat_index]);
    } else {
        printf("[");
        for (int i = 0; i < arr.shape[depth]; i++) {
            index[depth] = i;
            nd_print(arr,depth + 1, index);
            
        }
        printf("]");
        if (depth == 0) {
            printf("\n");
        }
    }
}