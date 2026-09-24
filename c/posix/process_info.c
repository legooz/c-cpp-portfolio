#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* With arguments, run that command in the child. Otherwise run `true`.
   This keeps the fork/exec/wait demonstration short and deterministic. */
int main(int argc, char *argv[]) {
    fflush(NULL);
    pid_t child = fork();
    if (child < 0) { perror("fork"); return 1; }
    if (child == 0) {
        printf("Child PID: %ld; parent PID: %ld\n", (long)getpid(), (long)getppid());
        fflush(stdout);
        char *default_args[] = {"true", NULL};
        char **command = argc > 1 ? &argv[1] : default_args;
        execvp(command[0], command);
        perror("execvp");
        _exit(127);
    }
    printf("Parent PID: %ld; child PID: %ld\n", (long)getpid(), (long)child);
    int status;
    while (waitpid(child, &status, 0) < 0) {
        if (errno == EINTR) continue;
        perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status)) return WEXITSTATUS(status);
    if (WIFSIGNALED(status)) return 128 + WTERMSIG(status);
    return 1;
}
