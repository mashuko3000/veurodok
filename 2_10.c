#include <stdarg.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Прототипы функций
int overscanf(const char *format, ...);
int handle_int(const char **input, va_list args);
int handle_unsigned_int(const char **input, va_list args);
int handle_float(const char **input, va_list args);
int handle_long_float(const char **input, va_list args);
int handle_symbol(const char **input, va_list args);
int handle_string(const char **input, va_list args);
int handle_octal(const char **input, va_list args);
int handle_hex(const char **input, va_list args);
int handle_Hex(const char **input, va_list args);
int handle_roman(const char **input, va_list args);
int handle_zecendorf(const char **input, va_list args);
int handle_cv(const char **input, va_list args);
int handle_CV(const char **input, va_list args);

// Статусные функции
void on_success();
void on_error();
void on_special_case();

// Обработчики флагов
typedef int (*flag_handler_func)(const char **input, va_list args);

typedef struct {
    const char* flag;
    flag_handler_func handler;
} flag_handler;

flag_handler handlers[] = {
    {'d', handle_int},
    {'u', handle_unsigned_int},
    {'f', handle_float},
    {'lf', handle_long_float},
    {'c', handle_symbol},
    {'s', handle_string},
    {'o', handle_octal},
    {'x', handle_hex},
    {'X', handle_Hex},
    {'Ro', handle_roman},
    {'Zr', handle_zecendorf},
    {'Cv', handle_cv},
    {'CV', handle_CV},
};

// Статусные обработчики
typedef void (*status_handler_func)();

status_handler_func status_handlers[] = {
    on_success,      // Статус-код 0: Успех
    on_error,        // Статус-код -1: Ошибка
    on_special_case  // Другие специальные случаи
};

// Стандартные флаги (функции для парсинга)
int d(const char **input);
unsigned int u(const char **input);
float f(const char **input);
char *s(const char **input);

// Функции для обработки флагов
int handle_d(const char **input, va_list args) {
    int *iptr = va_arg(args, int*);
    *iptr = d(input);
    return 0;  // Успешная обработка
}

int handle_u(const char **input, va_list args) {
    unsigned int *uiptr = va_arg(args, unsigned int*);
    *uiptr = u(input);
    return 0;  // Успешная обработка
}

int handle_f(const char **input, va_list args) {
    float *fptr = va_arg(args, float*);
    *fptr = f(input);
    return 0;  // Успешная обработка
}

int handle_s(const char **input, va_list args) {
    char **strptr = va_arg(args, char**);
    *strptr = s(input);
    return 0;  // Успешная обработка
}

int handle_invalid(const char **input, va_list args) {
    return -1;  // Неверный флаг
}

// Статусные функции
void on_success() {
    printf("Флаг обработан успешно\n");
}

void on_error() {
    printf("Ошибка при обработке флага\n");
}

void on_special_case() {
    printf("Обработан специальный случай\n");
}

// Основная функция overscanf
int overscanf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    
    char input[100];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        va_end(args);
        return -1;
    }

    const char *ptr = format;
    const char *str_input = input;

    while (*ptr != '\0') {
        if (*ptr == '%') {
            ptr++;  // Пропускаем символ '%'
            int status = -1;  // По умолчанию ошибка

            // Ищем флаг в массиве
            for (int i = 0; i < sizeof(handlers) / sizeof(handlers[0]); i++) {
                if (handlers[i].flag == *ptr) {
                    status = handlers[i].handler(&str_input, args);  // Вызываем обработчик
                    break;
                }
            }

            // Вызов функции по статусу
            if (status == 0) {
                status_handlers[0]();  // Успех
            } else if (status == -1) {
                status_handlers[1]();  // Ошибка
            } else {
                status_handlers[2]();  // Специальный случай
            }
        } else {
            ptr++;  // Пропускаем обычные символы
        }
    }

    va_end(args);
    return 0;
}

// Реализация функций для стандартных флагов
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

char *s(const char **input) {
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


#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Универсальная функция для пропуска пробелов
void skip_spaces(const char **input) {
    while (isspace(**input)) {
        (*input)++;
    }
}

// Универсальная функция для чтения целых чисел (с знаком или без)
long read_integer(const char **input, int base, int is_signed) {
    long value = 0;
    int sign = 1;

    skip_spaces(input);

    // Обрабатываем знак
    if (is_signed && **input == '-') {
        sign = -1;
        (*input)++;
    } else if (**input == '+') {
        (*input)++;
    }

    // Читаем цифры
    while ((**input >= '0' && **input <= '9') || 
           (base == 16 && ((**input >= 'a' && **input <= 'f') || (**input >= 'A' && **input <= 'F')))) {
        char c = **input;
        if (isdigit(c)) {
            value = value * base + (c - '0');
        } else if (base == 16) {
            if (c >= 'a' && c <= 'f') {
                value = value * base + (c - 'a' + 10);
            } else if (c >= 'A' && c <= 'F') {
                value = value * base + (c - 'A' + 10);
            }
        }
        (*input)++;
    }

    return value * sign;
}

// Чтение знакового целого числа
int d(const char **input) {
    return (int)read_integer(input, 10, 1);
}

// Чтение беззнакового целого числа
unsigned int u(const char **input) {
    return (unsigned int)read_integer(input, 10, 0);
}

// Чтение восьмеричного числа
unsigned int o(const char **input) {
    return (unsigned int)read_integer(input, 8, 0);
}

// Чтение шестнадцатеричного числа (нижний регистр)
unsigned int x(const char **input) {
    return (unsigned int)read_integer(input, 16, 0);
}

// Чтение шестнадцатеричного числа (верхний регистр)
unsigned int X(const char **input) {
    return (unsigned int)read_integer(input, 16, 0);
}

// Чтение вещественного числа
float f(const char **input) {
    float value = 0;
    int divisor = 1;

    skip_spaces(input);

    // Чтение целой части
    while (isdigit(**input)) {
        value = value * 10 + (**input - '0');
        (*input)++;
    }

    // Чтение дробной части
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

// Чтение вещественного числа с двойной точностью
double lf(const char **input) {
    double value = 0;
    int divisor = 1;

    skip_spaces(input);

    // Чтение целой части
    while (isdigit(**input)) {
        value = value * 10 + (**input - '0');
        (*input)++;
    }

    // Чтение дробной части
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

// Чтение символа
char c(const char **input) {
    skip_spaces(input);
    char ch = **input;
    (*input)++;
    return ch;
}

// Чтение строки
char *s(const char **input) {
    skip_spaces(input);
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

// Чтение римских чисел
int Ro(const char **input) {
    skip_spaces(input);

    int result = 0;
    char c;

    char *roman[] = { "I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM" };
    int values[] = { 1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900 };
        
    while (**input != '\0'){

        for (size_t i = 0; i < 12; i++) {
            int current_value = 0;
            int next_value = 0;

            // Находим значение текущего символа
            for (int j = 0; j < 12; j++) {
                size_t roman_len = strlen(roman[j]);
                if (strncmp(&input[i], roman[j], roman_len) == 0) {
                    current_value = values[j];
                    break;
                }
            }

            // Находим значение следующего символа (если он есть)
            if (i + 1 < len) {
                for (int j = 0; j < 12; j++) {
                    size_t roman_len = strlen(roman[j]);
                    if (strncmp(&input[i + 1], roman[j], roman_len) == 0) {
                        next_value = values[j];
                        break;
                    }
                }
            }

            // Если текущее число меньше следующего, вычитаем его из результата
            if (current_value < next_value) {
                result -= current_value;
            } else {
                result += current_value;
            }
            (*input)++;
        }

    return result;
    }
    
}

// Чтение числа в системе счисления с произвольной базой
int Cv(const char **input, int base) {
    return (int)read_integer(input, base, 1);
}

// Чтение числа в системе счисления с верхними буквами
int CV(const char **input, int base) {
    return (int)read_integer(input, base, 1);
}


// Пример использования overscanf
int main() {
    int a;
    unsigned int b;
    float c;
    char *s_value;

    printf("Введите целое число (d): ");
    overscanf("%d", &a);
    printf("Целое число: %d\n", a);

    printf("Введите беззнаковое число (u): ");
    overscanf("%u", &b);
    printf("Беззнаковое число: %u\n", b);

    printf("Введите число с плавающей точкой (f): ");
    overscanf("%f", &c);
    printf("Число с плавающей точкой: %.2f\n", c);

    printf("Введите строку (s): ");
    overscanf("%s", &s_value);
    printf("Строка: %s\n", s_value);
    free(s_value);

    return 0;
}
