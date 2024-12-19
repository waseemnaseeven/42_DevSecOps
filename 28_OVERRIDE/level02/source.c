#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char password_file_content[48] = {0};
    char username[100] = {0};            
    char password[100] = {0};            
    FILE *password_file;

    // Ouvre le fichier contenant le mot de passe
    password_file = fopen("/home/users/level03/.pass", "r");
    if (password_file == NULL) {
        fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
        exit(1);
    }

    // Lit le contenu du fichier dans `password_file_content`
    size_t password_length = fread(password_file_content, 1, 41, password_file);
    fclose(password_file);

    if (password_length != 41) {
        fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
        exit(1);
    }

    // Supprime le caractère de nouvelle ligne du contenu lu
    size_t newline_pos = strcspn(password_file_content, "\n");
    password_file_content[newline_pos] = '\0';

    // Affiche l'interface utilisateur
    puts("===== [ Secure Access System v1.0 ] =====");
    puts("/***************************************\\");
    puts("| You must login to access this system. |");
    puts("\\**************************************/");
    
    // Demande et lit le nom d'utilisateur
    printf("--[ Username: ");
    fgets(username, sizeof(username), stdin);
    newline_pos = strcspn(username, "\n");
    username[newline_pos] = '\0';

    // Demande et lit le mot de passe
    printf("--[ Password: ");
    fgets(password, sizeof(password), stdin);
    newline_pos = strcspn(password, "\n");
    password[newline_pos] = '\0';

    puts("*****************************************");

    // Vérifie si le mot de passe est correct
    if (strncmp(password_file_content, password, 41) == 0) {
        printf("Greetings, %s!\n", username);
        system("/bin/sh"); // Lancer un shell si le mot de passe est correct
        return 0;
    } else {
        printf("%s does not have access!\n", username);
        exit(1);
    }
}
