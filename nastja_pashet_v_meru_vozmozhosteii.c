/*WTF: 
1)макросы нормально приплести
2)избавиться от буфера и сразу выводить через fputs
3)функцию num_len скопировать
4)проверить работу функции Z(Zn)
5)для to и TO щдна функция To

*/

 

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define OSHIBKA "Ошибка выделения памяти"

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
char* doub_to_dumb(double num);
char* float_to_dumb(float num);
int number_len(const int number);



//буфер и буф индекс в основной, а изменяем в остальных
void d(int num);
void u(unsigned int num);
void f(float num);
void lf(double num);
void c(char c);
void s(char* str);
void o(int num);
void x(int num);
void X(int num);

void Ro(int num);
void Zr(unsigned int num); 
void Cv(int num, int base);  
void CV(int num, int base); 
void To(char* str, int base);
void mi(int num);
void mu(unsigned int num);
void md(char* buffer, double num, int buf_ind);
void mf(char* buffer, float num, int buf_ind);




void my_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            i++; // Переход к следующему символу после '%'
            switch (format[i]) {
            case 'd': {
                d;
                break;
            }
            case 'u': {
                u;
                break;
            }
            case 'f': {
                f;
                break;
            }
            case 'l': {
                if (format[i++] == 'f') {
                    lf;
                    i++;
                    break;
                }
            }
            case 'c': {
                c;
                break;
            }
            case 's': {
                s;
                break;
            }
            case 'o': {
                o;
                break;
            }
            case 'x': {
                x;
                break;
            }
            case 'X': {
                X;
                i++;
                break;
            }
            case 'R': {
                if (format[i++] == 'o') {
                    Ro;
                    i++;
                    break;
                }
            }
            case 'Z': {
                if (format[i++] == 'r') {
                    Zr;
                    i++;
                    break;
                }
            }
            case 'C': {
                if (format[i++] == 'v') {
                    Cv;
                    i++;
                    break;
                }
                else if (format[i++] == 'V') {
                    CV;
                    i++;
                    break;
                }
            }
            case 't': {
                if (format[i++] == 'o') {
                    To;
                    i++;
                    break;
                }
            }
            case 'T': {
                if (format[i++] == 'O') {
                    To;
                    i++;
                    break;
                }
            }
            case 'm': {
                if (format[i++] == 'i') {
                    mi;
                    i++;
                    break;
                }
                else if (format[i++] == 'u') {
                    mu;
                    i++;
                    break;
                }
                else if (format[i++] == 'd') {
                    md;
                    i++;
                    break;
                }
                else if (format[i++] == 'f') {
                    mf;
                    i++;
                    break;
                }
            }
            default:
                fputc(format[i], stdout); // Необработанный символ 
                break;
            }
        }
        else
            fputc(format[i], stdout); 
    }
}


int main() {
    
    return 0;
}






char* int_to_str(int num) 
{
    char* str = (char*)malloc(20 * sizeof(char));
    int is_negative = 0;
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    int i = 0;
    do {
        int digit = num % 10;
        str[i++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');  // Преобразуем цифры
        num /= 10;
    } while (num != 0);

    if (is_negative) {
        str[i++] = '-';  // Если число было отрицательным, добавляем минус
    }

    str[i] = '\0';  // Завершаем строку нулевым символом

    // Инвертируем строку
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
char* unsigned_int_to_str(unsigned int num)
{
    char* str = (char*)malloc(20 * sizeof(char));

    int i = 0;
    do {
        int digit = num % 10;
        str[i++] = digit + '0';
        num /= 10;
    } while (num != 0);

    
    str[i] = '\0';  // Завершаем строку нулевым символом

    // Инвертируем строку
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}
char* float_to_str(float num) {
    size_t size = 32; 
    char* str = (char*)malloc(size);
    if (str == NULL) return NULL;

    char* int_our = (char*)malloc(sizeof(char) * 16); // массив под целую часть 
    char* float_our = (char*)malloc(sizeof(char) * 16); // массив под дробную часть

    if (int_our == NULL || float_our == NULL) {
        free(str);
        return NULL;
    }

    int negative = 0;
    int int_part = (int)num;
    float float_part = num - int_part;

    // Обработка знака
    if (int_part < 0) {
        negative = 1;
        int_part = -int_part;
        float_part = -float_part; // Дробную часть тоже делаем положительной
    }

    // Обработка целой части
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

    // Инвертирование целой части
    for (int j = 0; j < i / 2; j++) {
        char temp = int_our[j];
        int_our[j] = int_our[i - 1 - j];
        int_our[i - 1 - j] = temp;
    }

    // Обработка дробной части
    int k = 0;
    while (k < 6) {  // Ограничиваем дробную часть 6 знаками
        float_part *= 10;
        int digit = (int)float_part;
        float_our[k++] = digit + '0';
        float_part -= digit;
    }
    float_our[k] = '\0';

    // Проверка на необходимость увеличения памяти
    size_t nado = i + k + 3 + (negative ? 1 : 0); // +3 для точки, знака и \0
    if (size < nado) {
        char* buffer = (char*)realloc(str, nado);
        if (buffer == NULL) {
            free(str);
            free(int_our);
            free(float_our);
            return OSHIBKA;
        }
        str = buffer;
    }

    // Заполняем строку результатом
    int b = 0;
    if (negative) {
        str[b++] = '-';
    }

    // Копируем целую часть
    for (int j = 0; j < i; j++) {
        str[b++] = int_our[j];
    }

    // Добавляем точку
    str[b++] = '.';

    // Копируем дробную часть
    for (int j = 0; j < k; j++) {
        str[b++] = float_our[j];
    }

    str[b] = '\0'; // Завершаем строку

    // Освобождаем память
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
        return NULL;
    }

    int negative = 0;
    int int_part = (int)num;
    float float_part = num - int_part;

    // Обработка знака
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

    // Проверка на необходимость увеличения памяти
    size_t nado = i + k + 3 + (negative ? 1 : 0); // +3 для точки, знака и \0
    if (size < nado) {
        char* buffer = (char*)realloc(str, nado);
        if (buffer == NULL) {
            free(str);
            free(int_our);
            free(float_our);
            return OSHIBKA;
        }
        str = buffer;
    }

    // Заполняем строку результатом
    int b = 0;
    if (negative) {
        str[b++] = '-';
    }

    // Копируем целую часть
    for (int j = 0; j < i; j++) {
        str[b++] = int_our[j];
    }

    // Добавляем точку
    str[b++] = '.';

    // Копируем дробную часть
    for (int j = 0; j < k; j++) {
        str[b++] = float_our[j];
    }

    str[b] = '\0'; // Завершаем строку

    // Освобождаем память
    free(int_our);
    free(float_our);

    return str;
}
char* num_to_base(int num, int base) {
    char* str = (char*)malloc(sizeof(char) * 25);
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
            } 
        }
        else {
            char alphabet2[] = "0123456789ABCDEF"; 
            while (num > 0) {
                str[i++] = alphabet2[num % 16]; 
                num /= 16;
            }
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
    return str;
}
char* Roman(int num) {
    char* roman[] = { "I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM" };
    int values[] = { 1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900 };

    char* str = (char*)malloc(sizeof(char) * 64);
    int j = 0;
    for (int i = 11; i >= 0; i--) {
        while (num >= values[i]) {
            strcpy(&str[j], roman[i]);
            j += strlen(roman[i]);
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


    char** result_str = (char**)malloc((null_index) * sizeof(char*) + 1); 
    if (result_str == NULL) {
        return;
    }

    int j = 1;
    for (int k = 0; k <= null_index; k++) {
        result_str[j] = unsigned_int_to_str(fib[k]); 
        j++; 
    }
    result_str[0] = unsigned_int_to_str(null_index); 
    return result_str;
}
char* convert_base(int num, int base, char size) { 
    char* buffer = (char*)malloc(65 * sizeof(char));  // Достаточно для 64 цифр + '\0' 
    char digitsS[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char digitsB[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; 
    int i = 0;
    char* digits = NULL; 
    switch (size)
    {
    case 'B':
        digits = digitsB; 
    case 'S':
        digits = digitsS;  
    }
    int is_negative = 0;
    
    if (buffer == NULL) {
        return OSHIBKA; 
    }

    if (num < 0 && base == 10) { //TODO: спросить у маши, почему только для 10
        is_negative = 1;
        num = -num; 
    }

    // Преобразуем число в строку
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

    // Переворачиваем строку
    int start = 0;
    int end = i - 1;
    while (start < end) {
        char temp = buffer[start];
        buffer[start] = buffer[end];
        buffer[end] = temp;
        start++;
        end--;
    }
}
char* str_to_base(char* str, int base) {
    int result;
    int power = 1;
    int pr_value = 0;
    int is_negative = 0;
    int ind = 0;
    int sch = strlen(str) - 1;
    int i = 0;

    if (str[0] == '-') {
        is_negative = 1;
        ind++;
    } 

    while (sch >= ind) {//
        if (isalpha(str[sch])) { 
            pr_value = tolower(str[sch]) - 'a' + 10;
        }
        if (isdigit(str[sch])) {
            pr_value = str[sch] - '0';
        }
        else
            return OSHIBKA;

        if (pr_value >= base)
            return OSHIBKA;
        result += power * pr_value;
        power *= base;
        sch--;
    }
    if (is_negative) {
        result = -result;
    }
    
    return int_to_str(result);
}
char* iu_to_dumb(unsigned int num, int type) {//1 - отрицательные
    if (num == 0 || num == 1) {
        char * result = "00000000";
        if (num == 1) {
            result[7] = '1';
        }
        return result;
    }
    int max_ind = floor(log2(num)); 
    int m = max_ind + 1;
    int max = (max_ind + 1) % 8 == 0 ? max_ind + m / 8 - 1 : max_ind + m % 8 + m / 8 ;  
    int izm_num = num; 

    char* result = (char*)calloc(max+2, sizeof(char)); 
    
    if (result == NULL)
        return OSHIBKA;

    for (int i = max; izm_num; i--) { 
        result[i] = izm_num % 2;
        izm_num /= 2;
        if ((i + 1) % 9 == 0 && i != max) {
            result[i] = ' ';
            i--;
        }
    }
    result[max + 1] = '\0';

    int max_position = -2; 

    if (type == 1) {  
        for (int i = max; i >= 0; i--) {
            if (result[i] == '0')
                result[i] = '1';
            else if (result[i] == '1'){
                result[i] = '0';
                max_position = max_position > i ? max_position : i; 
            }
        }
        if (max_position < 0) {
            char* ptr = (char*)calloc(max + 10, sizeof(char));
            if (ptr == NULL) {
                free(result);
                return OSHIBKA; 
            }
            free(result);
            ptr[7] = '1';
            return ptr;
        }
        else {
            for (int i = max; i > max_position; i--) {
                result[i] = '0';
            }
            result[max_position] = '1';
        }
    }
    return result;
}
char* doub_to_dumb(double num);
char* float_to_dumb(float num);
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



void d(int num)
{
    char* num_str =int_to_str(num); 
    if (num_str == NULL) {
        free(num_str); 
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void u(unsigned int num) 
{
    char* num_str = unsigned_int_to_str(num); 
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void f(float num) {
    char* num_str = float_to_str(num); 
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void lf(double num) {
    char* num_str = double_to_str(num);
    if (num_str == NULL) { 
        free(num_str); 
        return OSHIBKA; 
    }
    fputs(num_str, stdout); 
    free(num_str); 
}
void c(char c) {
    fputc(c, stdout);
}
void s(char* str) {
    fputs(str, stdout); 
}
void o(int num) {
    char* num_str = num_to_base(num, 8);
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void x(int num) {
    char* num_str = num_to_base(num, 16);
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void X(int num) {
    char* num_str = num_to_base(num, 160);
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void Ro(int num) {
    char* num_str = Roman(num);
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void Zr(unsigned int num) {
    char** num_str = Z(num); 
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    int k = 1;
    while (strcmp(num_str[0], unsigned_int_to_str(k)) >= 0) { 
        fputs(num_str[k], stdout);
        fputc(' ', stdout);
        k++;
    }
    free(num_str);
}
void Cv(int num, int base) {
      
    if (base < 2 || base > 36) {
        base = 10;  // Если основание некорректное, используем десятичное
    }
    
    char* str= convert_base(num, base, 'S'); 
    fputs(str, stdout);
    free(str); 
}
void CV(int num, int base) { 
    if (base < 2 || base > 36) {
        base = 10;  // Если основание некорректное, используем десятичное
    }

    char* str = convert_base(num, base, 'B');
    fputs(str, stdout);
    free(str); 
}
void To(char* str, int base) {
    char* num_str = str_to_base(str, base); 
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void mi(int num) {
    int type = 0;
    if (num < 0) {
        type = 1;
    }
    char* num_str = iu_to_dumb(num, type);
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void mu(unsigned int num) {
    char* num_str = iu_to_dumb(num, 0);
    if (num_str == NULL) {
        free(num_str);
        return OSHIBKA;
    }
    fputs(num_str, stdout);
    free(num_str);
}
void md(char* buffer, double num, int buf_ind);
void mf(char* buffer, float num, int buf_ind);
