#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define FREE_MEMORY 1
#define CLOSE_FILE 2


int release_resources(void *first_resource, ...) {
    va_list args;
    void *resource = first_resource;
    int action;

    va_start(args, first_resource);

    while (resource != NULL) {
        action = va_arg(args, int);  

        switch (action) {
            case FREE_MEMORY:
                free(resource);
                break;
            case CLOSE_FILE:
                fclose((FILE *)resource);
                break;
            default:
                va_end(args);
                return -1;  // Возвращаем -1 при неизвестном действии
        }

        resource = va_arg(args, void *);  
    }

    va_end(args);
    return 0;  // Возвращаем 0 при успешном завершении
}


int main() {
    int *dynamic_memory = (int *)malloc(sizeof(int) * 10);
    if (!dynamic_memory) {
        return 1;  // Ошибка выделения памяти
    }

    FILE *file = fopen("example.txt", "w");
    if (!file) {
        free(dynamic_memory);
        return 1;  // Ошибка открытия файла
    }

    int result = release_resources(dynamic_memory, FREE_MEMORY, file, CLOSE_FILE, NULL);
    if (result == -1) {
        return 1;  // Ошибка при освобождении ресурсов
    }

    return 0;
}
