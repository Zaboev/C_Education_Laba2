#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

typedef enum geometry_function_error_handler
{
    ARRAY_ELEMENT_VALUE_EQUALS_ZERO
} geometry_function_error_handler;

double geometry(double array[], int count)
{
    double multiplication = 1;
    for (int i = 0; i < count; i++)
    {
        if (array[i] == 0.0)
        {
            return ARRAY_ELEMENT_VALUE_EQUALS_ZERO;
        }
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
    double result1 = geometry(array, 3);
    if (result1 == ARRAY_ELEMENT_VALUE_EQUALS_ZERO)
    {
        printf("Array element value equals zero.\n");
    }
    else
    {
        printf("Function worked successfully.\n");
        printf("%f\n\n", result1);
    }
    double x = 3.2;
    int n = 5;
    double result2 = My_pow(x, n);
    printf("%f\n\n", result2);
}