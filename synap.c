
#include <Python.h>
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
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>


static NdArray build_ndArray(PyArrayObject *array){
    double* data = (double*)PyArray_DATA(array);
    int nd = PyArray_NDIM(array);
    npy_intp* dims = PyArray_DIMS(array);
    int *shape=(int*)calloc(INT_SIZE,nd);
    for(int i=0;i<nd;i++) shape[i]=dims[i];

    NdArray arr= NdArray__init__(data,shape,nd); 
    return arr;
}



static PyObject* network_init(PyObject* self, PyObject* args) {
    int num_layers;
    if (!PyArg_ParseTuple(args, "i", &num_layers)) {
        return NULL;
    }
    Network *nn = Network__init__(num_layers);
    return PyCapsule_New(nn, NULL, NULL);
}
 
static PyObject* compile_network(PyObject* self, PyObject* args) {
    PyObject* network_capsule;
    PyArrayObject* X_train_obj;
    if (!PyArg_ParseTuple(args, "OO", &network_capsule, &X_train_obj)) {
        return NULL;
    }
    Network *nn = PyCapsule_GetPointer(network_capsule, NULL);

    NdArray X_train=build_ndArray(X_train_obj);
    _compile(nn, X_train);
    Py_RETURN_NONE;
}
 
static PyObject* add(PyObject* self, PyObject* args) {
    PyObject* network_capsule;
    int neurons;
    if (!PyArg_ParseTuple(args, "Oi", &network_capsule, &neurons)) {
        return NULL;
    }
    Network *nn = PyCapsule_GetPointer(network_capsule, NULL);
    nn_add(nn,neurons);
    
    Py_RETURN_NONE;
}
 
static PyObject* train_network(PyObject* self, PyObject* args) {
    PyObject* network_capsule;
    PyArrayObject* X_train_obj;
    PyArrayObject* y_train_obj;
    int epochs;
    if (!PyArg_ParseTuple(args, "OOOi", &network_capsule, &X_train_obj, &y_train_obj, &epochs)) {
        return NULL;
    }
    Network *nn = PyCapsule_GetPointer(network_capsule, NULL);
    NdArray X_train=build_ndArray(X_train_obj);
    NdArray y_train=build_ndArray(y_train_obj);
    train(nn, X_train, y_train, epochs);
    Py_RETURN_NONE;
}
 
static PyMethodDef NetworkMethods[] = {
    {"init", network_init, METH_VARARGS, "Initialize network"},
    {"compile", compile_network, METH_VARARGS, "Compile network"},
    {"train", train_network, METH_VARARGS, "Train network"},
    {"add", add, METH_VARARGS, "add layer"},
    {NULL, NULL, 0, NULL}  // Sentinel
};
 
static struct PyModuleDef synapc = {
    PyModuleDef_HEAD_INIT,
    "synapc",
    "Module for network operations",
    -1,
    NetworkMethods
};
 
PyMODINIT_FUNC PyInit_synapc(void) {
    return PyModule_Create(&synapc);
}
