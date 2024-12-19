#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Buffer pour le mdp
char c[68];

struct my_struct {
    int id;
    char *str;
};

// Fonction qui affiche le contenu de 'c' qui est le mdp et l'heure actuelle
void m(void *param_1, int param_2, char *c, int param_4, int param_5) {
    time_t current_time;
    
    current_time = time(NULL);
    
    printf("%s - %ld\n", c, current_time);
}

int main(int argc, char **argv) {
    struct my_struct *s1, *s2;
    FILE *stream;

    // Vérification du nombre d'arguments
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <arg1> <arg2>\n", argv[0]);
        return 1;
    }

    s1 = malloc(sizeof(struct my_struct));
    if (s1 == NULL) {
        perror("malloc");
        return 1;
    }
    s1->id = 1;
    s1->str = malloc(8);
    if (s1->str == NULL) {
        perror("malloc");
        free(s1);
        return 1;
    }

    s2 = malloc(sizeof(struct my_struct));
    if (s2 == NULL) {
        perror("malloc");
        free(s1->str);
        free(s1);
        return 1;
    }
    s2->id = 2;
    s2->str = malloc(8);
    if (s2->str == NULL) {
        perror("malloc");
        free(s2);
        free(s1->str);
        free(s1);
        return 1;
    }

    // Copie des arguments de la ligne de commande dans les structures
    strcpy(s1->str, argv[1]);
    strcpy(s2->str, argv[2]);

    // Ouverture fichier mdp
    stream = fopen("/home/user/level8/.pass", "r");
    if (stream == NULL) {
        perror("fopen");
        free(s2->str);
        free(s2);
        free(s1->str);
        free(s1);
        return 1;
    }
    
    // Lecture dans un buffer c[68] via fgets
    if (fgets(c, sizeof(c), stream) == NULL) {
        perror("fgets");
        fclose(stream);
        free(s2->str);
        free(s2);
        free(s1->str);
        free(s1);
        return 1;
    }

    fclose(stream);

    // Affichage d'un message
    puts("~~");

    free(s2->str);
    free(s2);
    free(s1->str);
    free(s1);

    return 0;
}
