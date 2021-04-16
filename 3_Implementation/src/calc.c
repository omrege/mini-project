#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include "calc.h"
 
int add(int n1, int n2)
{   
    int a,b,total;
    a=n1;b=n2;
    total=a+b;
    return total;
}
 
int subtract(int n1, int n2)
{ 
    int a,b,total;
    a=n1;b=n2;
    total=a-b; 
    return total;
}
 
int multiply(int n1, int n2)
{
    int a,b,total;
    a=n1;b=n2;
    total=a*b; 
    return total;
}
 
int divide(int n1, int n2)
{
    int a,b,total;
    a=n1;b=n2;
    total=a/b;
    return total;
}
 
