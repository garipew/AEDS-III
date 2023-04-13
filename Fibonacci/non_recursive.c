#include <stdio.h>
#include <stdlib.h>

int Fibonacci(int a){

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

int main(){

    int f;

    printf("Type a number: ");
    scanf("%d", &f);

    printf("Fibonacci number %d = %d\n", f, Fibonacci(f));

}