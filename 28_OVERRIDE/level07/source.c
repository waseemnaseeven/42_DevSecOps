#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned int numbers[100]; // Simulating memory used by `store_number`

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

unsigned int get_unum() {
    unsigned int num;
    fflush(stdout);
    scanf("%u", &num);
    clear_stdin();
    return num;
}

int store_number(unsigned int *storage) {
    unsigned int index, value;

    printf(" Number: ");
    number = get_unum();

    printf(" Index: ");
    index = get_unum();

    // Check if the index or number is reserved
    if ((index % 3 == 0) || ((number >> 24) == 0xb7)) {
        puts(" *** ERROR! ***");
        puts("   This index is reserved for wil!");
        puts(" *** ERROR! ***");
        return 1;
    }

    // Store the value at the index
    storage[index] = value;
    return 0;
}

// Read a number from a specific index in the storage
int read_number(uint32_t *storage) {
    unsigned int index;

    printf(" Index: ");
    index = get_unum();

    printf(" Number at data[%u] is %u\n", index, storage[index]);
    return 0;
}

int main(int argc, char **argv) {
    unsigned int *storage = (unsigned int *)malloc(400);
    memset(storage, 0, 400); // Zero-initialize storage
    int keep_running = 1;
    char command[20];

    while (keep_running) {
        printf("\n----------------------------------------------------\n");
        printf("  Welcome to the number storage service!           \n");
        printf("----------------------------------------------------\n");
        printf(" Commands:                                         \n");
        printf("    store - store a number                         \n");
        printf("    read  - read a number                          \n");
        printf("    quit  - exit the program                       \n");
        printf("----------------------------------------------------\n");

        printf("Input command: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "store") == 0) {
            if (store_number(storage)) {
                printf("Failed to store number.\n");
            }
        } else if (strcmp(command, "read") == 0) {
            if (read_number(storage)) {
                printf("Failed to read number.\n");
            }
        } else if (strcmp(command, "quit") == 0) {
            keep_running = 0;
        } else {
            printf("Unknown command: %s\n", command);
        }
    }

    free(storage); 
    return 0;
}
