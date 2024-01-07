#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef enum Error {
    NO_ERROR,
    INVALID_BASE,
    INVALID_NUMBER,
    MEMORY_ERROR,
} Error;

char char_to_int(char c)
{
    if (c >= '0' && c <= '9')
    {
        return c - '0';
    }
    else if (c >= 'a' && c <= 'z') {
        return c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'Z') {
        return c - 'A' + 10;
    }
    else {
        return -1;
    }
}

char int_to_char(int i) {
    if (i >= 0 && i <= 9) {
        return i + '0';
    }
    else if (i >= 10 && i <= 35) {
        return i - 10 + 'a';
    }
    else {
        return '?';
    }
}

char* add(char* a, char* b, int base, Error* error) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int len_c = len_a > len_b ? len_a + 1 : len_b + 1;
    char* c = (char*)malloc(len_c + 1);
    if (c == NULL) {
        *error = MEMORY_ERROR;
        return NULL;
    }
    memset(c, '0', len_c);
    c[len_c] = '\0';
    int carry = 0;
    for (int i = 0; i < len_c; i++) {
        int x = i < len_a ? char_to_int(a[len_a - i - 1]) : 0;
        int y = i < len_b ? char_to_int(b[len_b - i - 1]) : 0;
        if (x == -1 || y == -1) {
            *error = INVALID_NUMBER;
            free(c);
            return NULL;
        }
        int sum = x + y + carry;
        carry = sum / base;
        c[len_c - i - 1] = int_to_char(sum % base);
    }
    while (len_c > 1 && c[0] == '0') {
        len_c--;
        memmove(c, c + 1, len_c);
    }
    *error = NO_ERROR;
    return c;
}

char* sum(int base, int count, ...) {
    va_list args;
    va_start(args, count);
    char* result = (char*)malloc(2);
    if (result == NULL) {
        return NULL;
    }
    result[0] = '0';
    result[1] = '\0';
    Error error = NO_ERROR;
    for (int i = 0; i < count; i++) {
        char* s = va_arg(args, char*);
        char* t = add(result, s, base, &error);
        free(result);
        if (t == NULL) {
            return NULL;
        }
        result = t;
        if (error != NO_ERROR) {
            switch (error) {
            case INVALID_BASE:
                return "Invalid base";
            case INVALID_NUMBER:
                return "Invalid number";
            case MEMORY_ERROR:
                return "Memory error";
            default:
                return "Unknown error";
            }
        }
    }
    va_end(args);
    return result;
}

int main() {
    char* a = "101010";
    char* b = "111111";
    char* c = "1000000";
    char* d = "101";
    char* e = "111";
    char* f = "1010";
    char* s = sum(2, 6, a, b, c, d, e, f);
    if (s == NULL) {
        printf("Memory error\n");
        return 1;
    }
    if (strcmp(s, "Invalid base") == 0) {
        printf("Invalid base\n");
    }
    else if (strcmp(s, "Invalid number") == 0) {
        printf("Invalid number\n");
    }
    else if (strcmp(s, "Memory error") == 0) {
        printf("Memory error\n");
    }
    else {
        printf("%s\n", s);
        free(s);
    }
    return 0;
}
