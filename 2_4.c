#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

// Функция поиска подстроки в строке
int find_substring(const char *str, const char *substr) {
    if (str == NULL || substr == NULL) {
        return -1; // Возвращаем -1, если str или substr равны NULL
    }

    int i = 0;
    while (str[i] != '\0') {
        int j = 0;
        // Ищем вхождение подстроки
        while (str[i + j] == substr[j] && substr[j] != '\0') {
            j++;
        }

        // Если нашли полное вхождение подстроки
        if (substr[j] == '\0') {
            return i;  // Возвращаем индекс начала вхождения подстроки
        }
        i++;  // Идем дальше по строке
    }

    return -1;  // Подстрока не найдена
}

// Функция для поиска подстроки в файле
void search_in_file(const char *filename, const char *substring) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Ошибка при открытии файла: %s\n", filename);
        return;
    }

    char str[BUFSIZ];
    int counter_str = 1;
    while (fgets(str, sizeof(str), file)) {
        int index = 0;
        while ((index = find_substring(str + index, substring)) != -1) {
            // index + 1 - для того чтобы начать с позиции 1 (не с 0)
            printf("File: %s, String: %d, Position: %d\n", filename, counter_str, index + 1);
            index++;  // Продолжаем поиск с позиции после найденной подстроки
        }
        counter_str++;
    }

    fclose(file);
}

// Функция с переменным числом аргументов
void search_in_files(const char *substring, int num_files, ...) {
    va_list files;
    va_start(files, num_files);

    for (int i = 0; i < num_files; i++) {
        const char *filename = va_arg(files, const char*);
        search_in_file(filename, substring);
    }

    va_end(files);
}

int main() {
    // Пример использования: ищем подстроку "035veakideash" в трёх файлах
    search_in_files("035veakideash", 3, "dityo1.txt", "dityo2.txt", "dityo3.txt");
    return 0;
}