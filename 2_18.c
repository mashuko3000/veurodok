
#include <stdio.h>
#include <stdlib.h>
#include <string.h>  

#define SUCCESS 0
#define ERR_NULL_ITEMS 1
#define ERR_NULL_RESULT_COMBINATIONS 2
#define ERR_NULL_RESULT_COMBINATIONS_COUNT 3
#define ERR_NULL_EQUALITY_COMPARER 4
#define ERR_K_GREATER_THAN_ITEMS_COUNT 5
#define ERR_MEMORY_ALLOCATION 6
#define ERR_DUPLICATE_ELEMENTS 7


int default_equality_comparer(int const *a, int const *b) {
    return (*a - *b);
}

int generate_combinations(int *items, size_t items_count, size_t k,
                           size_t start, size_t depth, int *current_combination,
                           int ***result_combinations, size_t *result_combinations_count,
                           size_t *capacity, int (*equality_comparer)(int const *, int const *)) {
    size_t i, j;
    int status;


    if (depth == k) {
        for (i = 0; i < depth - 1; ++i) {
            for (j = i + 1; j < depth; ++j) {
                if (equality_comparer(current_combination + i, current_combination + j) == 0) {
                    return ERR_DUPLICATE_ELEMENTS;
                }
            }
        }

        if (*result_combinations_count >= *capacity) {
            *capacity *= 2;
            int** temp = (int **)realloc(*result_combinations, sizeof(int *) * (*capacity));
            if (temp == NULL) {
                
                for (i = 0; i < *result_combinations_count; ++i)
                {
                    free((*result_combinations)[i]);
                }
                free(*result_combinations);
                
                *result_combinations = NULL;
                *capacity = 0;
                return ERR_MEMORY_ALLOCATION;
            }
            *result_combinations = temp; 
        }

        int *new_combination = (int *)malloc(k * sizeof(int));
        if (new_combination == NULL) {
            //*result_combinations_count = ERR_MEMORY_ALLOCATION;
            for (i = 0; i < *result_combinations_count; ++i)
            {
                free((*result_combinations)[i]);
            }
            free(*result_combinations);
                
            *result_combinations = NULL;
            *capacity = 0;
            return ERR_MEMORY_ALLOCATION;
        }
        memcpy(new_combination, current_combination, k * sizeof(int));

        (*result_combinations)[*result_combinations_count] = new_combination;
        ++*result_combinations_count;
        return SUCCESS;
    }

    for (i = start; i < items_count; ++i) {
        current_combination[depth] = items[i];
        if ((status = generate_combinations(items, items_count, k, i + 1, depth + 1, current_combination, result_combinations, result_combinations_count, capacity, equality_comparer)) != SUCCESS)
        {
            return status;
        }
    }

    return SUCCESS;
}

int combinations(int *items, size_t items_count, int ***result_combinations,
                 size_t *result_combinations_count,
                 int (*equality_comparer)(int const *, int const *), size_t k) {

    int status;
    size_t i, j;

    if (items == NULL) return ERR_NULL_ITEMS;
    if (result_combinations == NULL) return ERR_NULL_RESULT_COMBINATIONS;
    if (result_combinations_count == NULL) return ERR_NULL_RESULT_COMBINATIONS_COUNT;
    if (equality_comparer == NULL) return ERR_NULL_EQUALITY_COMPARER;
    if (k > items_count) return ERR_K_GREATER_THAN_ITEMS_COUNT;

    for (i = 0; i < items_count - 1; ++i) {
        for (j = i + 1; j < items_count; ++j) {
            if (equality_comparer(&items[i], &items[j]) == 0) {
                return ERR_DUPLICATE_ELEMENTS;
            }
        }
    }

    size_t capacity = 50;
    *result_combinations = (int **)malloc(sizeof(int *) * capacity);
    if (*result_combinations == NULL) return ERR_MEMORY_ALLOCATION;

    *result_combinations_count = 0;

    int *current_combination = (int *)malloc(k * sizeof(int));
    if (current_combination == NULL) {
        free(*result_combinations);
        *result_combinations = NULL;
        *result_combinations_count = 0;
        return ERR_MEMORY_ALLOCATION;
    }

    if ((status = generate_combinations(items, items_count, k, 0, 0, current_combination, result_combinations, result_combinations_count, &capacity, equality_comparer)) != SUCCESS)
    {
        free(current_combination);
        for (i = 0; i < *result_combinations_count; ++i)
        {
            free((*result_combinations)[i]);
        }
        free(*result_combinations);
        *result_combinations = NULL;
        *result_combinations_count = 0;
        return status;
    }

    free(current_combination);
    return SUCCESS;
}

void free_combinations(int ***result_combinations, size_t *result_combinations_count) {
    for (size_t i = 0; i < *result_combinations_count; ++i) {
        free((*result_combinations)[i]);
    }
    free(*result_combinations);
    *result_combinations = NULL;
}

int main() {
    int items[] = {1, 2, 3, 4, 5, 6};
    size_t items_count = 6;
    int k = 3;
    int **result_combinations = NULL;
    size_t result_combinations_count = 0;


    int status = combinations(items, items_count, &result_combinations, &result_combinations_count, default_equality_comparer, k);

    if (status == SUCCESS) {

        printf("Combinations found: %zu\n", result_combinations_count);
        for (size_t i = 0; i < result_combinations_count; ++i) {
            for (size_t j = 0; j < k; ++j) {
                printf("%d ", result_combinations[i][j]);
            }
            printf("\n");
        }

        free_combinations(&result_combinations, &result_combinations_count);
    } else {
        printf("Error: %d\n", status);
    }

    return 0;
}