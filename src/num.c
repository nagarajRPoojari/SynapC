#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "../header_files/ndarray.h"
#include "../header_files/num.h"


//nd sum add given axis
void _add(NdArray arr,double *ans,int *index,int index_size,int axis){
    int sum=1;
    for(int i=0;i<arr.ndim;i++) sum*=arr.shape[i];
    int idx=0;
    for(int i=0;i<index_size;i++){
        int curr=sum/arr.shape[i];
        idx+= curr*index[i];
        sum=curr;
    }
    int sum2=1;
    for(int i=0;i<arr.ndim;i++) sum2*=i==axis? 1: arr.shape[i];
    int idx2=0;
    for(int i=0;i<index_size;i++){
        int curr= i==axis? 0: sum2/arr.shape[i];
        idx2+= curr*index[i];
        sum2=curr;
    }
    //_add
    int j=idx2;
    for(int i=idx;i<idx+sum;i++,j++){
        ans[j]+=arr.data[i];
    }
}
void _rec_sum(NdArray arr,double *ans,int *index,int axis,int i){
    if(i==axis){
        for(int j=0;j<arr.shape[i];j++){
            index[i]=j;
            
            _add(arr,ans,index,axis+1,i);
        }
    }else{
        for(int j=0;j<arr.shape[i];j++){
            index[i]=j;
            _rec_sum(arr,ans,index,axis,i+1);
        }
    }
}
NdArray nd_sum(NdArray arr,int axis){
    long size=arr.size;
    size/=arr.shape[axis];
    double *ans=(double*)calloc(size,DOUBLE_SIZE);
    int *index=(int*)calloc(arr.ndim,INT_SIZE);
    _rec_sum(arr,ans,index,axis,0);
    int *shape=(int*)malloc(INT_SIZE*arr.ndim);
    memcpy(shape,arr.shape, INT_SIZE*arr.ndim);
    shape[axis]=1;
    NdArray ans_arr=NdArray__init__(ans,shape,arr.ndim);

    free(index);
    return ans_arr;
}


int ans_i=0;
//nd product
int _getIndex(NdArray arr,int *index,int index_size){
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
void _matB(NdArray ans,NdArray A,NdArray B,int *indexA,int *indexB,int indexB_size){
    if(indexB_size==B.ndim-2){
        int row_i=_getIndex(A,indexA,A.ndim-1);
        for(int i=0;i<B.shape[B.ndim-1];i++){
            indexB[B.ndim-1]=i;
            int col_i=_getIndex(B,indexB,B.ndim);
            for(int j=0;j<B.shape[B.ndim-2];j++){
                ans.data[ans_i]+= A.data[row_i+j]* B.data[B.shape[B.ndim-1]*j+col_i];
            }
            ans_i++;
        }
    }else{
        for(int j=0;j<A.shape[indexB_size];j++){
            indexB[indexB_size]=j;
            _matB(ans,A,B,indexA,indexB,indexB_size+1);
        }
    }
}
double* _matA(NdArray ans,NdArray A,NdArray B,int *indexA,int index_size){
    if(index_size==A.ndim-1){
        int *indexB=(int*)calloc(B.ndim,INT_SIZE);
        _matB(ans,A,B,indexA,indexB,0);
        free(indexB);
    }
    else{
        for(int j=0;j<A.shape[index_size];j++){
            indexA[index_size]=j;
            _matA(ans,A,B,indexA,index_size+1);
        }
    }
}
NdArray nd_product(NdArray A,NdArray B){
    long size=A.size;
    int *tt=(int*)malloc(sizeof(int)*2);
    ans_i=0;
    for(int i=0;i<B.ndim;i++) size*=i==B.ndim-2 ? 1: B.shape[i];
    double *ans_arr=(double*)calloc(size,DOUBLE_SIZE);

    int ndim=2*A.ndim-2;
    int *shape=(int*)calloc(ndim,INT_SIZE);
    for(int i=0;i<A.ndim-1;i++)
        shape[i]=A.shape[i];

    for(int i=0;i<B.ndim-2;i++)
        shape[A.ndim-i-1]=B.shape[i];
    shape[ndim-1]=B.shape[B.ndim-1];

    NdArray ans=NdArray__init__(ans_arr,shape,ndim);
    int *index=(int*)calloc(A.ndim,INT_SIZE);
    _matA(ans,A,B,index,0);
    free(index);
    free(tt);
    return ans;
}



NdArray nd_transpose(NdArray A){
    //2D transpose
    int *shape=(int*)calloc(A.ndim,DOUBLE_SIZE);
    long size=A.size;
    for(int i=A.ndim-1;i>=0;i--){
        shape[i]=A.shape[A.ndim-i-1];
    }
    double *t=(double*)calloc(size,DOUBLE_SIZE);
    for(int i=0;i<A.shape[0];i++)
        for(int j=0;j<A.shape[1];j++)
            t[j*A.shape[0]+i]=A.data[i*A.shape[1]+j];
    return NdArray__init__(t,shape,A.ndim);
}




NdArray nd_exponent(NdArray A){
    long size=A.size;
    int *new_shape=(int*)calloc(A.ndim,INT_SIZE);
    memcpy(new_shape,A.shape,INT_SIZE*A.ndim);
    double *ans=(double*)calloc(size,DOUBLE_SIZE);
    for(int i=0;i<size;i++) ans[i]=exp(A.data[i]);
    return NdArray__init__(ans,new_shape,A.ndim);
}


void nd_sine(NdArray A){
    long size=A.size;
    for(int i=0;i<size;i++) A.data[i]=sin(A.data[i]);
}

void nd_cosine(NdArray A){
    long size=A.size;
    for(int i=0;i<size;i++) A.data[i]=cos(A.data[i]);
}


double nd_shrink(NdArray A){
    return A.data[0];
}


void nd_divide(NdArray A,double denm){
    long size=A.size;
    for(int i=0;i<size;i++) A.data[i]/=denm;
}
void nd_multiply(NdArray A,double factor){
    long size=A.size;
    for(int i=0;i<size;i++) A.data[i]*=factor;
}



void nd_divide_ele(NdArray A,NdArray B){
    long size=A.size;
    for(int i=0;i<size;i++) A.data[i]/=B.data[i];
}
void nd_add_ele(NdArray A,NdArray B){
    long size=A.size;
    for(int i=0;i<size;i++) A.data[i]-=B.data[i];
}


void nd_log(NdArray A){
    long size=A.size;
    for(int i=0;i<size;i++) A.data[i]=log(A.data[i]);
}



//not general purpose 
void _select_and_add(NdArray A,NdArray B,int val){
    for(int i=0;i<A.shape[0];i++){
        A.data[i*A.shape[1]+(int)B.data[i]]+=val;
    }
}


NdArray nd_maximum(NdArray A,int value){
    long size=A.size;
    double *ans=(double*)calloc(size,DOUBLE_SIZE);
    for(int i=0;i<size;i++) ans[i]=value>=A.data[i]? A.data[i]*0.01:A.data[i];
    int *new_shape=(int*)calloc(A.ndim,INT_SIZE);
    memcpy(new_shape,A.shape,INT_SIZE*A.ndim);
    return NdArray__init__(ans,new_shape,A.ndim);
}



NdArray nd_broadcast(NdArray A,int axis,int times){
    double *ans=(double*)calloc(times*A.size,DOUBLE_SIZE);
    int idx=0;
    for(int i=0;i<times;i++)
        for(int j=0;j<A.size;j++) ans[idx++]=A.data[j];


    int *new_shape=(int*)calloc(A.ndim,INT_SIZE);
    memcpy(new_shape,A.shape,INT_SIZE*A.ndim);
    new_shape[axis]=times;
    return NdArray__init__(ans,new_shape,A.ndim);
}

NdArray nd_copy(NdArray A){
    double *ans=(double*)calloc(A.size,DOUBLE_SIZE);
    int *new_shape=(int*)calloc(A.ndim,INT_SIZE);
    memcpy(ans,A.data,DOUBLE_SIZE*A.size);
    memcpy(new_shape,A.shape,INT_SIZE*A.ndim);
    return NdArray__init__(ans,new_shape,A.ndim);
}


double _double_rand(double low,double high){
    double sd=(double)rand()/RAND_MAX;
    double r=sd*(2.0-1.0);
    return r;
}


NdArray nd_uniform(double low,double high,int *shape,int ndim){
    int size=1;
    for(int i=0;i<ndim;i++) size*=shape[i];
    double *ans=(double*)calloc(size,DOUBLE_SIZE);
    for(int i=0;i<size;i++){
         ans[i]=_double_rand(low,high)*(sqrt(2.0/shape[0]));
    }
    int *new_shape=(int*)calloc(ndim,INT_SIZE);
    memcpy(new_shape,shape,INT_SIZE*ndim);
    NdArray res=NdArray__init__(ans,new_shape,ndim);
    return res;
}

NdArray nd_zeros(int *shape,int ndim){
    int size=1;
    for(int i=0;i<ndim;i++) size*=shape[i];
    double *ans=(double*)calloc(size,DOUBLE_SIZE);
    return NdArray__init__(ans,shape,ndim);
}

