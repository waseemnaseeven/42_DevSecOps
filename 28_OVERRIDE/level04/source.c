#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

unsigned int get_unum(void) {
    unsigned int num = 0;
    fflush(stdout);
    scanf("%u", &num);
    clear_stdin();
    return num;
}

void prog_timeout(void) {
    exit(1);
}

void enable_timeout_cons(void) {
    signal(SIGALRM, prog_timeout);
    alarm(60);
}

int main(void) {
    char buffer[155] = {0}; // Local buffer (potential vulnerability)
    pid_t child_pid = fork();
    int status;
    long syscall;

    if (child_pid == 0) {
        // Child process
        prctl(PR_SET_PDEATHSIG, 1);
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        puts("Give me some shellcode, k");
        gets(buffer); // VULNERABLE: Buffer overflow
    } else {
        // Parent process
        while (1) {
            wait(&status);
            if (WIFEXITED(status) || (WIFSIGNALED(status) && WTERMSIG(status) != SIGSTOP)) {
                puts("child is exiting...");
                return 0;
            }
            syscall = ptrace(PTRACE_PEEKUSER, child_pid, 44, 0); // 44 = syscall register
            if (syscall == 11) { // 11 = execve syscall
                puts("no exec() for you");
                kill(child_pid, SIGKILL);
                return 0;
            }
        }
    }
    return 0;
}
