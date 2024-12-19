#include <stdio.h>
#include <string.h>

// Expected username and password
const char *expected_username = "dat_wil";
const char *expected_password = "admin"; // ?????

// Verify the username
int verify_user_name(const char *username) {
    puts("Verifying username...\n");
    return strncmp(username, expected_username, strlen(expected_username));
}

// Verify the password
int verify_user_pass(const char *password) {
    return strncmp(password, expected_password, strlen(expected_password));
}

int main(void) {
    char username[256];
    char password[100];
    int result;

    puts("********* ADMIN LOGIN PROMPT *********");

    printf("Enter Username: ");
    if (!fgets(username, sizeof(username), stdin)) {
        puts("Error reading username.");
        return 1;
    }

    username[strcspn(username, "\n")] = '\0';

    // Check username
    result = verify_user_name(username);
    if (result != 0) {
        puts("Nope, incorrect username...\n");
        return 1;
    }

    // Request password
    printf("Enter Password: ");
    if (!fgets(password, sizeof(password), stdin)) {
        puts("Error reading password.");
        return 1;
    }

    // Remove the trailing newline
    password[strcspn(password, "\n")] = '\0';

    // Check password
    result = verify_user_pass(password);
    if (result != 0) {
        puts("Nope, incorrect password...\n");
        return 1;
    }

    puts("Authentication successful!");
    return 0;
}
