/*WTF: 
1)макросы нормально приплести
2)избавиться от буфера и сразу выводить через fputs
3)фришнуть в my_printf указатели 
4)функцию num_len скопировать
5)проверить работу функции Z(Zn)
*/



#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define OSHIBKA "Ошибка выделения памяти"

char* int_to_str(int num);
char* unsigned_int_to_str(unsigned int num);  
char* float_to_str(float num); 
char* double_to_str(double num);
char* str_to_dynamic_str(char* str); //что это вообще
char* num_to_base(int num, int i);
char* Roman(int num);
char* str_to_base(char* str, int num, int i);
char* num_to_dumb(int num);
char* unsig_to_dumb(unsigned int num);
char* doub_to_dumb(double num);
char* float_to_dumb(float num);



//буфер и буф индекс в основной, а изменяем в остальных
void d(int num);
void u(char* buffer, unsigned int num, int buf_ind);
void f(char* buffer, float num, int buf_ind);
void lf(char* buffer, double num, int buf_ind);
void c(char* buffer, char c, int buf_ind);
void s(char* buffer, char* str, int buf_ind);
void o(char* buffer, int num, int buf_ind);
void x(char* buffer, int num, int buf_ind);
void X(char* buffer, int num, int buf_ind);

void Ro(char* buffer, int num, int buf_ind);
void Zr(char* buffer, unsigned int num, int buf_ind);
void Cv(char* buffer, int num, int buf_ind);
void CV(char* buffer, int num, int buf_ind);
void to(char* buffer, char* str, int buf_ind);
void TO(char* buffer, char* str, int buf_ind);
void mi(char* buffer, int num, int buf_ind);
void mu(char* buffer, unsigned int num, int buf_ind);
void md(char* buffer, double num, int buf_ind);
void mf(char* buffer, float num, int buf_ind);




void my_printf(const char* format, ...)
{
    va_list args;
    va_start(args, format);

    const char* ptr = format;
}





int main() {
    float num = -12345.6789f;
    char* result = float_to_str(num);
    if (result) {
        printf("Float as string: %s\n", result);
        free(result);  // Освобождаем память после использования
    }
    else {
        printf("Ошибка преобразования числа.\n");
    }
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
char* str_to_dynamic_str(char* str);

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
char* str_to_base(char* str, int num, int i);
char* num_to_dumb(int num);
char* unsig_to_dumb(unsigned int num);
char* doub_to_dumb(double num);
char* float_to_dumb(float num);



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
void Cv(char* buffer, int num, int buf_ind);
void CV(char* buffer, int num, int buf_ind);
void to(char* buffer, char* str, int buf_ind);
void TO(char* buffer, char* str, int buf_ind);
void mi(char* buffer, int num, int buf_ind);
void mu(char* buffer, unsigned int num, int buf_ind);
void md(char* buffer, double num, int buf_ind);
void mf(char* buffer, float num, int buf_ind);
