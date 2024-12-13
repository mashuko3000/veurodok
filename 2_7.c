#include <stdio.h> 
#include <stdarg.h> 
#include <stdlib.h> 
#include <string.h> 

#define YESS 1  
#define OH_NO 0 

int is_Kaprecar(long long x) { 
    long long square = x * x; 
    char square_num[BUFSIZ]; 
    int len;

    sprintf(square_num, "%lld", square); 

    len = 0; 
    while (square_num[len] != '\0') { 
        len++; 
    } 

    for (int i = 0; i < len; i++) {  
        char left_part[i + 1];
        strncpy(left_part, square_num, i);
        left_part[i] = '\0'; 

        char *right_part = square_num + i;

        long long left_num = strtoll(left_part, NULL, 10);
        long long right_num = strtoll(right_part, NULL, 10);

        if (left_num + right_num == x) { 
            return YESS; 
        } 
    } 

    return OH_NO; 
} 

void number_of_Kaprecar(int count, int base, ...) { 
    va_list ptr; 
    va_start(ptr, base); 

    for (int i = 0; i < count; i++) { 
        const char* num_str = va_arg(ptr, const char*);  
        long long number = strtoll(num_str, NULL, base);  

        if (is_Kaprecar(number)) { 
            printf("%s is a Kaprekar number\n", num_str); 
        } else { 
            printf("%s is not a Kaprekar number\n", num_str); 
        } 
    } 

    va_end(ptr); 
} 

int main() { 
    number_of_Kaprecar(1, 10, "8"); 
    return 0; 
}
