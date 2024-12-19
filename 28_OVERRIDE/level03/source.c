#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void decrypt(nb) {
    int i = 0;
    char* hash = "Q}|u`sfg~sf{}|a";
    int hashLength = 15;
    char* buff1 = NULL;

    hashLength = strlen(hash);

    do {
        hash[i] = hash[i] ^ nb;
        i++
    } while (i < hashLength)

    if (strncmp(hash, "Congratulations!", 17) != 0) {
        puts("\nInvalid Password");
    } else {
        system("/bin/sh");

    }

    return;
}

void test(int param_1, int param_2) {
    int diff = param_2 - param_1;

    if (diff >= 0 && diff <= 21) {
        decrypt((unsigned char)diff);
    } else {
        decrypt((unsigned char)rand());
    }
}

int main(void) {
    unsigned int seed;

    // Seed the random number generator
    seed = (unsigned int)time(NULL);
    srand(seed);

    puts("***********************************");
    puts("*\t\tlevel03\t\t**");
    puts("***********************************");
    printf("Password: ");

    unsigned int input = get_unum();

    test(input, 0x1337d00d); // Call the test function with hardcoded second parameter
    // Password:322424845
    return 0;
}