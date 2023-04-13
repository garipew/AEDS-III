#include <stdio.h>
#include <stdlib.h>

int Fibonacci(int a){

    if(a==0)
        return 0;
    if(a==1)
        return 1;
    return Fibonacci(a-1) + Fibonacci(a-2);

}

int main(){

    int f;

    printf("Type a number: ");
    scanf("%d", &f);

    printf("Fibonacci number %d = %d\n", f, Fibonacci(f));

}