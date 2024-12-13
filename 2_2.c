
#include <stdio.h>
#include <stdlib.h>

int str_len(const char* string) {
    int len = 0;
    for (len; string[len] != '\0'; len++);
    return len;
}

char* reverse(const char* string) {
    int len = str_len(string);
    char* reverse_str = (char*)malloc((len + 1) * sizeof(char));

    if (reverse_str == NULL)
        return NULL;

    int k = len - 1;

    for (int i = 0; i < len; i++) {
        reverse_str[i] = string[k];
        k--;
    }
    reverse_str[len] = '\0';

    return reverse_str;
}

char* second_upper(const char* string) {
    int len = str_len(string);
    char* upper_string = (char*)malloc((len + 1) * sizeof(char));
    if (upper_string == NULL) {
        return NULL; // Возвращаем NULL при ошибке
    }

    for (int i = 0; i < len; i++) {
        if (i % 2 == 1 && string[i] >= 'a' && string[i] <= 'z') {
            upper_string[i] = string[i] - 32;
        }
        else
            upper_string[i] = string[i];
    }
    upper_string[len] = '\0';

    return upper_string;
}

char* sort_string(const char* string) {
    int len = str_len(string);
    char* sort = (char*)malloc((len + 1) * sizeof(char));
    if (sort == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < len; i++) {
        if (string[i] >= '0' && string[i] <= '9') {
            sort[index] = string[i];
            index++;
        }
    }

    for (int i = 0; i < len; i++) {
        if (string[i] >= 'A' && string[i] <= 'Z' || string[i] >= 'a' && string[i] <= 'z') {
            sort[index] = string[i];
            index++;
        }
    }

    for (int i = 0; i < len; i++) {
        if (!(string[i] >= '0' && string[i] <= '9' || string[i] >= 'A' && string[i] <= 'Z' || string[i] >= 'a' && string[i] <= 'z')) {
            sort[index] = string[i];
            index++;
        }
    }
    sort[len] = '\0';
    return sort;
}

int* randomization(int seed, int count) {
    int num = count - 2;

    int* arr = (int*)malloc(num * sizeof(int));
    if (arr == NULL)
        return NULL;

    for (int i = 0; i < num; i++) {
        arr[i] = i + 1;
    }

    for (int i = num - 1; i > 0; i--) {
        int j = (seed + i) % (i + 1); // Генерируем случайный индекс от 0 до i

        // Меняем местами элементы arr[i] и arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    return arr;
}

char* concatenate(char* string, char* string_new) {
    int len1 = str_len(string);
    int len2 = str_len(string_new);

    char* temp_string = (char*)realloc(string, (len1 + len2) * sizeof(char));
    if (temp_string == NULL) {
        free(string);
        free(string_new);
        return NULL;
    }
    string = temp_string;

    int index = 0;
    for (int i = len1; i < len1 + len2; i++) {
        string[i] = string_new[index++];
    }

    string[len1 + len2] = '\0';
    return string;
}

int main(int argc, char* argv[]) {
    if (argc < 3)
        return 8;

    int* random_int = NULL;

    switch (argv[1][1]) {
        case 'l':
            printf("Length of the string is: %d\n", str_len(argv[2]));
            break;
        case 'r':
            printf("Reversed string is: %s\n", reverse(argv[2]));
            break;
        case 'u':
            printf("String with uppercase odd positions is %s\n", second_upper(argv[2]));
            break;
        case 'n':
            printf("Sorted string : %s\n", sort_string(argv[2]));
            break;
        case 'c':
            // Проверяем, есть ли достаточно аргументов
            if (argc < 4) {
                printf("Недостаточно аргументов для конкатенации.\n");
                return 9;
            }

            random_int = randomization(atoi(argv[2]), argc - 2);

            if (random_int == NULL) {
                printf("Ошибка выделения памяти.\n");
                return 7;
            }


            // Проходим по случайным индексам и конкатенируем строки
            char* result_string = argv[3]; // Начинаем с третьего аргумента (argv[2] - это seed)
            for (int i = 0; i < argc - 3; i++) {
                if (random_int[i] < argc - 2) {
                    result_string = concatenate(result_string, argv[random_int[i] + 3]);
                    if (result_string == NULL) {
                        printf("Ошибка конкатенации.\n");
                        free(random_int);
                        return 6;
                    }
                }
            }
            printf("Concatenated string: %s\n", result_string);

            // Освобождаем память после завершения
            free(random_int);
            break;
        default:
            printf("Неверный второй символ первого аргумента.\n");
            return 2;
    }

    return 0;
}
