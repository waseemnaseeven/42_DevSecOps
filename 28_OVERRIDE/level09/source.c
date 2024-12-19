#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void secret_backdoor() {
    char command[128];
    fgets(command, sizeof(command), stdin);
    system(command);
}

void set_username(char *user_data) {
    char username[140] = {0};
    printf(">: Enter your username\n>>: ");
    fgets(username, sizeof(username), stdin);
    strncpy(user_data + 140, username, 40);
    printf(">: Welcome, %s", user_data + 140);
}

void set_msg(char *user_data) {
    char msg[1024] = {0};
    printf(">: Msg @Unix-Dude\n>>: ");
    fgets(msg, sizeof(msg), stdin);
    strncpy(user_data, msg, *(int *)(user_data + 180)); // overflow here 
}

void handle_msg() {
    char user_data[192] = {0};
    *(int *)(user_data + 180) = 140;
    set_username(user_data);
    set_msg(user_data);
    puts(">: Msg sent!");
}

int main() {
    puts("--------------------------------------------");
    puts("|   ~Welcome to l33t-m$n ~    v1337        |");
    puts("--------------------------------------------");
    handle_msg();
    return 0;
}
