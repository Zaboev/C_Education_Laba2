#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

int* Search_Line(char*, int, ...);

int main(int argc, const char* argv[])
{
    int i, number_row, number_symbol, number_file, * values, * valuesPointer;
    values = Search_Line("star", 1, "k1ng.txt");
    valuesPointer = values;
    if (values == NULL)
    { 
        printf("Arguments invalid or file can not be open");
        return 1;
    }
    for (i = 1; *valuesPointer != 0; i++)
    {
        number_file = *valuesPointer++;
        number_row = *valuesPointer++;
        number_symbol = *valuesPointer++;
        printf("Count number %d in file %d: row %d, symbol %d\n", i, number_file, number_row, number_symbol);
    }
    if (values != NULL)
    {
        free(values);
    }
    return 0;
}

int* Search_Line(char* const str, int count, ...)
{
    int* values, *valuesPointer;
    va_list ap;
    FILE* file;
    char ch, * strPointer = str;
    int i, findedIndex = -1, number_row = 1, number_symbolInRow = 0;
    if (count < 1) 
    {
        return NULL;
    }
    values = calloc(BUFSIZ, sizeof(char));
    if (values == NULL) 
    {
        return NULL;
    }
    valuesPointer = values;
    va_start(ap, count);
    for (i = 0; i < count; i++)
    {
        if (!(file = fopen(va_arg(ap, char*), "r")))
        {
            continue;
        }
        strPointer = str;
        findedIndex = -1;
        number_row = 1;
        number_symbolInRow = 0;
        while ((ch = fgetc(file)) != EOF)
        {
            if (ch == '\n')
            {
                number_symbolInRow = 0;
                number_row++;
                findedIndex = -1;
                strPointer = str;
                continue;
            }
            number_symbolInRow++;
            if (ch == *strPointer++)
            {
                if (findedIndex == -1) findedIndex = number_symbolInRow;
            }
            else
            {
                strPointer = str;
                findedIndex = -1;
            }
            if (*strPointer == '\0')
            {
                *valuesPointer++ = (i + 1);
                *valuesPointer++ = number_row;
                *valuesPointer++ = findedIndex;
                strPointer = str;
                findedIndex = -1;
            }
        }
        fclose(file);
    }
    va_end(ap);
    return values;
}