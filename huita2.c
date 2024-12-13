#include <stdio.h> 
#include <stdlib.h>

#define OSHIBKA "Ошибка выделения памяти"

char* float_to_str(float num) {
    // Инициализация строки достаточного размера
    size_t size = 32;  // Увеличиваем начальный размер для гарантии
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
    } else {
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

int main() {
    float num = -12345.6789f;
    char* result = float_to_str(num);
    if (result) {
        printf("Float as string: %s\n", result);
        free(result);  // Освобождаем память после использования
    } else {
        printf("Ошибка преобразования числа.\n");
    }
    return 0;
}

