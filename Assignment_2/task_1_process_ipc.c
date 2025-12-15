#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER_SIZE 256

void reverse_string(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char tmp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = tmp;
    }
}

int main() {
    int parent_to_child[2];
    int child_to_parent[2];
    pid_t pid;
    char buffer[BUFFER_SIZE];

    pipe(parent_to_child);
    pipe(child_to_parent);

    pid = fork();

    if (pid > 0) {
        /* ---------- Parent process ---------- */
        close(parent_to_child[0]);
        close(child_to_parent[1]);

        printf("Parent (PID: %d) created child (PID: %d)\n", getpid(), pid);
        printf("Parent (PID: %d) sleeping 20 seconds. Check with ps...\n", getpid());

        sleep(20);   // ⏸ Пауза для просмотра процессов

        char message[] = "Hello from Parent";
        printf("Parent (PID: %d) sending data: %s\n", getpid(), message);

        write(parent_to_child[1], message, strlen(message) + 1);
        read(child_to_parent[0], buffer, BUFFER_SIZE);

        printf("Parent (PID: %d) received result: %s\n", getpid(), buffer);

    } else if (pid == 0) {
        /* ---------- Child process ---------- */
        close(parent_to_child[1]);
        close(child_to_parent[0]);

        printf("Child (PID: %d, PPID: %d) started\n", getpid(), getppid());
        printf("Child (PID: %d) sleeping 20 seconds. Check with ps...\n", getpid());

        sleep(20);   // ⏸ Пауза для просмотра процессов

        read(parent_to_child[0], buffer, BUFFER_SIZE);
        printf("Child (PID: %d) received data: %s\n", getpid(), buffer);

        reverse_string(buffer);
        printf("Child (PID: %d) processed data\n", getpid());

        write(child_to_parent[1], buffer, strlen(buffer) + 1);
    }

    return 0;
}
