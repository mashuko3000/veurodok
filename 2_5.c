#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

// Структура для представления координат точки
typedef struct {
    double x, y;
} Point;

// Функция для вычисления векторного произведения двух векторов AB и AC
double cross_product(const Point* A, const Point* B, const Point* C) {
    return (B->x - A->x) * (C->y - A->y) - (B->y - A->y) * (C->x - A->x);
}

// Проверка, пересекаются ли два отрезка AB и CD
int is_segments_intersect(const Point* A, const Point* B, const Point* C, const Point* D, double epsilon) {
    // Векторные произведения
    double cross1 = cross_product(A, B, C);
    double cross2 = cross_product(A, B, D);
    double cross3 = cross_product(C, D, A);
    double cross4 = cross_product(C, D, B);

    // Проверяем, лежат ли точки C и D по разные стороны от AB и наоборот
    return ((cross1 > 0 && cross2 < 0) || (cross1 < 0 && cross2 > 0)) &&
           ((cross3 > 0 && cross4 < 0) || (cross3 < 0 && cross4 > 0));
}

// Функция проверки на выпуклость многоугольника с переменным числом аргументов
int is_convex_polygon(double epsilon, int num_points, ...) {
    if (num_points < 3) {
        printf("Недостаточно точек для формирования многоугольника.\n");
        return 0;
    }

    // Считываем координаты из переменных аргументов
    va_list args;
    va_start(args, num_points);
    
    Point* points = (Point*)malloc(num_points * sizeof(Point));
    if (!points) {
        printf("Ошибка выделения памяти.\n");
        va_end(args);
        return 0;
    }

    for (int i = 0; i < num_points; i++) {
        points[i].x = va_arg(args, double);
        points[i].y = va_arg(args, double);
    }
    va_end(args);

    // Проверка на выпуклость с использованием векторного произведения
    int sign = 0;
    for (int i = 0; i < num_points; i++) {
        Point* A = &points[i];
        Point* B = &points[(i + 1) % num_points]; // Следующая точка
        Point* C = &points[(i + 2) % num_points]; // Точка через одну

        double cross = cross_product(A, B, C);

        if (fabs(cross) > epsilon) {
            if (sign == 0) {
                sign = (cross > 0) ? 1 : -1;
            } else if ((cross > 0 && sign < 0) || (cross < 0 && sign > 0)) {
                printf("Многоугольник невыпуклый.\n");
                free(points);
                return 0;
            }
        }
    }

    // Проверка на пересекающиеся отрезки
    int intersection_count = 0;
    for (int i = 0; i < num_points - 2; i++) {
        for (int j = i + 2; j < num_points; j++) {
            if (i == 0 && j == num_points - 1) continue;  // Пропускаем смежные ребра
            if (is_segments_intersect(&points[i], &points[i+1], &points[j], &points[(j+1) % num_points], epsilon)) {
                intersection_count++;
                if (intersection_count >= 2) {
                    printf("Многоугольник невыпуклый: пересекаются отрезки.\n");
                    free(points);
                    return 0;
                }
            }
        }
    }

    printf("Многоугольник выпуклый.\n");
    free(points);
    return 1;
}

int main() {
    int num_points;
    double epsilon = 1e-9;

    printf("Введите количество вершин многоугольника: ");
    if (scanf("%d", &num_points) != 1 || num_points < 3) {
        printf("Ошибка: недостаточно точек для формирования многоугольника.\n");
        return 1;
    }

    // Ввод координат вершин
    printf("Введите координаты вершин (x y) для каждой точки:\n");
    double* coords = (double*)malloc(num_points * 2 * sizeof(double));
    if (!coords) {
        printf("Ошибка выделения памяти.\n");
        return 1;
    }

    for (int i = 0; i < num_points; i++) {
        printf("Вершина %d: ", i + 1);
        if (scanf("%lf %lf", &coords[i*2], &coords[i*2 + 1]) != 2) {
            printf("Ошибка ввода координат.\n");
            free(coords);
            return 1;
        }
    }

    // Проверка многоугольника на выпуклость с переменным числом аргументов
    switch (is_convex_polygon(epsilon, num_points, coords[0], coords[1], coords[2], coords[3], coords[4], coords[5])) {
        case 0:
            printf("Невыпуклый многоугольник.\n");
            break;
        default:
            printf("Done\n");
    }
    free(coords);
}
