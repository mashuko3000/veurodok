#include<stdio.h>
#include<stdarg.h>

// base основание степени, которое мы будем возводить
// exponent - степень, в которую возводим base
double my_pow(double base, int exponent){
    if (exponent == 0){
        return 1.0;
    }
    double result = 1.0;
    for (int i=0; i<exponent; i++)
    {
        result *= base;
    }
    return result;
}

double polynomial(double x, int degree, ...)
// double - значение многочлена в заданной точке
// x-точка, в которой будет вычисляться значение многочлена
// degree степень многочлена
{
    va_list args; // Переменная для хранения списка аргументов
    va_start(args, degree); // Инициализация списка

    double result = 0.0; // итоговое значение многочлена

    for (int i = degree; i>=0; i--)
    // функция пройдёт от старшей степени degree до 0, i - текущая степень многочлена
    {
        double index = va_arg(args, double);
        result += index * my_pow(x, i);
        // Добавляем к результату текущий член многочлена, (возводим x в степень i)
    }
    va_end(args);
    return result;
}

int main(){
    double x = 2.0; // знчение точки, в которой будет вычисляться многочлен
    int degree = 5; // степень многочлена, максимальная

    double result = polynomial(x, degree, 1.98, -6.542, 98.3, 26.54, 67.0, 76.8);
    printf("The value of the polynomail at the point x = %.6f: %.6f\n", x, result);
    return 0;
}