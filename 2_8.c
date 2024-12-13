#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

// Функция для перевода символа в его числовое значение
int char_to_digit(char c, int base) {
    if (isdigit(c)) {
        return c - '0';
    } else if (isalpha(c)) {
        return tolower(c) - 'a' + 10;
    }
    return -1;  // Некорректный символ
}

// Функция для перевода числа из строки в десятичное представление
unsigned long long str_to_decimal(const char *num, int base) {
    unsigned long long result = 0;
    while (*num) {
        result = result * base + char_to_digit(*num, base);
        num++;
    }
    return result;
}

// Функция для перевода числа из десятичного представления в строку в указанной системе счисления
void decimal_to_str(unsigned long long num, int base, char *result) {
    const char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char temp[64];
    int index = 0;

    if (num == 0) {
        result[index++] = '0';
    } else {
        while (num > 0) {
            temp[index++] = digits[num % base];
            num /= base;
        }
        // Обратить строку
        for (int i = 0; i < index; i++) {
            result[i] = temp[index - i - 1];
        }
    }
    result[index] = '\0';
}

// Функция сложения двух чисел в заданной системе счисления
char* add_numbers(int base, const char *num1, const char *num2, char *result) {
    unsigned long long n1 = str_to_decimal(num1, base);
    unsigned long long n2 = str_to_decimal(num2, base);
    unsigned long long sum = n1 + n2;
    decimal_to_str(sum, base, result);
    return result;
}

// Основная функция для вычисления суммы всех чисел
char* sum_numbers(int base, int count, char *result, ...) {
    va_list args;
    va_start(args, result);

    // Сначала берем первое число
    char *current_num = va_arg(args, char*);
    strcpy(result, current_num);

    // Затем поочередно прибавляем остальные числа
    for (int i = 1; i < count; i++) {
        current_num = va_arg(args, char*);
        char temp_result[100];
        add_numbers(base, result, current_num, temp_result);
        strcpy(result, temp_result);
    }

    va_end(args);
    return result;
}

int main() {
    char result[100];

    // Пример с основанием 16 (шестнадцатеричная система счисления)
    sum_numbers(32, 3, result, "pdd", "ad", "3b");
    printf("Сумма чисел в шестнадцатеричной системе: %s\n", result);

    // Пример с основанием 10 (десятичная система счисления)
    sum_numbers(10, 4, result, "123", "456", "789", "101");
    printf("Сумма чисел в десятичной системе: %s\n", result);

    return 0;
}