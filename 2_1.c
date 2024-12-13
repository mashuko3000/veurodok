#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define NOT_A_VALUE 0
#define OK 1


void to_base_r(unsigned int num, unsigned int r) {
    
    unsigned int base = 1 << r;  
    unsigned int mask = base - 1; 
    unsigned int result[32];  
    int index = 0;

    printf("Число %u в системе с основанием 2^%u: ", num, r);

    if (num == 0) {
        printf("0\n");
        return;
    }

    while (num > 0) {
        unsigned int digit = num & mask; 
        result[index++] = digit;  
        num >>= r;  
    }

    
    for (int i = index - 1; i >= 0; i--) {
        if (result[i] < 10) {
            printf("%c", result[i] + '0');
        } else {
            printf("%c", result[i] + 55);  // 55 = 'A' - 10
        }
    }
    printf("\n");
}

// Функция для проверки, является ли строка числом
int is_number(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return NOT_A_VALUE; // Не число
        }
        str++;
    }
    return OK; // Число
}

int main() {
    unsigned int num;
    unsigned int r;
    char input[100];

    // Запрашиваем число у пользователя с валидацией ввода
    while (1) {
        printf("Введите число, целое неотрицательное, которое будет переводиться в сс с основанием 2 в степени r: ");
        fgets(input, sizeof(input), stdin); // Считываем строку

        // Убираем символ новой строки, если он есть
        input[strcspn(input, "\n")] = 0;

        // Проверяем, является ли ввод числом
        if (is_number(input)) {
            num = atoi(input); // Преобразуем строку в число
            break; // Ввод корректен, выходим из цикла
        } else {
            printf("Ошибка: Ввод должен быть числом.\n");
        }
    }

    // Запрашиваем значение r с валидацией
    while (1) {
        printf("Введите значение r (1-5), степень числа, в которую будет возводиться 2, система основания ранее введенного числа: ");
        fgets(input, sizeof(input), stdin);

        // Убираем символ новой строки
        input[strcspn(input, "\n")] = 0;

        // Проверяем, является ли ввод числом и в пределах диапазона
        if (is_number(input)) {
            r = atoi(input);
            if (r >= 1 && r <= 5) {
                break; // Значение r корректно, выходим из цикла
            } else {
                printf("Ошибка: Значение r должно быть в пределах от 1 до 5.\n");
            }
        } else {
            printf("Ошибка: Ввод должен быть числом.\n");
        }
    }

    // Вызываем функцию для преобразования
    to_base_r(num, r);

    return 0;
}