#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
// прототипчики мяу
int overscanf( const char *format, ...);
int overfscanf(FILE *stream, const char *format, ...);
int oversscanf(const char *str, const char *format, ...);

// стандартные флаги
int d(const char **input);
unsigned int u(const char **input);
float f(const char **input);
double lf(const char **input);
char c(const char **input);
char* s(const char **input);
unsigned int o(const char **input);
unsigned int x(const char **input);
unsigned int X(const char **input);

// нестандартные флаги
int Ro(const char **input);
int Zr(const char **input);
int Cv(const char **input, int base, int koef);
int CV(const char **input, int base);

int overscanf(const char *format, ...) {
    int strl;
    va_list args;
    va_start(args, format); 
    
    
    char input[BUFSIZ]; 
    if (fgets(input, sizeof(input), stdin) == NULL) {
        va_end(args);
        return -1;
    }

    if (input[(strl = strlen(input)) - 1] == '\n')
    {
        input[strl - 1] = '\0';
    }

    const char *ptr = format;
    const char *str_input = input;

    while (*ptr != '\0') {
        if (*ptr == '%') {
            ptr++;
            switch (*ptr) {
                case 'd': {
                    int *iptr = va_arg(args, int*);
                    *iptr = d(&str_input);  
                    break;
                }
                case 'u': {
                    unsigned int *uiptr = va_arg(args, unsigned int*);
                    *uiptr = u(&str_input);
                    break;
                }
                case 'f': {
                    float *fptr = va_arg(args, float*);
                    *fptr = f(&str_input);
                    break;
                }
                case 'l': {
                    if (*(ptr + 1) == 'f') {
                        double *fptr = va_arg(args, double*);
                        *fptr = lf(&str_input); 
                        ptr++; 
                        break;
                    }
                    break;
                }
                case 'c': {
                    char *cptr = va_arg(args, char*);
                    *cptr = c(&str_input); 
                    break;
                }
                case 's': {
                    char **strptr = va_arg(args, char**); 
                    *strptr = s(&str_input);   
                    break;
                }
                 case 'o': {
                    unsigned int *optr = va_arg(args, unsigned int*);
                    *optr = o(&str_input);  
                    break;
                }
                case 'x': {
                    unsigned int *xptr = va_arg(args, unsigned int*);
                    *xptr = x(&str_input);
                    break;
                }
                case 'X': {
                    unsigned int *Xptr = va_arg(args, unsigned int*);
                    *Xptr = X(&str_input);
                    break;
                }
                case 'R': {
                    if (*(ptr + 1) == 'o') {
                        int* roptr = va_arg(args, int*);
                        *roptr = Ro(&str_input); 
                        ptr++; 
                    }
                    break;
                }
                case 'Z': {

                    if (*(ptr + 1) == 'r') {
                        input[strcspn(input, "\n")] = 0;
                        int *uiptr = va_arg(args, int*);
                        *uiptr = Zr(&str_input);  
                        ptr++; 
                    }
                    break;
                }
                case 'C': {
                    if (*(ptr + 1) == 'v') {
                        int *iptr = va_arg(args, int*);
                        int base = va_arg(args, int);
                        *iptr = Cv(&str_input, base, 1);
                        ptr++; 
                    } else if (*(ptr + 1) == 'V') {
                        int *iptr = va_arg(args, int*);
                        int base = va_arg(args, int);
                        *iptr = Cv(&str_input, base, 2); 
                        ptr++;
                    }
                    break;
                }
            }
        } else {
            ptr++;
        }
    }

    va_end(args);
    return 0;
}

int overfscanf(FILE *stream, const char *format, ...)
{
    va_list args;
    va_start(args, format); 
    
    
    char input[100]; 
    if (fgets(input, sizeof(input), stream) == NULL) {
        va_end(args);
        return -1;
    }

    const char *ptr = format;
    const char *str_input = input;

    while (*ptr != '\0') {
        if (*ptr == '%') {
            ptr++;
            switch (*ptr) {
                case 'd': {
                    int *iptr = va_arg(args, int*);
                    *iptr = d(&str_input);  
                    break;
                }
                case 'u': {
                    unsigned int *uiptr = va_arg(args, unsigned int*);
                    *uiptr = u(&str_input);
                    break;
                }
                case 'f': {
                    float *fptr = va_arg(args, float*);
                    *fptr = f(&str_input);
                    break;
                }
                case 'l': {
                    if (*(ptr + 1) == 'f') {
                        double *fptr = va_arg(args, double*);
                        *fptr = lf(&str_input); 
                        ptr++; 
                        break;
                    }
                    break;
                }
                case 'c': {
                    char *cptr = va_arg(args, char*);
                    *cptr = c(&str_input); 
                    break;
                }
                case 's': {
                    char **strptr = va_arg(args, char**); 
                    *strptr = s(&str_input);   
                    break;
                }
                 case 'o': {
                    unsigned int *optr = va_arg(args, unsigned int*);
                    *optr = o(&str_input);  
                    break;
                }
                case 'x': {
                    unsigned int *xptr = va_arg(args, unsigned int*);
                    *xptr = x(&str_input);
                    break;
                }
                case 'X': {
                    unsigned int *Xptr = va_arg(args, unsigned int*);
                    *Xptr = X(&str_input);
                    break;
                }
                case 'R': {
                    if (*(ptr + 1) == 'o') {
                        int* roptr = va_arg(args, int*);
                        *roptr = Ro(&str_input); 
                        ptr++; 
                    }
                    break;
                }
                case 'Z': {

                    if (*(ptr + 1) == 'r') {
                        input[strcspn(input, "\n")] = 0;
                        int *uiptr = va_arg(args, int*);
                        *uiptr = Zr(&str_input);  
                        ptr++; 
                    }
                    break;
                }
                case 'C': {
                    if (*(ptr + 1) == 'v') {
                        int *iptr = va_arg(args, int*);
                        int base = va_arg(args, int);
                        *iptr = Cv(&str_input, base, 1);
                        ptr++; 
                    } else if (*(ptr + 1) == 'V') {
                        int *iptr = va_arg(args, int*);
                        int base = va_arg(args, int);
                        *iptr = Cv(&str_input, base, 2); 
                        ptr++;
                    }
                    break;
                }
            }
        } else {
            ptr++;
        }
    }

    va_end(args);
    return 0;
}
int oversscanf(const char *str, const char *format, ...)
{
    va_list args;
    va_start(args, format); 
    
    const char *str_input = str;
    const char *ptr = format;

    while (*ptr != '\0') {
        if (*ptr == '%') {
            ptr++;
            switch (*ptr) {
                case 'd': {
                    int *iptr = va_arg(args, int*);
                    *iptr = d(&str_input);  
                    break;
                }
                case 'u': {
                    unsigned int *uiptr = va_arg(args, unsigned int*);
                    *uiptr = u(&str_input);
                    break;
                }
                case 'f': {
                    float *fptr = va_arg(args, float*);
                    *fptr = f(&str_input);
                    break;
                }
                case 'l': {
                    if (*(ptr + 1) == 'f') {
                        double *fptr = va_arg(args, double*);
                        *fptr = lf(&str_input); 
                        ptr++; 
                        break;
                    }
                    break;
                }
                case 'c': {
                    char *cptr = va_arg(args, char*);
                    *cptr = c(&str_input); 
                    break;
                }
                case 's': {
                    char **strptr = va_arg(args, char**); 
                    *strptr = s(&str_input);   
                    break;
                }
                 case 'o': {
                    unsigned int *optr = va_arg(args, unsigned int*);
                    *optr = o(&str_input);  
                    break;
                }
                case 'x': {
                    unsigned int *xptr = va_arg(args, unsigned int*);
                    *xptr = x(&str_input);
                    break;
                }
                case 'X': {
                    unsigned int *Xptr = va_arg(args, unsigned int*);
                    *Xptr = X(&str_input);
                    break;
                }
                case 'R': {
                    if (*(ptr + 1) == 'o') {
                        int* roptr = va_arg(args, int*);
                        *roptr = Ro(&str_input); 
                        ptr++; 
                    }
                    break;
                }
                case 'Z': {

                    if (*(ptr + 1) == 'r') {
                        int *uiptr = va_arg(args, int*);
                        *uiptr = Zr(&str_input);  
                        ptr++; 
                    }
                    break;
                }
                case 'C': {
                    if (*(ptr + 1) == 'v') {
                        int *iptr = va_arg(args, int*);
                        int base = va_arg(args, int);
                        *iptr = Cv(&str_input, base, 1);
                        ptr++; 
                    } else if (*(ptr + 1) == 'V') {
                        int *iptr = va_arg(args, int*);
                        int base = va_arg(args, int);
                        *iptr = Cv(&str_input, base, 2); 
                        ptr++;
                    }
                    break;
                }
            }
        } else {
            ptr++;
        }
    }

    va_end(args);
    return 0;
}

// стандартные флаги

int d(const char **input) {
    int value = 0;
    int sign = 1;

    while (isspace(**input)) {
        (*input)++;
    }

    if (**input == '-') {
        sign = -1;
        (*input)++;
    } else if (**input == '+') {
        (*input)++;
    }

    while (isdigit(**input)) {
        value = value * 10 + (**input - '0');
        (*input)++;
    }

    return value * sign; 
}

unsigned int u(const char **input) {
    unsigned int value = 0;

    while (isspace(**input)) {
        (*input)++;
    }

    while (isdigit(**input)) {
        value = value * 10 + (**input - '0');
        (*input)++;
    }

    return value;
}

float f(const char **input) {
    float value = 0;
    int divisor = 1;

    while (isspace(**input)) {
        (*input)++;
    }

    while (isdigit(**input)) {
        value = value * 10 + (**input - '0');
        (*input)++;
    }

    if (**input == '.') {
        (*input)++;
        while (isdigit(**input)) {
            value = value * 10 + (**input - '0');
            divisor *= 10;
            (*input)++;
        }
    }

    return value / divisor;
}

double lf(const char **input) {
    double value = 0;
    int divisor = 1;

    while (isspace(**input)) {
        (*input)++;
    }

    while (isdigit(**input)) {
        value = value * 10 + (**input - '0');
        (*input)++;
    }

    if (**input == '.') {
        (*input)++;
        while (isdigit(**input)) {
            value = value * 10 + (**input - '0');
            divisor *= 10;
            (*input)++;
        }
    }

    return value / divisor;
}
char c(const char **input)
{
    char c = **input;
    (*input)++;
    return c;
}
char* s(const char **input)
{
    const char *start = *input;
    while (**input != ' ' && **input != '\0') {
        (*input)++;
    }
    size_t length = *input - start;
    char *str = (char *)malloc(length + 1);
    if (str) {
        strncpy(str, start, length);
        str[length] = '\0';
    }
    return str;
}

unsigned int o(const char **input) {
    unsigned int value = 0;
    while (**input >= '0' && **input <= '7') { 
        value = value * 8 + (**input - '0');  
        (*input)++;  
    }
    return value;
}

unsigned int x(const char **input) {
    unsigned int value = 0;
    while ((**input >= '0' && **input <= '9') || (**input >= 'a' && **input <= 'f')) {  
        char c = **input;
        if (c >= '0' && c <= '9') {
            value = value * 16 + (c - '0'); 
        } else if (c >= 'a' && c <= 'f') {
            value = value * 16 + (c - 'a' + 10);  
        }
        (*input)++;  
    }
    return value;
}

unsigned int X(const char **input) {
    unsigned int value = 0;
    while ((**input >= '0' && **input <= '9') || (**input >= 'A' && **input <= 'F')) { 
        char c = **input;
        if (c >= '0' && c <= '9') {
            value = value * 16 + (c - '0'); 
        } else if (c >= 'A' && c <= 'F') {
            value = value * 16 + (c - 'A' + 10);  
        }
        (*input)++; 
    }
    return value;
}

int Ro(const char ** input) {
    char* romanNumerals[] = { "I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M" };
    int values[] = { 1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000 };
    
    int length = strlen(*input);
    int total = 0;
    int i = 0;

    while (i < length) {
        int matched = 0;
        for (int j = 12; j >= 0; j--) {
            int len = strlen(romanNumerals[j]);
            if (strncmp(*input + i, romanNumerals[j], len) == 0) {
                total += values[j];
                i += len;
                matched = 1;
                break;
            }
        }
        if (!matched) {
            return -1;
        }
    }

    return total;
}

int Zr(const char **input) {
    int capacity = 10; 
    int fibCount = 2;
    int length = strlen(*input);
    int value = 0, i;
    int fibIndex = 0;
    const char *str = *input;
    if (length == 0) {
        return 0;
    }

    int *fibArray = (int *)malloc(capacity * sizeof(int));
    if (fibArray == NULL) {
        return 0; 
    }

    fibArray[0] = 1;
    fibArray[1] = 1;

    while (fibArray[fibCount - 1] <= length)
    {
        if (fibCount == capacity)
          {
            capacity *= 2;
            int* temp = (int*)realloc(fibArray, capacity * sizeof(int));
            if (temp == NULL)
            {
              free(fibArray);
              return 0; 
            }
            fibArray = temp;
          }
        fibArray[fibCount] = fibArray[fibCount - 1] + fibArray[fibCount - 2];
        fibCount++;
    }
    
    for (i = 0; i < length; i++) {
        if (str[i] == '1') {
            if (i != length - 1) {
                value += fibArray[fibIndex];
            }
        }
        fibIndex++;
    }

    return value;
}

int Cv(const char **input, int base, int koef) {
    if (base < 2 || base > 36) {
        base = 10; 
    }
    int value = 0;
    char c;
    while ((c = **input) != '\0') {
        if (isdigit(c)) {
            int digit = c - '0';
            if (digit >= base) break; 
            value = value * base + digit;
            (*input)++;
        } else if (koef == 1 || koef == 2){
            if (isalpha(c)) {
                int digit = tolower(c) - 'a' + 10;
                if (digit >= base) break; 
                value = value * base + digit;
                (*input)++;
            }
        } 
        else {
            break; 
        }
    }
    return value;
}

int main() {
    int a;
    unsigned int b;
    float c;
    double d;
    int d_value;
    unsigned int u_value;
    float f_value;
    char c_value;
    char *s_value;
    unsigned int o_value, x_value, X_value;
    int ro_value, Cv_value, CV_value, zr_value;
    /*
    printf("Введите целое число (d): ");
    overscanf("%d", &a);
    printf("Целое число: %d\n", a);

    printf("Введите беззнаковое число (u): ");
    overscanf("%u", &b);
    printf("Беззнаковое число: %u\n", b);

    printf("Введите число с плавающей точкой (f): ");
    overscanf("%f", &c);
    printf("Число с плавающей точкой: %.6f\n", c);

    printf("Введите число с плавающей точкой (lf): ");
    overscanf("%lf", &d);
    printf("Число с плавающей точкой (double): %.6f\n", d);

    printf("Введите значение для %%c: ");
    overscanf("%c", &c_value);
    printf("Результат %%c: %c\n", c_value);

    printf("Введите значение для %%s: ");
    overscanf("%s", &s_value);
    printf("Результат %%s: %s\n", s_value);
    free(s_value); 

    printf("Введите октальное число (например, 123): ");
    overscanf("%o", &o_value);
    printf("Число в десятичной системе: %u\n", o_value);
    
    printf("Введите шестнадцатеричное число (например, 1a): ");
    overscanf("%x", &x_value);
    printf("Число в десятичной системе: %u\n", x_value);
    
    printf("Введите шестнадцатеричное число с заглавными буквами (например, 1A): ");
    overscanf("%X", &X_value);
    printf("Число в десятичной системе: %u\n", X_value);

    printf("Введите значение для %%Ro (римские числа): ");
    overscanf("%Ro", &ro_value);
    printf("Результат %%Ro: %d\n", ro_value);
*/

    printf("Введите значение для %%Zr (римские числа): ");
    overscanf("%Zr", &zr_value);
    printf("Результат %%Zr: %d\n", zr_value);

/*
    printf("Введите значение для %%Cv (система счисления): ");
    overscanf("%Cv", &Cv_value, 16); 
    printf("Результат %%Cv: %d\n", Cv_value);

    printf("Введите значение для %%CV (система счисления с верхним регистром): ");
    overscanf("%CV", &CV_value, 16); 
    printf("Результат %%CV: %d\n", CV_value);
*/
    return 0;
}
