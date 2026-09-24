#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* Tutorial 4: the child displays the parent/child process tree with IDs.
   An explicit command remains available for testing fork/exec failure paths. */
int main(int argc, char *argv[]) {
    const pid_t parent = getpid();
    fflush(NULL);
    pid_t child = fork();
    if (child < 0) { perror("fork"); return 1; }
    if (child == 0) {
        printf("Child PID: %ld; parent PID: %ld\n", (long)getpid(), (long)getppid());
        fflush(stdout);
        char parent_text[32];
        snprintf(parent_text, sizeof(parent_text), "%ld", (long)parent);
        char *default_args[] = {"pstree", "-p", parent_text, NULL};
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
