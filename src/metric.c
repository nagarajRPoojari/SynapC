#include<stdio.h>
#include<math.h>
#include "../header_files/ndarray.h"
#include "../header_files/num.h"



double accuracy(NdArray predicted,NdArray actual){
    int total_sum=0;
    for(int i=0;i<actual.shape[0];i++){
        double maxV=predicted.data[i*predicted.shape[1]],maxIdx=0;
        for(int j=0;j<predicted.data[1];j++){
            double curr=predicted.data[i*predicted.shape[1]+j];
            if(curr>maxV){
                maxV=curr;
                maxIdx=j;
            }
        }
        total_sum+= actual.data[i]==maxIdx ? 1:0;
    }
    return total_sum/actual.shape[0];
}