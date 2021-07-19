#include "simpleSor.h"

int inc1 (int arg) {

    arg++;

    return arg; 
}


int inc2 (int *arg) {

    (*arg)++;

    return *arg;
}