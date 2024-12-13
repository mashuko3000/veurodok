#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define OK 0
#define ERROR_COUNT_PROCESS 1 

int main(int argc, char *argv[]) {
    // Проверка аргументов командной строки
    if (argc != 2) {
        printf("Error! Input valid count of processes!\n");
        return ERROR_COUNT_PROCESS;
    }

    // Преобразование аргумента в целое число
    int num_processes = atoi(argv[1]);
    if (num_processes <= 0) {
        printf("Error! Invalid count of processes!\n");
        return ERROR_COUNT_PROCESS;
    }

    // Цикл для порождения процессов
    for (int i = 0; i < num_processes; i++) {
        int pid = fork();
        
        // Проверка на ошибку создания процесса
        if (pid < 0) {
            perror("Error during fork");
            return ERROR_COUNT_PROCESS;
        }
        
        // Дочерний процесс
        if (pid == 0) {
            printf("Hi! This is child process! PID: %d, FIO: Dulina Mariya Alekseevna\n", getpid());
            exit(OK);  // Завершаем дочерний процесс
        }
        
        // Родительский процесс ожидает завершения дочернего
        else {
            int status;
            waitpid(pid, &status, 0);  // Ожидание завершения дочернего процесса
        }
    }

    return OK;
}
