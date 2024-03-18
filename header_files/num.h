#ifndef NUM_H
#define NUM_H

#include "ndarray.h"

#define DOUBLE_SIZE (sizeof(double))
#define INT_SIZE (sizeof(int))
#define LONG_SIZE (sizeof(long))

//private
void _add(NdArray arr,double *ans,int *index,int index_size,int axis);
void _rec_sum(NdArray arr,double *ans,int *index,int axis,int i);
int _getIndex(NdArray arr,int *index,int index_size);
void _matB(NdArray ans,NdArray A,NdArray B,int *indexA,int *indexB,int indexB_size);
double* _matA(NdArray ans,NdArray A,NdArray B,int *indexA,int index_size);
double _double_rand(double low,double high);

NdArray nd_transpose(NdArray A);
NdArray nd_sum(NdArray arr,int axis);
NdArray nd_product(NdArray A,NdArray B);
NdArray nd_exponent(NdArray A);
NdArray nd_broadcast(NdArray A,int axis,int times);
NdArray nd_maximum(NdArray A,int value);
NdArray nd_copy(NdArray A);
NdArray nd_uniform(double low,double high,int *shape,int ndim);
NdArray nd_zeros(int *shape,int ndim);

void nd_log(NdArray A);
void _select_and_add(NdArray A,NdArray B,int val);
void nd_divide_ele(NdArray A,NdArray B);
void nd_add_ele(NdArray A,NdArray B);
void nd_sine(NdArray A);
void nd_cosine(NdArray A);
double nd_shrink(NdArray A);
void nd_divide(NdArray A,double denm);
void nd_multiply(NdArray A,double factor);
#endif