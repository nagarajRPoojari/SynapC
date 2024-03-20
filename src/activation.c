#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../header_files/activation.h"
#include "../header_files/ndarray.h"
#include "../header_files/num.h"



NdArray relu(NdArray A){
    NdArray ans=nd_maximum(A,0);
    return ans;
}


NdArray softmax(NdArray A){
    int *t=(int*)malloc(sizeof(int)*2);
    NdArray exp_scores=nd_exponent(A);
    NdArray __sum=nd_sum(exp_scores,1);
    NdArray _sum=nd_broadcast(__sum,1,3);
    nd_divide_ele(exp_scores,_sum);

    nd_free(_sum);
    nd_free(__sum);
    free(t);
    return exp_scores;
}


