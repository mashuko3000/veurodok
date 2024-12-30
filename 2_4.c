#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define OK 0
#define ERROR_EMPTY_SUBSTRING -1
#define ERROR_NOTHING_IS_FOUNDED -2
#define ERROR_OPENING_FILE 1
#define ERROR_MEMORY_ALLOCATION 2
#define ERROR_NULL_POINTER 3

// structure for storing match information
typedef struct {
    const char *file_path;
    int line_num;
    int position;
} Match;

// function prototypes
int find_substring(const char *line, const char *substring);
int process_files(const char *substring, int num_files, Match **matches, ...);

int main() {
    const char *substring = "text";
    Match *matches = NULL;
    int match_count = 0;

    int status = process_files(substring, 2, &matches, "file1.txt", "file2.txt");
    
    if (status == 0) {
        for (int i = 0; i < match_count; i++) {
            printf("File: %s, Line: %d, Position: %d\n", matches[i].file_path, matches[i].line_num, matches[i].position);
        }
        free(matches);
    } else {
        if (status == ERROR_EMPTY_SUBSTRING) {
            printf("error: invalid substring\n");
        } else if (status == ERROR_NOTHING_IS_FOUNDED) {
            printf("nothing was founded\n");
        } else if (status == ERROR_OPENING_FILE) {
            printf("error: failed to open file\n");
        } else if (status == ERROR_MEMORY_ALLOCATION) {
            printf("error: failed to allocate memory for result\n");
        } else {
            printf("unknown error: %d\n", status);
        }
    }

    return OK;
}

// function to find a substring in a line
int find_substring(const char *line, const char *substring) {
    const char *p = line;
    const char *q = substring;

    if (*q == '\0') return ERROR_EMPTY_SUBSTRING;

    while (*p != '\0') {
        if (*p == *q) {
            const char *start = p;
            while (*p != '\0' && *q != '\0' && *p == *q) {
                p++;
                q++;
            }
            if (*q == '\0') {
                return (start - line) + 1;
            }
            q = substring;
        }
        p++;
    }
    return ERROR_NOTHING_IS_FOUNDED -1;
}

// function for processing files
int process_files(const char *substring, int num_files, Match **matches, ...) {

    if (substring == NULL) {
        return ERROR_EMPTY_SUBSTRING;
    }
    if (matches == NULL) {
        // TODO
    }

    va_list args;
    va_start(args, matches);
    
    int match_count = 0;
    *matches = NULL;

    for (int i = 0; i < num_files; i++) {
        const char *file_path = va_arg(args, const char*);
        FILE *file = fopen(file_path, "r");
        
        if (!file) {
            va_end(args);
            free(*matches);
            return ERROR_OPENING_FILE;
        }

        char *line = NULL;  // pointer for the line
        size_t line_size = 0;  // size of allocated memory for the line
        int line_num = 1;
        
        // Replace getline with fgets
        while (fgets(line, line_size, file) != NULL) {
            int pos = find_substring(line, substring);
            while (pos != -1) {
                match_count++;
                Match *temp = realloc(*matches, match_count * sizeof(Match));
                if (temp == NULL) {
                    free(line);
                    fclose(file);
                    free(*matches);
                    *matches = NULL;
                    va_end(args);
                    return ERROR_MEMORY_ALLOCATION;
                }
                *matches = temp;

                (*matches)[match_count - 1].file_path = file_path;
                (*matches)[match_count - 1].line_num = line_num;
                (*matches)[match_count - 1].position = pos;

                pos = find_substring(line + pos, substring); // search for the next occurrence
            }
            line_num++;
        }
        
        free(line);
        fclose(file);
    }

    va_end(args);
    return OK;
}
