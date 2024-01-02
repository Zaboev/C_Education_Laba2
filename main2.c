#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

double geometry(double array[], int count)
{
    double multiplication = 1;
    for (int i = 0; i < count; i++)
    {
        multiplication *= array[i];
    }
    double result = pow(multiplication, 0.5);
    return result;
}

double My_pow(double x, int n)
{
    if (n == 0)
    {
        return 1;
    }
    if (n % 2 == 0) 
    {
        return My_pow(x * x, n / 2);
    }
    else
    {
        return x * My_pow(x * x, (n - 1) / 2);
    }
}

int main()
{
    double array[] = { 13.0, 915.1, 51.156 };
    double result1 = geometry(array, sizeof(array) / sizeof(array[0]));
    printf("%f\n\n", result1);
    double x = 3.2;
    int n = 5;
    double result2 = My_pow(x, n);
    printf("%f", result2);
}