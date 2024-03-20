
#include <Python.h>
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>
#include "other.h"


static PyObject* process_numpy_array(PyObject* self, PyObject* args) {
    PyArrayObject* array;
    if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &array)) {
        return NULL;
    }
 
    // Accessing NumPy array properties

    int x=add(10,20);

    int nd = PyArray_NDIM(array);
    npy_intp* dims = PyArray_DIMS(array);
 
    printf("Received NumPy array with %d dimensions\n", nd);
    printf("Shape: ");
    for (int i = 0; i < nd; i++) {
        printf("%ld ", dims[i]);
    }
    printf("\n");
 
    // Accessing array data
    printf("Array data:\n");
    npy_intp size = PyArray_SIZE(array);
    double* data = (double*)PyArray_DATA(array);
    for (npy_intp i = 0; i < size; i++) {
        printf("%.2f ", data[i]);
    }
    printf("\n");
 
    // Return None indicating successful processing
    Py_INCREF(Py_None);
    return Py_None;
}
 
// Method definition table
static PyMethodDef numpy_extension_methods[] = {
    {"process_numpy_array", process_numpy_array, METH_VARARGS, "Process a NumPy array"},
    {NULL, NULL, 0, NULL} // Sentinel
};
 
// Module definition structure
static struct PyModuleDef numpy_extension_module = {
    PyModuleDef_HEAD_INIT,
    "numpy_extension",   // Module name
    "A module written in C to process NumPy arrays", // Module description
    -1,
    numpy_extension_methods
};


// Module initialization function
PyMODINIT_FUNC PyInit_numpy_extension(void) {
    import_array(); // Initialize NumPy C-API
    return PyModule_Create(&numpy_extension_module);
}
