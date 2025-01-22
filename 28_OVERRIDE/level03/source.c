#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Password doit etre dans l'intervalle [322424824, 322424845]
// BRUTEFORCE La bonne valeur est 322424827, qui donne diff = 18.
// Parce que 18 est la clé qui transforme "Q}|usfg~sf{}|a"en"Congratulations"`.
/*
EXAMPLE bitwise
char c = 'A' ^ 42;  // Chiffrement avec 42
char m = c ^ 42;    // Déchiffrement avec 42 (retrouve 'A')
*/
void decrypt(nb) {
    int i = 0;
    char* hash = "Q}|u`sfg~sf{}|a"; // version chiffre de congratuliations
    int hashLength = 15;
    char* buff1 = NULL;

    hashLength = strlen(hash);

    do {
        hash[i] = hash[i] ^ nb; // chaque caractere est modifie en fonction de la valeur de nb
        i++
    } while (i < hashLength)

    if (strncmp(hash, "Congratulations", 17) != 0) {
        puts("\nInvalid Password");
    } else {
        system("/bin/sh");

    }

    return;
}


// Calcule la difference entre password et 322424845
// Si cette diff est > a 21 decrypt est appele avec un nb aleatoire et on ne veut pas ca
// Si diff est entre 0 et 21, decrypt est appele avec diff en argument
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