#include <stdio.h>
#include <stdlib.h>
#include "fibonacci.h"

long int non_recursiveF(int a){

    int f = 0;
    int f1 = 1;
    int t;

    if(a == 0)
        return 0;
    if(a == 1)
        return 1;

    // loop stars from fibonacci 2
    for(int i = 2; i <= a; i++){
        t = f + f1;
        f = f1;
        f1 = t;
    }

    return t;

}

int recursiveF(int a){

    if(a==0)
        return 0;
    if(a==1)
        return 1;
    return recursiveF(a-1) + recursiveF(a-2);

}