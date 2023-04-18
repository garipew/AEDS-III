#include "fibonacci.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int main(int argc, char* argv[]){

    int f, opt;

    while((opt = getopt(argc, argv, "rn")) != -1){
        
        printf("Type a number: ");
        scanf("%d", &f);
        switch(opt){
            case 'r':
                printf("Fibonacci number %d = %d\n", f, recursiveF(f));
                break;
            case 'n':
                printf("Fibonacci number %d = %ld\n", f, non_recursiveF(f));
                break;
            default:
                printf("Usage -r/-n");
        }

    }


}