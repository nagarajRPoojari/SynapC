#include <stdio.h>
#include <stdlib.h>
 
// Define a structure to represent the n-dimensional array
typedef struct {
    double *data;
    int *shape;
    int ndim;
} NdArray;
 
int ans_i=0;

int getIndex(NdArray arr,int *index,int index_size){
    int sum=1;
    for(int i=0;i<arr.ndim;i++) sum*=arr.shape[i];
    int idx=0;
    for(int i=0;i<index_size;i++){
        int curr=sum/arr.shape[i];
        idx+= curr*index[i];
        sum=curr;
    }
    return idx;
}

void matB(NdArray ans,NdArray A,NdArray B,int *indexA,int *indexB,int indexB_size){
    if(indexB_size==B.ndim-2){
        int row_i=getIndex(A,indexA,A.ndim-1);
        for(int i=0;i<B.shape[B.ndim-1];i++){
            indexB[B.ndim-1]=i;
            int col_i=getIndex(B,indexB,B.ndim);
            for(int j=0;j<B.shape[B.ndim-2];j++){
                ans.data[ans_i]+= A.data[row_i+j]* B.data[B.shape[B.ndim-1]*j+col_i];
            }
            ans_i++;
        }
    }else{
        for(int j=0;j<A.shape[indexB_size];j++){
            indexB[indexB_size]=j;
            matB(ans,A,B,indexA,indexB,indexB_size+1);
        }
    }
}


double* matA(NdArray ans,NdArray A,NdArray B,int *indexA,int index_size){
    if(index_size==A.ndim-1){
        int *indexB=(int*)malloc(sizeof(int)*B.ndim);
        matB(ans,A,B,indexA,indexB,0);
    }
    else{
        for(int j=0;j<A.shape[index_size];j++){
            indexA[index_size]=j;
            matA(ans,A,B,indexA,index_size+1);
        }
    }
}

double* product(NdArray A,NdArray B){
    int size=1;
    for(int i=0;i<A.ndim-1;i++) size*=A.shape[i];
    for(int i=0;i<B.ndim;i++) size*=i==B.ndim-2 ? 1: B.shape[i];
    double *ans_arr=(double*)malloc(sizeof(double)*size);
    NdArray ans;
    ans.data=ans_arr;
    int *index=(int*)malloc(sizeof(int)*A.ndim);
    matA(ans,A,B,index,0);
    
    return ans_arr;
}


int main(){
    double data[] = {1, 2, 3, 4, 5, 6};
 
    int shape[] = {3,2}; 
    int ndim = 2;
 
    NdArray arr;
    arr.data = data;
    arr.shape = shape;
    arr.ndim = ndim;

    double data2[] = {1, 2, 3, 4, 5, 6};
 
    int shape2[] = {2,3}; 
    int ndim2 = 2; 

    NdArray arr2;
    arr2.data = data2;
    arr2.shape = shape2;
    arr2.ndim = ndim2;


    double* res =product(arr,arr2);

    for(int i=0;i<9;i++)
        printf("%f ",res[i]);

    printf("\n");
    return 0;
}