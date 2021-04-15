#include "calc.h"
#include <stdio.h>
int main(){
    int c;
    printf("enter any value");
    scanf("%d",&c);
    switch(c){
        case 1: addition();
                break;
        case 2: subtraction();
                break;
        case 3: multiplication();
                break;
        case 4: division();
                break;

    } 
    return 0;
}