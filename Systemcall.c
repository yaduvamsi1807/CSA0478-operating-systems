#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t child_pid, parent_pid;

    // Create a child process
    child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) { 
        // Child process
        printf("I am the child process. My PID is: %d\n", getpid());
        printf("My parent's PID is: %d\n", getppid());
    } else {
        // Parent process
        printf("I am the parent process. My PID is: %d\n", getpid());
        printf("My child's PID is: %d\n", child_pid);
    }

    return 0;
}
