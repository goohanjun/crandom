// MacOS
#include <Python.h>
// Linux
// #include <Python.h>
#include <iostream>

#include "singleton.h"
using namespace std;

typedef unsigned long long int ullong;
typedef unsigned int uint;

static PyObject* errorObject;

struct cRandom {
    ullong u, v, w;

    cRandom(ullong j) {
        seed(j);
    }
    inline void seed(ullong j) {
        v = 4101842887655102017LL;
        w = 1;
        u = j ^ v;
        int64();
        v = u;
        int64();
        w = v;
        int64();
    }
    inline ullong int64() {
        u = u * 2862933555777941757LL + 7046029254386353087LL;
        v ^= v >> 17;
        v ^= v << 31;
        v ^= v >> 8;
        w = 4294957665U * (w & 0xffffffff) + (w >> 32);
        ullong x = u ^ (u << 21);
        x ^= x >> 35;
        x ^= x << 4;
        return (x + v) ^ w;
    }
    inline double doub() {
        return 5.42101086242752217E-20 * int64();
    }
    inline double int32() {
        return (uint)int64();
    }
    inline double uniform(double low, double high) {
        return doub() * (high - low) + low;
    }
};

PyObject* uniform(PyObject* dummy, PyObject* args) {
    cRandom* ptr = Singleton<cRandom>::getInstance();
    double sample = ptr->doub();
    return PyFloat_FromDouble(sample);
}

PyObject* seed(PyObject* self, PyObject* args) {
    if (not(Singleton<cRandom>::doesInstanceExist())) {
        PyErr_SetString(errorObject, "Singleton does not exist");
        return NULL;
    }

    PyObject* input;
    PyArg_ParseTuple(args, "O", &input);

    if (!PyLong_Check(input)) {
        PyErr_SetString(errorObject, "Input should be a long integer");
        return NULL;
    }

    cRandom* ptr = Singleton<cRandom>::getInstance();
    ptr->seed(ullong(input));

    Py_INCREF(Py_None);
    return Py_None;
}

PyMethodDef RandomFunctions[] = {
    {"seed", seed, METH_VARARGS, "set seed value from long."},
    {"uniform", uniform, METH_VARARGS, "sample from uniform distribution [0, 1]."},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef crandommodule = {
    PyModuleDef_HEAD_INIT,
    "cRandom",                 /* name of module */
    "Random number generator", /* module documentation, may be NULL */
    -1,                        /* size of per-interpreter state of the module,
                 or -1 if the module keeps state in global variables. */
    RandomFunctions};

PyMODINIT_FUNC PyInit_cRandom(void) {
    cRandom* ptr = new cRandom(ullong(long(0)));
    Singleton<cRandom>::setInstance(ptr);
    return PyModule_Create(&crandommodule);
}

int main(int argc, char* argv[]) {
    wchar_t* program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }

    /* Add a built-in module, before Py_Initialize */
    if (PyImport_AppendInittab("cRandom", PyInit_cRandom) == -1) {
        fprintf(stderr, "Error: could not extend in-built modules table\n");
        exit(1);
    }

    /* Pass argv[0] to the Python interpreter */
    Py_SetProgramName(program);

    /* Initialize the Python interpreter.  Required.
       If this step fails, it will be a fatal error. */
    Py_Initialize();

    return 0;
}
