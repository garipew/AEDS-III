#include "fibonacci.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int main(int argc, char* argv[]){

    int f, opt;

    while((opt = getopt(argc, argv, "rn")) != -1){
        

        switch(opt){
            case 'r':
                printf("Type a number: ");
                scanf("%d", &f);
                printf("Fibonacci number %d = %d\n", f, recursiveF(f));
                break;
            case 'n':
                printf("Type a number: ");
                scanf("%d", &f);
                printf("Fibonacci number %d = %ld\n", f, non_recursiveF(f));
                break;
            default:
                printf("Usage -r/-n\n");
        }

    }


}