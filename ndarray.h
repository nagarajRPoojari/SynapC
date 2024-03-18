#ifndef ND_ARRAY_H
#define ND_ARRAY_H



typedef struct {
    double *data;
    int *shape;
    int ndim;
    long size;
} NdArray;

NdArray NdArray__init__(double *data,int *shape,int ndim);
void nd_print(NdArray arr,int depth,int *index);
void nd_free(NdArray A);
#endif