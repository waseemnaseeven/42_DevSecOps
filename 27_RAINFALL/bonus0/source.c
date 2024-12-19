#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Lit une entree, remplace '\n' par '\0', copie jusqu'a 20bytes dans param_1
void p(char *param_1, char *param_2) {
    char buffer[4104]; // lea eax,[ebp-0x1008]

    puts(param_2);
    read(0, buffer, 4096);
    char *newline = strchr(buffer, '\n');
    if (newline) *newline = '\0';
    strncpy(param_1, buffer, 20);
}

// Call 2x p
void pp(char *param_1) {
    // HERE: si on lit + de 20 caracteres, la fonction puts va afficher le contenu du buffer et crash
    char local_34[20]; // tmp buffer 
    char local_20[20]; // tmp buffer

    p(local_34, "Enter first part:");
    p(local_20, "Enter second part:");

    strcpy(param_1, local_34);

    size_t len = strlen(param_1);
    param_1[len] = ' ';
    param_1[len + 1] = '\0';

    strcat(param_1, local_20);
}

int main(void) {
    char local_3a[54];
    pp(local_3a);
    puts(local_3a);
    return 0;
}
