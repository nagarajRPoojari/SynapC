#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "../header_files/ndarray.h"
#include "../header_files/num.h"
#include "../header_files/nn.h"

double cross_entropy(NdArray predicted,NdArray actual){
    int *t=(int*)malloc(sizeof(int)*2);
    double total_sum=0;
    for(int i=0;i<actual.shape[0];i++){
        int x=i*predicted.shape[1]+(int)actual.data[0];
        double prob=predicted.data[x];
        total_sum+= -log(prob);
    }
    free(t);
    return total_sum/predicted.shape[0];
}
