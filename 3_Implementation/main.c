#include "calc.h"
#include <stdio.h>
int main(){
    int c;
    int a=0; int b=0;
    printf("enter any value");
    scanf("%d",&c);
    switch(c){
        case 1: printf("Enter two numbers");
                scanf("%d %d", &a, &b);
                printf("sum=%d",add(a,b));
                break;
        case 2: printf("Enter two numbers");
                scanf("%d %d", &a, &b);
                printf("difference=%d",subtract(a,b));
                break;
        case 3: printf("Enter two numbers");
                scanf("%d %d", &a, &b);
                printf("product=%d",multiply(a,b));
                break;
        case 4: printf("Enter two numbers");
                scanf("%d %d", &a, &b);
                printf("division=%d",divide(a,b));
                break;

    } 
    return 0;
}