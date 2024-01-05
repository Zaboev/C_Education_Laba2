#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

void search_string(char* search, int files, ...)
{
    va_list remnant;
    char* file_name;
    int i, j;
    char a;
    int line = 1;
    int word_num = 1;
    int word_result, helpy;
    int search_len = strlen(search);
    va_start(remnant, files);
    for (i = 0; i < files; i++)
    {
        FILE* file;
        file_name = va_arg(remnant, char*);
        if ((file = fopen(file_name, "r")) != NULL)
        {
            word_num = 1;
            line = 1;
            helpy = 0;
            while ((a = fgetc(file)) != EOF)
            {
                if (a == '\n')
                {
                    line++;
                    word_num = 1;
                }
                else if (a == *search)
                {
                    word_result = word_num + 1;
                    j = 0;
                    while (helpy < search_len && (a == *(search + j)))
                    {
                        a = fgetc(file);
                        j++;
                        helpy++;
                        word_num++;
                    }
                    if (helpy == search_len)
                    {
                        printf("From file %s we found in %d line by %d symbol\n", file_name, line, word_result - search_len + 1);
                        helpy = 0;
                    }
                    else
                    {
                        word_num -= helpy;
                        helpy = 0;
                    }
                }
                else
                {
                    word_num++;
                }
            }
            fclose(file);
        }
        else
        {
            printf("Hi\n");
            perror("E");
        }
    }
    va_end(remnant);
}

int main()
{
    search_string("star", 1, "k1ng.txt");
    return 0;
}
