#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define PTR_ERROR -1
#define OK 0
#define INVALID_INPUT 3
#define MEMORY_ERROR -2
#define INITIAL_CAPACITY 10

int towers_construction(int blocks_count, int ***result_towers, size_t *result_towers_count, bool allowed_partial_blocks_usage, bool allowed_adjacent_layers_blocks_equal_count);
void find_towers(int blocks_count, int *current_tower, int current_size, int ***towers, size_t *count, size_t *capacity, bool allowed_partial_blocks_usage, bool allowed_adjacent_layers_blocks_equal_count);

int main() {
    int result = 0;
    int **result_towers = NULL;
    size_t result_towers_count = 0, i, j;
    bool allowed_partial_blocks_usage = true; 
    bool allowed_adjacent_layers_blocks_equal_count = true;

    int blocks_start = allowed_partial_blocks_usage ? 6 : 6;
    int blocks_end = allowed_partial_blocks_usage ? 1 : 6;
    
    for (int blocks = blocks_start; blocks >= blocks_end; blocks--) {
        result_towers_count = 0;
        result = towers_construction(blocks, &result_towers, &result_towers_count, allowed_partial_blocks_usage, allowed_adjacent_layers_blocks_equal_count);

        if (result == OK) {
            printf("Конфигурации башен для %d кубиков:\n", blocks);
            for (i = 0; i < result_towers_count; i++) {
                if (result_towers[i] != NULL) {
                    printf("Конфигурация %zu: ", i + 1);
                    for (j = 1; j <= result_towers[i][0]; j++) {
                        printf("%d ", result_towers[i][j]);
                    }
                    printf("\n");
                    free(result_towers[i]);
                }
            }
            free(result_towers);
        } else {
            printf("Произошла ошибка с кодом: %d\n", result);
        }
    }

    return 0;
}


void find_towers(int blocks_count, int *current_tower, int current_size, int ***towers, size_t *count, size_t *capacity, bool allowed_partial_blocks_usage, bool allowed_adjacent_layers_blocks_equal_count) {
  
    if (blocks_count == 0) {
      if (*count >= *capacity) {
          *capacity *= 2;
          int **temp = (int**)realloc(*towers, *capacity * sizeof(int*));
          if (temp == NULL) {
              return; 
          }
          *towers = temp;
      }
        (*towers)[*count] = (int *)malloc(sizeof(int) * (current_size + 1));
        if ((*towers)[*count] == NULL) {
            return;
        }
        (*towers)[*count][0] = current_size;
        for (int i = 0; i < current_size; i++) {
            (*towers)[*count][i + 1] = current_tower[i];
        }
        (*count)++;
        return;
    }

    int start = (current_size == 0) ? 1 : (allowed_adjacent_layers_blocks_equal_count ? 1 : current_tower[current_size - 1] + 1);
    for (int j = start; j <= blocks_count; j++) {
      if(!allowed_adjacent_layers_blocks_equal_count && current_size > 0 && j == current_tower[current_size - 1]){
        continue;
      }
        current_tower[current_size] = j;
        find_towers(blocks_count - j, current_tower, current_size + 1, towers, count, capacity, allowed_partial_blocks_usage, allowed_adjacent_layers_blocks_equal_count);
    }
}

int towers_construction(int blocks_count, int ***result_towers, size_t *result_towers_count, bool allowed_partial_blocks_usage, bool allowed_adjacent_layers_blocks_equal_count) {
    if (result_towers == NULL || result_towers_count == NULL) {
        return PTR_ERROR;
    }
    if (blocks_count <= 0) {
        return INVALID_INPUT;
    }

    *result_towers = NULL;
    *result_towers_count = 0;

    size_t capacity = INITIAL_CAPACITY;
    int **towers = (int **)malloc(capacity * sizeof(int *));
    if (towers == NULL) {
        return MEMORY_ERROR;
    }

    int *current_tower = (int *)malloc(blocks_count * sizeof(int));
    if (current_tower == NULL) {
        free(towers);
        return MEMORY_ERROR;
    }

    find_towers(blocks_count, current_tower, 0, &towers, result_towers_count, &capacity, allowed_partial_blocks_usage, allowed_adjacent_layers_blocks_equal_count);

    free(current_tower);

    int **temp = (int **)realloc(towers, (*result_towers_count) * sizeof(int *));
    if (temp == NULL) {
        for(size_t i = 0; i < *result_towers_count; i++){
            free(towers[i]);
        }
        free(towers);
        return MEMORY_ERROR;
    }
    *result_towers = temp;

    return OK;
}
