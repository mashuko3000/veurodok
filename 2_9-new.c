#include <stdarg.h> 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdint.h>

#pragma warning(disable : 4996)

#define OSHIBKA NULL

typedef enum { STDOUT, FILES, STRING } Type;

char* int_to_str(int num);
char* unsigned_int_to_str(unsigned int num);
char* float_to_str(float num);
char* double_to_str(double num);
char* num_to_base(int num, int i);
char* Roman(int num);
char** Z(unsigned int num);
char* convert_base(int num, int base, char size);
char* str_to_base(char* str, int base);
char* iu_to_dumb(unsigned int num, int type);
int number_len(const int number);
char* exponent(double num, char type);
char* significand(double num, char type);

void d(int num, Type target, void* format);
void u(unsigned int num, Type target, void* format);
void f(float num, Type target, void* format);
void lf(double num, Type target, void* format);
void c(char c, Type target, void* format);
void s(char* str, Type target, void* format);
void o(int num, Type target, void* format);
void x(int num, Type target, void* format);
void X(int num, Type target, void* format);

void Ro(int num, Type target, void* format);
void Zr(unsigned int num, Type target, void* format);
void Cv(int num, int base, Type target, void* format);
void CV(int num, int base, Type target, void* format);
void To(char* str, int base, Type target, void* format);
void mi(int num, Type target, void* format);
void mu(unsigned int num, Type target, void* format);
void md(double num, Type target, void* format);
void mf(float num, Type target, void* format);

void where_print_c(char c, Type target, void* stream) {
    if (target == STDOUT) {
        fputc(c, stdout);
    }
    else if (target == FILES) {
        if (stream) {
            fputc(c, (FILE*)stream);
        }
    }
    else if (target == STRING) {
        if (stream) {
            char** str_ptr = (char**)stream;
            if (*str_ptr) {
                int i = (*str_ptr)[0] - '0';
                if (i < strlen(*str_ptr)) {
                    (*str_ptr)[i] = c;
                    (*str_ptr)[0] = (i + 1) + '0';
                }
            }
        }
    }
}
void where_print_s(char* str, Type target, void* stream) {
    if (target == STDOUT) {
        fputs(str, stdout);
    }
    else if (target == FILES) {
        if (stream) {
            fputs(str, (FILE*)stream);
        }
    }
    else if (target == STRING) {
        if (stream) {
            char** str_ptr = (char**)stream;
            if (*str_ptr) {
                int i = (*str_ptr)[0] - '0';
                int len = strlen(str);
                if (i + len + 1 <= strlen(*str_ptr)) {
                    memcpy((*str_ptr) + i, str, len);
                    (*str_ptr)[i + len] = '\0';
                    (*str_ptr)[0] = (i + len) + '0';
                }
            }
        }
    }
}

void my_printf(Type target, void* stream, char* format, va_list args) {
    char* str;
    int val;
    int val2;
    float fl;
    int k = 0;
    if (format == NULL) {
        return;
    }

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++;
            switch (format[i]) {
            case 'd': {
                d(va_arg(args, int), target, stream);
                break;
            }
            case 'u': {
                u(va_arg(args, unsigned int), target, stream);
                break;
            }
            case 'f': {
                fl = (float)va_arg(args, double);
                f(fl, target, stream);
                break;
            }
            case 'l': {
                if (format[i + 1] == 'f') {
                    lf(va_arg(args, double), target, stream);
                    i++;
                }
                break;
            }
            case 'c': {
                c(va_arg(args, int), target, stream);
                break;
            }
            case 's': {
                s(va_arg(args, char*), target, stream);
                break;
            }
            case 'o': {
                o(va_arg(args, int), target, stream);
                break;
            }
            case 'x': {
                x(va_arg(args, int), target, stream);
                break;
            }
            case 'X': {
                X(va_arg(args, int), target, stream);
                break;
            }
            case 'R': {
                if (format[i + 1] == 'o') {
                    Ro(va_arg(args, int), target, stream);
                    i++;
                }
                break;
            }
            case 'Z': {
                if (format[i + 1] == 'r') {
                    val = va_arg(args, unsigned int);
                    Zr(val, target, stream);
                    i++;
                }
                break;
            }
            case 'C': {
                if (format[i + 1] == 'v') {
                    val = va_arg(args, int);
                    val2 = va_arg(args, int);
                    Cv(val, val2, target, stream);
                    i++;
                }
                else if (format[i + 1] == 'V') {
                    val = va_arg(args, int);
                    val2 = va_arg(args, int);
                    CV(val, val2, target, stream);
                    i++;
                }
                break;
            }
            case 't': {
                if (format[i + 1] == 'o') {
                    str = va_arg(args, char*);
                    val = va_arg(args, int);
                    To(str, val, target, stream);
                    i++;
                }
                break;
            }
            case 'T': {
                if (format[i + 1] == 'O') {
                    str = va_arg(args, char*);
                    val = va_arg(args, int);
                    To(str, val, target, stream);
                    i++;
                }
                break;
            }
            case 'm': {
                if (format[i + 1] == 'i') {
                    mi(va_arg(args, int), target, stream);
                    i++;
                }
                else if (format[i + 1] == 'u') {
                    mu(va_arg(args, int), target, stream);
                    i++;
                }
                else if (format[i + 1] == 'd') {
                    md(va_arg(args, double), target, stream);
                    i++;
                }
                else if (format[i + 1] == 'f') {
                    fl = (float)va_arg(args, double);
                    mf(fl, target, stream);
                    i++;
                }
                break;
            }
            default:
                where_print_c(format[i], target, stream);
                break;
            }
        }
        else
            where_print_c(format[i], target, stream);
    }
    where_print_c('\n', target, stream);
}

void overprintf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    Type target = STDOUT;
    char* stream = NULL;
    my_printf(target, stream, (char*)format, args);
    va_end(args);
}

void overfprintf(FILE* stream, const char* format, ...) {
    va_list args;
    va_start(args, format);
    Type target = FILES;
    my_printf(target, stream, (char*)format, args);
    va_end(args);
}

int oversprintf(char** str, const char* format, ...) {
    if (*str == NULL) {
        return -1;
    }
    int i = 0;
    va_list args;
    va_start(args, format);
    int len = strlen(*str);
    char* stream = (char*)malloc(sizeof(char) * (len + 1024));
    if (stream == NULL) {
        va_end(args);
        return -1;
    }
    stream[0] = '0';
    stream[1] = '\0';

    Type target = STRING;
    my_printf(target, &stream, (char*)format, args); 
    i = stream[0] - '0';

    if (i > len) {
        memcpy(*str, stream + 1, len);
        (*str)[len] = '\0';
    }
    else {
        memcpy(*str, stream + 1, i);
        (*str)[i] = '\0';
    }
    free(stream);
    va_end(args);
    return i;
}




int main() {
    char* dtr = (char*)malloc(sizeof(char) * 100);
    if (dtr == NULL)
    {
        //обработка ошибки
        return 1;
    }
    dtr[0] = '\0';
    char* fli = "djid";  
    overprintf("Examples of how the my_printf works:\n for int: %d\n for unsigned int: %u\n for char: %c\n for string: %s\n for octal: %o\n for hexademical: %x\n for Hexademical: %X", 10, 20, 'A', "Hello", 10, 15, 15);
    overprintf(" for float: %f\n for double : %lf", (float)12.11, -5.564);
    oversprintf(&dtr, "%s", fli); 
    overprintf("%s", dtr);  
    overprintf(" for Roman:%Ro, %Ro\n for the Zenkendorf representation: %d - %Zr, %d - %Zr", 999, 123, 10, 10, 289, 289);
    overprintf(" for number to base: %Cv, %Cv\n for Number to base: %CV, %CV\n for decimal representation: %to\n for decimal representation: %TO", 15, 30, 134, 16, 15, 30, 134, 16, "abf", 17, "ABF", 17);
    overprintf(" for int in memory: %mi\n for unsigned int in memory: %mu\n for double in memory: %md, %md\n for float in memory: %mf, %mf", -546, 546, -0.342, 345.78, (float)1.2, (float)21.3);

    // Демонстрация overprintf
    overprintf("This is a test of overprintf: %d, %s", 123, "hello");

    // Демонстрация overfprintf
    FILE* test_file = fopen("test.txt", "w");
    if (test_file != NULL) {
        overfprintf(test_file, "This is a test of overfprintf: %f, %c", 3.14, 'X');
        fclose(test_file);
        printf("Check 'test.txt' for output of overfprintf.\n");
    }
    else {
        printf("Error creating 'test.txt'\n");
    }


    // Демонстрация oversprintf
    char* buffer = (char*)malloc(sizeof(char) * 50);
    if (buffer == NULL) {
        return 1;
    }
    buffer[0] = '\0';

    int chars_written = oversprintf(&buffer, "This is a test of oversprintf: %d, %s", 456, "world");
    if (chars_written != -1) {
        printf("Output of oversprintf: %s, chars_written: %d\n", buffer, chars_written);
    }
    else {
        printf("Error with oversprintf\n");
    }


    free(dtr);
    free(buffer);
    return 0;
}

char* int_to_str(int num) {
    char* str = (char*)malloc(20 * sizeof(char));
    if (str == NULL) return NULL;

    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    int i = 0;
    do {
        int digit = num % 10;
        str[i++] = digit + '0';
        num /= 10;
    } while (num != 0);

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}
char* unsigned_int_to_str(unsigned int num)
{
    char* str = (char*)malloc(20 * sizeof(char));
    if (str == NULL) return NULL;

    int i = 0;
    do {
        int digit = num % 10;
        str[i++] = digit + '0';
        num /= 10;
    } while (num != 0);

    str[i] = '\0';

    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
    return str;
}
char* float_to_str(float num) {
    size_t size = 16;
    char* str = (char*)malloc(size);
    if (str == NULL) return (char*)OSHIBKA;

    int negative = 0;
    int int_part = (int)num;
    float float_part = num - int_part;

    if (int_part < 0) {
        negative = 1;
        int_part = -int_part;
        float_part = -float_part;
    }
    // Выделяем память под целую часть
    int int_len = (int)ceil(log10(fabs(int_part) + 1));
    if (int_part == 0) {
        int_len = 1;
    }
    char* int_our = (char*)malloc(sizeof(char) * (int_len + 1));
    if (int_our == NULL) {
        free(str);
        return (char*)OSHIBKA;
    }
    int_our[int_len] = '\0';


    int i = 0;
    if (int_part == 0) {
        int_our[i++] = '0';
    }
    else {
        while (int_part != 0) {
            int_our[i++] = (int_part % 10) + '0';
            int_part /= 10;
        }

    }
    for (int j = 0; j < i / 2; j++) {
        char temp = int_our[j];
        int_our[j] = int_our[i - 1 - j];
        int_our[i - 1 - j] = temp;
    }

    // Выделяем память под дробную часть.
    int float_len = 6;
    char* float_our = (char*)malloc(sizeof(char) * (float_len + 1));
    if (float_our == NULL) {
        free(str);
        free(int_our);
        return (char*)OSHIBKA;
    }
    float_our[float_len] = '\0';


    int k = 0;
    while (k < float_len) {
        float_part *= 10;
        int digit = (int)float_part;
        float_our[k++] = digit + '0';
        float_part -= digit;
        if (fabs(float_part) < 1e-6) {
            break;
        }

    }
    float_our[k] = '\0';

    size_t nado = strlen(int_our) + strlen(float_our) + 2 + (negative ? 1 : 0);
    if (strlen(float_our) == 0)
        nado--;

    if (size < nado) {
        char* buffer = (char*)realloc(str, nado);
        if (buffer == NULL) {
            free(str);
            free(int_our);
            free(float_our);
            return (char*)OSHIBKA;
        }
        str = buffer;
    }

    int b = 0;
    if (negative) {
        str[b++] = '-';
    }

    for (int j = 0; int_our[j] != '\0'; j++) {
        str[b++] = int_our[j];
    }

    if (strlen(float_our) > 0) {
        str[b++] = '.';
        for (int j = 0; float_our[j] != '\0'; j++) {
            str[b++] = float_our[j];
        }

    }


    str[b] = '\0';

    free(int_our);
    free(float_our);

    return str;
}
char* double_to_str(double num)
{
    size_t size = 256;
    char* str = (char*)malloc(size);
    if (str == NULL) return NULL;

    char* int_our = (char*)malloc(sizeof(char) * 192); // массив под целую часть
    char* float_our = (char*)malloc(sizeof(char) * 57); // массив под дробную часть

    if (int_our == NULL || float_our == NULL) {
        free(str);
        return (char*)OSHIBKA;
    }

    int negative = 0;
    int int_part = (int)num;
    float float_part = num - int_part;

    if (int_part < 0) {
        negative = 1;
        int_part = -int_part;
        float_part = -float_part;
    }

    int i = 0;
    if (int_part == 0) {
        int_our[i++] = '0';
    }
    else {
        while (int_part != 0) {
            int_our[i++] = (int_part % 10) + '0';
            int_part /= 10;
        }
        int_our[i] = '\0';
    }

    for (int j = 0; j < i / 2; j++) {
        char temp = int_our[j];
        int_our[j] = int_our[i - 1 - j];
        int_our[i - 1 - j] = temp;
    }

    int k = 0;
    while (k < 6) {
        float_part *= 10;
        int digit = (int)float_part;
        float_our[k++] = digit + '0';
        float_part -= digit;
    }
    float_our[k] = '\0';

    size_t nado = i + k + 3 + (negative ? 1 : 0); // +3 для точки, знака и \0
    if (size < nado) {
        char* buffer = (char*)realloc(str, nado);
        if (buffer == NULL) {
            free(str);
            free(int_our);
            free(float_our);
            return (char*)OSHIBKA;
        }
        str = buffer;
    }

    int b = 0;
    if (negative) {
        str[b++] = '-';
    }

    for (int j = 0; j < i; j++) {
        str[b++] = int_our[j];
    }

    str[b++] = '.';

    for (int j = 0; j < k; j++) {
        str[b++] = float_our[j];
    }

    str[b] = '\0';
    free(int_our);
    free(float_our);

    return str;
}

char* num_to_base(int num, int base) {
    char* str = (char*)malloc(sizeof(char) * 25);
    if (str == NULL) return OSHIBKA;
    int i = 0;
    if (base == 8) {
        while (num > 0) {
            str[i++] = (num % 8) + '0';
            num /= 8;
        }
        str[i] = '\0';
        int st = 0;
        int end = i - 1;
        while (st < end) {
            char temp = str[st];
            str[st] = str[end];
            str[end] = temp;
            st++;
            end--;
        }
    }

    if (base == 16 || base == 160) {
        if (base == 16) {
            char alphabet1[] = "0123456789abcdef";
            while (num > 0) {
                str[i++] = alphabet1[num % 16];
                num /= 16;
            } str[i] = '\0';
        }
        else {
            char alphabet2[] = "0123456789ABCDEF";
            while (num > 0) {
                str[i++] = alphabet2[num % 16];
                num /= 16;
            } str[i] = '\0';
        }

        int st = 0;
        int end = i - 1;
        while (st < end) {
            char temp = str[st];
            str[st] = str[end];
            str[end] = temp;
            st++;
            end--;
        }
    }
    return str;
}

char* Roman(int num) {
    char* roman[] = { "I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M" };
    int values[] = { 1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000 };


    char* str = (char*)malloc(sizeof(char) * 20);
    if (str == NULL) return OSHIBKA;

    int j = 0;
    for (int i = 12; i >= 0; i--) {
        while (num >= values[i]) {
            size_t len = strlen(roman[i]);
            strncpy(str + j, roman[i], len);
            j += len;
            num -= values[i];
        }
    }
    str[j] = '\0';
    return str;
}
char** Z(unsigned int num) {
    unsigned int fib[1024] = { 0 };
    fib[0] = 1;
    fib[2] = 1;
    int i = 2;
    while ((fib[i] + fib[i - 2]) <= num) {
        i += 2;
        fib[i] = fib[i - 4] + fib[i - 2];
    }
    unsigned int null_index = i + 1;
    unsigned int val_index = i;

    fib[null_index] = 1;
    int sum = fib[val_index];
    for (int ind = (val_index - 4); ind >= 0; ind -= 2) {
        if ((sum + fib[ind]) == num) {
            fib[ind + 1] = 1;
            break;
        }
        if (sum + fib[ind] < num) {
            sum += fib[ind];
            fib[ind + 1] = 1;
        }
    }

    char** result_str = (char**)malloc((null_index + 3) * sizeof(char*));//под массив указателей
    if (result_str == NULL) {
        return NULL;
    }

    for (int k = 0; k <= null_index; k++) {
        result_str[k + 1] = unsigned_int_to_str(fib[k]);

    }
    result_str[0] = unsigned_int_to_str(null_index);
    result_str[null_index + 2] = NULL;
    return result_str;
}

char* convert_base(int num, int base, char size) {
    char* buffer = (char*)malloc(65 * sizeof(char));  // Достаточно для 64 цифр + '\0'
    if (buffer == NULL) return OSHIBKA;
    char digitsS[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char digitsB[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i = 0;
    char* digits = NULL;
    switch (size)
    {
    case 'B':
        digits = digitsB;
        break;
    case 'S':
        digits = digitsS;
        break;
    default:
        free(buffer);
        return NULL;

    }
    int is_negative = 0;

    if (num < 0 && base == 10) {
        is_negative = 1;
        num = -num;
    }

    if (num == 0) {
        buffer[i++] = '0';
    }

    while (num > 0) {
        buffer[i++] = digits[num % base];
        num /= base;
    }

    if (is_negative) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
    return buffer;
}

char* str_to_base(char* str, int base) {
    if (str == NULL)
        return NULL;
    int result = 0;
    int power = 1;
    int pr_value = 0;
    int is_negative = 0;
    int ind = 0;
    int sch = strlen(str) - 1;

    if (str[0] == '-') {
        is_negative = 1;
        ind++;
    }

    while (sch >= ind) {
        if (isalpha(str[sch])) {
            pr_value = tolower(str[sch]) - 'a' + 10;
        }
        else if (isdigit(str[sch])) {
            pr_value = str[sch] - '0';
        }
        else {
            return OSHIBKA;
        }


        if (pr_value >= base) {
            return OSHIBKA;
        }


        result += power * pr_value;
        power *= base;
        sch--;
    }

    if (is_negative) {
        result = -result;
    }
    return int_to_str(result);

}
char* iu_to_dumb(unsigned int num, int type) {
    int max_bits = 0;
    if (num == 0) {
        max_bits = 1;
    }
    else {
        max_bits = (int)ceil(log2(num + 1));
    }

    int full_bytes = (max_bits + 7) / 8;
    int max = full_bytes * 8;


    char* result = (char*)calloc(max + 1, sizeof(char));
    if (result == NULL) return OSHIBKA;
    memset(result, '0', max); // Заполняем нулями


    if (num == 0 && type == 0) {
        result[max - 1] = '0';
        result[max] = '\0';
        return result;
    }
    else if (num == 0 && type == 1)
    {
        result[max - 1] = '0';
        for (int i = 0; i < max; i++) {
            result[i] = '1';
        }
        result[max] = '\0';
        return result;
    }

    if (num == 1 && type == 0) {
        result[max - 1] = '1';
        result[max] = '\0';
        return result;
    }

    if (num == 1 && type == 1) {
        for (int i = 0; i < max - 1; i++) {
            result[i] = '1';
        }
        result[max - 1] = '0';
        result[max] = '\0';
        return result;
    }


    int i = max - 1;
    while (num > 0) {
        result[i--] = (num % 2) + '0';
        num /= 2;
    }


    if (type == 1) {
        // Инвертируем биты
        for (i = 0; i < max; ++i) {
            result[i] = (result[i] == '0' ? '1' : '0');
        }
        // Добавляем единицу (имитация дополнительного кода)
        int carry = 1;
        for (i = max - 1; i >= 0; i--) {
            if (carry == 0) break;
            if (result[i] == '0') {
                result[i] = '1';
                carry = 0;
            }
            else {
                result[i] = '0';
            }
        }
    }
    result[max] = '\0';


    return result;
}
int number_len(const int number) {
    int len = 0;
    int t = number;
    if (number == 0)
        return 1;
    while (t > 0) {
        len++;
        t /= 10;
    }
    return len;
}
char* toBinary(unsigned long long n, int size) {
    char* binary = (char*)calloc(size + 1, sizeof(char));
    if (binary == NULL) {
        return NULL;
    }
    for (int i = size - 1; i >= 0; --i) {
        binary[i] = ((n >> i) & 1) ? '1' : '0';
    }
    binary[size] = '\0';
    return binary;
}
char* exponent(double num, char type) {
    uint64_t* num_ptr = (uint64_t*)&num;
    uint64_t exponent_bits;
    long long exponent_value;
    int size;

    if (type == 'd') {
        exponent_bits = (*num_ptr >> 52) & 0x7FF;
        exponent_value = (long long)exponent_bits - 1023;
        size = 11;
    }
    else {
        exponent_bits = (*num_ptr >> 23) & 0xFF;
        exponent_value = (long long)exponent_bits - 127;
        size = 8;
    }


    char* binary_exponent = toBinary((unsigned long long)abs(exponent_value), size);
    if (binary_exponent == NULL) return NULL;
    if (exponent_value < 0) {
        for (int i = 0; i < size; i++) {
            binary_exponent[i] = (binary_exponent[i] == '0' ? '1' : '0');
        }

        int carry = 1;
        for (int i = size - 1; i >= 0; i--) {
            if (carry == 0) break;

            if (binary_exponent[i] == '0') {
                binary_exponent[i] = '1';
                carry = 0;
            }
            else {
                binary_exponent[i] = '0';
            }
        }
    }


    return binary_exponent;
}

char* significand(double num, char type) {
    uint64_t* num_ptr = (uint64_t*)&num;
    uint64_t mantissa_bits;
    int size;

    if (type == 'd') {
        mantissa_bits = (*num_ptr) & 0xFFFFFFFFFFFFF;
        size = 52;
    }
    else {
        mantissa_bits = (*num_ptr) & 0x7FFFFF;
        size = 23;
    }

    char* binary_mantissa = toBinary(mantissa_bits, size);
    if (binary_mantissa == NULL) return NULL;

    return binary_mantissa;
}


void d(int num, Type target, void* format)
{
    char* num_str = int_to_str(num);
    if (num_str == NULL) {
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void u(unsigned int num, Type target, void* format)
{
    char* num_str = unsigned_int_to_str(num);
    if (num_str == NULL) {
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void f(float num, Type target, void* format) {
    char* num_str = float_to_str(num);
    if (num_str == OSHIBKA) {
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void lf(double num, Type target, void* format) {
    char* num_str = double_to_str(num);
    if (num_str == NULL) {
        free(num_str);
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void c(char c, Type target, void* format) {
    where_print_c(c, target, format);
}
void s(char* str, Type target, void* format) {
    where_print_s(str, target, format);
}
void o(int num, Type target, void* format) {
    char* num_str = num_to_base(num, 8);
    if (num_str == NULL) {
        free(num_str);
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void x(int num, Type target, void* format) {
    char* num_str = num_to_base(num, 16);
    if (num_str == NULL) {
        free(num_str);
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void X(int num, Type target, void* format) {
    char* num_str = num_to_base(num, 160);
    if (num_str == NULL) {
        free(num_str);
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void Ro(int num, Type target, void* format) {
    char* num_str = Roman(num);
    if (num_str == NULL) {
        free(num_str);
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void Zr(unsigned int num, Type target, void* format) {
    char** num_str = Z(num);
    if (num_str == NULL) {
        return;
    }
    int k = 1;
    while (num_str[k] != NULL) {

        where_print_s(num_str[k], target, format);
        where_print_c(' ', target, format);
        free(num_str[k]);
        k++;
    }
    free(num_str[0]);
    free(num_str);
}


// int Cv(int num, int base, enum target (file stream / string stream), void *stream (FILE * - for file, char ** - for string) 

void Cv(int num, int base, Type target, void* format) {

    if (base < 2 || base > 36) {
        base = 10;  // Если основание некорректное, используем десятичное
    }

    char* str = convert_base(num, base, 'S');
    where_print_s(str, target, format);
    free(str);
}
void CV(int num, int base, Type target, void* format) {
    if (base < 2 || base > 36) {
        base = 10;  // Если основание некорректное, используем десятичное
    }

    char* str = convert_base(num, base, 'B');
    if (str == NULL) return;
    where_print_s(str, target, format);
    free(str);
}
void To(char* str, int base, Type target, void* format) {
    char* num_str = str_to_base(str, base);
    if (num_str == NULL) {
        free(num_str);
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void mi(int num, Type target, void* format) {
    int type = 0;
    if (num < 0) {
        type = 1;
        num = -num;
    }
    char* num_str = iu_to_dumb(num, type);
    if (num_str == NULL) {
        printf("nonono");
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
void mu(unsigned int num, Type target, void* format) {
    char* num_str = iu_to_dumb(num, 0);
    if (num_str == NULL) {
        return;
    }
    where_print_s(num_str, target, format);
    free(num_str);
}
/*
    1. знак : 1 - , 0 +
    2. экспонента: n + m
    n - число, на которое нужно сместить до нормализованного представление
    m = 2^кол-во бит под экспоненту  - 1 (для f = 127, d = 1023)
    3. мантисса:
    */
void md(double num, Type target, void* format) {
    char sign = (num < 0) ? '1' : '0';
    char* exp = exponent(num, 'd');
    char* mn = significand(num, 'd');

    if (exp == NULL || mn == NULL) {
        if (exp)
            free(exp);
        if (mn)
            free(mn);
        return;
    }
    size_t exp_len = strlen(exp);
    size_t mn_len = strlen(mn);
    size_t total_size = exp_len + mn_len + 4; // знак + пробелы + завершающий ноль

    char* result = (char*)malloc(total_size);
    if (result == NULL) {
        free(exp);
        free(mn);
        return;
    }

    result[0] = sign;
    result[1] = ' ';
    size_t i = 2;
    size_t j = 0;
    while (j < exp_len && i < total_size)
    {
        result[i] = exp[j];
        i++;
        j++;
    }
    if (i == total_size)
    {
        free(exp);
        free(mn);
        free(result);
        return;
    }
    result[i] = ' ';
    i++;
    j = 0;
    while (j < mn_len && i < total_size)
    {
        result[i] = mn[j];
        i++;
        j++;
    }
    if (i == total_size)
    {
        free(exp);
        free(mn);
        free(result);
        return;
    }
    result[i] = '\0';

    where_print_s(result, target, format);

    free(exp);
    free(mn);
    free(result);
}

void mf(float num, Type target, void* format) {
    char sign = (num < 0) ? '1' : '0';
    char* exp = exponent((double)num, 'f');
    char* mn = significand((double)num, 'f');

    if (exp == NULL || mn == NULL) {
        if (exp)
            free(exp);
        if (mn)
            free(mn);
        return;
    }
    size_t exp_len = strlen(exp);
    size_t mn_len = strlen(mn);
    size_t total_size = exp_len + mn_len + 4;

    char* result = (char*)malloc(total_size);
    if (result == NULL) {
        free(exp);
        free(mn);
        return;
    }

    result[0] = sign;
    result[1] = ' ';
    size_t i = 2;
    size_t j = 0;
    while (j < exp_len && i < total_size)
    {
        result[i] = exp[j];
        i++;
        j++;
    }
    if (i == total_size)
    {
        free(exp);
        free(mn);
        free(result);
        return;
    }
    result[i] = ' ';
    i++;
    j = 0;
    while (j < mn_len && i < total_size)
    {
        result[i] = mn[j];
        i++;
        j++;
    }
    if (i == total_size)
    {
        free(exp);
        free(mn);
        free(result);
        return;
    }
    result[i] = '\0';

    where_print_s(result, target, format);

    free(exp);
    free(mn);
    free(result);
}
