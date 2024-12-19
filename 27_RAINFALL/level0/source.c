#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define STRING_PATH "/home/user/level1/.pass"
#define ERROR_MSG "Invalid input. Access denied.\n"
#define COMMAND_PATH "/bin/bash"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int input = atoi(argv[1]);

    if (input != 423) {
        fprintf(stderr, ERROR_MSG);
        return 1;
    }

    char *duplicate = strdup(STRING_PATH);
    if (!duplicate) {
        perror("strdup failed");
        return 1;
    }

    gid_t gid = getegid();
    uid_t uid = geteuid();
    if (setresgid(gid, gid, gid) == -1 || setresuid(uid, uid, uid) == -1) {
        perror("setresgid/setresuid failed");
        free(duplicate);
        return 1;
    }

    char *args[] = {COMMAND_PATH, NULL};
    execv(duplicate, args);

    perror("execv failed");
    free(duplicate);
    return 1;
}
