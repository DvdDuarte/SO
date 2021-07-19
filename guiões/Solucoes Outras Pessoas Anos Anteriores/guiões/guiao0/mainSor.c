#include <stdlib.h>
#include <stdio.h>
#include "simpleSor.h"

int main (int argc, char *argv[]) { //fazer ./simple 10 20

    //main e argumentos
    printf("argumento 0 - %s\n", argv[0]);
    printf("argumento 1 - %s\n", argv[1]);
    printf("argumento 1 - %s\n\n\n", argv[2]);

    //apontadores, endereços e scopes
    int i = atoi(argv[1]);
    int *ptr = &i;

    printf("size i - %lu\n", sizeof(i));
    printf("size ptr - %lu\n\n\n", sizeof(ptr));

    printf("value of i - %d\n", i);
    printf("value of ptr - %lu\n\n\n", ptr);

    int res = inc1 (i);
    printf("value of i - %d\n", i);
    printf("value of res - %d\n\n\n", res);

    res = inc2 (ptr);
    printf("value of res - %d\n", res);
    printf("value of i - %d\n\n\n", i);

    //arrays
    int arr[2]; //int *arr = malloc(sizeof(int) * 2);
    arr[0] = atoi (argv[1]);
    arr[1] = atoi (argv[2]);

    printf ("arr[0] - %d\narr[1] - %d\n", arr[0], arr[1]);
    printf("&arr[0] - %lu\n&arr[1] - %lu\n\n\n", &arr[0], &arr[1]);

    printf("arr - %lu\narr+1 - %lu\n\n", arr, arr+1);
    printf("*arr - %d\n*arr+1 - %d\n\n\n", *arr, *arr+1);

    free(arr);
    //depois do free o SO ainda não colocou nada nestes endereços, pelo que ainda têm os valores anteriores
    printf("depois free *arr - %d\ndepois free *arr+1 - %d\n\n\n", *arr, *arr+1);

    return 0;    
}