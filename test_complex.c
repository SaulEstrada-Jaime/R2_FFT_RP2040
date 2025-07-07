#include "headers/complexwork.h"
#include <stdio.h>

int main(){
    complex a = {10, 0};
    complex s = {1, 2};
    int A = magnitude(a);
    printf("%u", A);
    printf("\n");
    complex res = dot_complex(a, s);
    printf("%.3f", res.Re);
    printf("\n");
    printf("%.3f", res.Im);
    printf("\n");
    return 0;
}