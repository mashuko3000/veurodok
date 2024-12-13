#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *int_to_str(int num);
char *float_to_str(float num); // получившуюся строчку копируем в буфер
char *double_to_str(double num);
char *str_to_dynamic_str(char *str);
char *num_to_base(int num, int i);
char *str_to_base(char*str, int num, int i);
char *num_to_dumb(int num);
char *unsig_to_dumb(unsigned int num);
char *doub_to_dumb(double num);
char *float_to_dumb(float num);



//буфер и буф индекс в основной, а изменяем в остальных
void d(char*buffer, int num, int buf_ind);
void u(char*buffer, unsigned int num, int buf_ind);
void f(char*buffer, float num, int buf_ind);
void lf(char*buffer, double num, int buf_ind);
void c(char*buffer, char c, int buf_ind);
void s(char*buffer, char*str, int buf_ind);
void o(char*buffer, int num, int buf_ind);
void x(char*buffer, int num, int buf_ind);
void X(char*buffer, int num, int buf_ind);

void Ro(char*buffer, int num, int buf_ind);
void Zr(char*buffer, unsigned int num, int buf_ind);
void Cv(char*buffer, int num, int buf_ind);
void CV(char*buffer, int num, int buf_ind);
void to(char*buffer, char*str, int buf_ind);
void TO(char*buffer, char*str, int buf_ind);
void mi(char*buffer, int num, int buf_ind);
void mu(char*buffer, unsigned int num, int buf_ind);
void md(char*buffer, double num, int buf_ind);
void mf(char*buffer, float num, int buf_ind);




void my_printf(const char *format, ...) 
{
    va_list args;
    va_start(args, format);

    const char *ptr = format;
}



char *int_to_str(int num)
{
    char*str=[12];
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
    return str;
}

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

char *double_to_str(double num);
char *str_to_dynamic_str(char *str);
char *num_to_base(int num, int i);
char *str_to_base(char*str, int num, int i);
char *num_to_dumb(int num);
char *unsig_to_dumb(unsigned int num);
char *doub_to_dumb(double num);
char *float_to_dumb(float num);



//буфер и буф индекс в основной, а изменяем в остальных
void d(char*buffer, int num, int buf_ind)
{   
    char*num_str=(char*)malloc(sizeof(char)*32);
    num_str=int_to_str(num);
    if ((strlen(num_str)+buf_ind+1)>=sizeof(buffer)){
        char*str_ptr=(char*)realloc(buffer, sizeof(buffer)*2);
        if (str_ptr==NULL){
            free(str_ptr);
            return OSHIBKA;
        }
        buffer=str_ptr;
    } // TODO скопировать настр в буфер и изменит бу инд
    strcpy(buffer + buffer_index, num_str);
    buffer_index += strlen(num_str);
}
void u(char*buffer, unsigned int num, int buf_ind);
void f(char*buffer, float num, int buf_ind);
void lf(char*buffer, double num, int buf_ind);
void c(char*buffer, char c, int buf_ind);
void s(char*buffer, char*str, int buf_ind);
void o(char*buffer, int num, int buf_ind);
void x(char*buffer, int num, int buf_ind);
void X(char*buffer, int num, int buf_ind);

void Ro(char*buffer, int num, int buf_ind);
void Zr(char*buffer, unsigned int num, int buf_ind);
void Cv(char*buffer, int num, int buf_ind);
void CV(char*buffer, int num, int buf_ind);
void to(char*buffer, char*str, int buf_ind);
void TO(char*buffer, char*str, int buf_ind);
void mi(char*buffer, int num, int buf_ind);
void mu(char*buffer, unsigned int num, int buf_ind);
void md(char*buffer, double num, int buf_ind);
void mf(char*buffer, float num, int buf_ind);