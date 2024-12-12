
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void Roman(int num, char *str) {
    char *roman[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM"};
    int values[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900};
    
    int j = 0;
    for (int i = 11; i >= 0; i--) {
        while (num >= values[i]) {
            strcpy(&str[j], roman[i]);
            j += strlen(roman[i]);
            num -= values[i];
        }
    }
    str[j] = '\0';
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

void Z(unsigned int num, char* str) {
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

    int size_str = 1; 
    for (int k = 0; k <= null_index; k++) { 
        size_str += number_len(fib[k]); 
        if (k < null_index) size_str++; 
    }

    char* result_str = (char*)malloc((size_str) * sizeof(char));    
    if (result_str == NULL) { 
        return; 
    }

    int j = 0;
    for (int k = 0; k <= null_index; k++) { 
        j += sprintf(result_str + j, "%d", fib[k]); 
        if (k < null_index) result_str[j++] = ' ';
    }

    strcpy(str, result_str);
    free(result_str);
}

void i_to_base(unsigned int num, int base, char* str) {
    int i = 0;
    if (base == 8) {
        while(num > 0) {
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
        char alphabet[] = "0123456789abcdef";
        while (num > 0) {
            str[i++] = alphabet[num % 16];
            num /= 16;
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
}

void ftoa(float num, char* str) {
    int int_part = (int)num;
    float float_part = num - int_part;
    int afterpoint = 6;

    int i = 0;
    while (int_part > 0) {
        str[i++] = (int_part % 10) + '0';
        int_part /= 10;
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

    str[i++] = '.';
    
    for (int j = 0; j < afterpoint; j++) {
        float_part *= 10;
        int digit = (int)float_part;
        str[i++] = digit + '0';
        float_part -= digit;
    }
    str[i] = '\0';
}

void dtoa(double num, char* str) {
    int int_part = (int)num;
    double double_part = num - int_part;
    int afterpoint = 6;

    int i = 0;
    while (int_part > 0) {
        str[i++] = (int_part % 10) + '0';
        int_part /= 10;
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

    str[i++] = '.';
    
    for (int j = 0; j < afterpoint; j++) {
        double_part *= 10;
        int digit = (int)double_part;
        str[i++] = digit + '0';
        double_part -= digit;
    }
    str[i] = '\0';
}

void convert_base(int value, int base, char *buffer) {
    char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";  
    int i = 0;
    int is_negative = 0;

    if (value < 0 && base == 10) {
        is_negative = 1;
        value = -value;  
    }

    // Преобразуем число в строку
    if (value == 0) {
        buffer[i++] = '0';
    }

    while (value > 0) {
        buffer[i++] = digits[value % base];
        value /= base;
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

void handle_Cv(va_list args) {
    int value = va_arg(args, int);  // Получаем число
    int base = va_arg(args, int);   // Получаем основание

    if (base < 2 || base > 36) {
        base = 10;  // Если основание некорректное, используем десятичное
    }

    // Динамически выделяем память для буфера
    char *buffer = (char *)malloc(65 * sizeof(char));  // Достаточно для 64 цифр + '\0'

    if (buffer == NULL) {
        // Если не удалось выделить память
        return;  // Выход
    }

    convert_base(value, base, buffer);
    free(buffer);
}

void convert_BASE(int value, int base, char *buffer) {
    char digits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";  
    int i = 0;
    int is_negative = 0;

    if (value < 0 && base == 10) {
        is_negative = 1;
        value = -value;  
    }

    // Преобразуем число в строку
    if (value == 0) {
        buffer[i++] = '0';
    }

    while (value > 0) {
        buffer[i++] = digits[value % base];
        value /= base;
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

void handle_CV(va_list args) {
    int value = va_arg(args, int);  // Получаем число
    int base = va_arg(args, int);   // Получаем основание

    if (base < 2 || base > 36) {
        base = 10;  // Если основание некорректное, используем десятичное
    }

    // Динамически выделяем память для буфера
    char *buffer = (char *)malloc(65 * sizeof(char));  // Достаточно для 64 цифр + '\0'

    if (buffer == NULL) {
        // Если не удалось выделить память
        return;  // Выход
    }

    convert_BASE(value, base, buffer);
    free(buffer);
}

void my_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char *buffer = (char*)malloc(1024*sizeof(char)); // Буфер для результата
    int buffer_size=sizeof(buffer);

    if (buffer == NULL) return;

    int buffer_index = 0;
    for (int i = 0; format[i] != '\0'; i++) {
        if (buffer_index==1022){
            buffer=(char*)realloc(buffer, buffer_size*2);
            buffer_size*=2;
        }
        if (format[i] == '%') 
        {
            i++; // Переход к следующему символу после '%'
            switch (format[i]) {
                case 'd': {
                    int num = va_arg(args, int);
                    char num_str[32]; // Достаточно для большинства int
                    itoa(num, num_str, 10); // Преобразование int в строку
                    strcpy(buffer + buffer_index, num_str);
                    buffer_index += strlen(num_str);
                    break;
                }
                case 'u': {
                    unsigned int num = va_arg(args, unsigned int);
                    char num_str[32];
                    itoa(num, num_str, 10);
                    strcpy(buffer + buffer_index, num_str);
                    buffer_index += strlen(num_str);
                    break;
                }
                case 'f': {
                    float f = va_arg(args, double);
                    char f_str[32];
                    ftoa(f, f_str);
                    strcpy(buffer + buffer_index, f_str);
                    buffer_index += strlen(f_str);
                    break;
                }
                case 'l': {
                    if (format[i++] == 'f') {
                        double lf = va_arg(args, double);
                        char lf_str[64];
                        dtoa(lf, lf_str);
                        strcpy(buffer + buffer_index, lf_str);
                        buffer_index += strlen(lf_str);
                    }
                    break;
                }
                case 'R': {  // Флаг для римских цифр
                    if (format[i + 1] == 'o') {
                        int num = va_arg(args, int);
                        char roman_str[32];
                        Roman(num, roman_str); // Обработка римских цифр
                        strcpy(buffer + buffer_index, roman_str);
                        buffer_index += strlen(roman_str);
                        i++; // Пропустить 'o'
                    }
                    break;
                }
                case 'Z': {  // Флаг для представления через числа Фибоначчи
                    if (format[i + 1] == 'r') {
                        unsigned int num = va_arg(args, unsigned int);
                        Z(num, buffer + buffer_index); // Функция для чисел Фибоначчи
                        buffer_index += strlen(buffer + buffer_index);
                        i++; // Пропустить 'r'
                    }
                    break;
                }
                case 'C':  
                    if (format[i + 1] == 'v') {

                        handle_Cv(args);  // Обрабатываем флаг %Cv
                        i += 2;  // Пропускаем 'v' и 'C'
                        break;  // Завершаем обработку флага %Cv
                    }
                    if (format[i + 1] == 'V') {
                        handle_CV(args);  // Обрабатываем флаг %CV
                        i += 2;  // Пропускаем 'V' и 'C'
                        break;  // Завершаем обработку флага %CV
                    }
                    break;
                case 'o': {
                    unsigned int o = va_arg(args, unsigned int);
                    char o_str[32];
                    i_to_base(o, 8, o_str); // Преобразование в восьмеричное основание
                    strcpy(buffer + buffer_index, o_str);
                    buffer_index += strlen(o_str);
                    break;
                }
                case 'x': {
                    unsigned int x = va_arg(args, unsigned int);
                    char x_str[32];
                    i_to_base(x, 160, x_str); // Преобразование в основание 160
                    strcpy(buffer + buffer_index, x_str);
                    buffer_index += strlen(x_str);
                    break;
                }
                case 'X': {
                    unsigned int x = va_arg(args, unsigned int);
                    char x_str[32];
                    i_to_base(x, 16, x_str); // Преобразование в шестнадцатеричное основание
                    strcpy(buffer + buffer_index, x_str);
                    buffer_index += strlen(x_str);
                    break;
                }
                default:
                    buffer[buffer_index++] = format[i]; // Необработанный символ
                    break;
            }
        } 
        else 
        {
            buffer[buffer_index++] = format[i]; // Обычный символ
        }
    }

    buffer[buffer_index] = '\0'; // Добавление завершающего нуля
    fputs(buffer, stdout);
    free(buffer);
}

int main() {
    // Пример использования всех флагов, чтобы проверить корректность работы функции my_printf.

    int num = 12345;
    unsigned int unum = 12345;
    float fnum = 123.456;
    double dnum = 789.123456;
    int roman_num = 1994; // Для римских цифр
    unsigned int fib_num = 22; // Для Zeckendorf представления
    char c = 'A';

    my_printf("Пример с флагами:\n");
    
    // Проверка чисел в различных системах счисления
    my_printf("Целое число (десятичное): %d\n", num);
    my_printf("Целое число (без знака): %u\n", unum);
    my_printf("Число с плавающей точкой (float): %f\n", fnum);
    my_printf("Число с плавающей точкой (double): %lf\n", dnum);

    // Проверка римских цифр
    my_printf("Римские цифры: %Ro \noctal: %o\n", roman_num, unum);
    
    // Проверка Fibonacci представления
    my_printf("Zeckendorf представление для %u: %Zr\n", fib_num, fib_num);
    
    // Проверка использования флагов Cv и CV
    my_printf("Флаг Cv: %Cv\n", num, 16);
    my_printf("Флаг CV: %CV\n", num, 16);

    // Пример вывода чисел в различных основаниях
    my_printf("Восьмеричное представление: %o\n", num);
    my_printf("Шестнадцатеричное представление: %x\n", num);
    my_printf("Основание 160: %X\n", num);

    return 0;
}