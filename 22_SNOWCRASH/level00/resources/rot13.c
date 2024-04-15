#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int ac, char **av)
{
    if (ac != 3) {
        printf("Just the text to decrypt and the offset\n");
        return 0;
    }
    
    int offset = atoi(av[2]);
    while (offset <= 26) {
        int i = 0;
        char *to_decrypt = strdup(av[1]);
        printf("THE WORD IS = %s\n", to_decrypt);
        while (to_decrypt[i]) {
        
            if (to_decrypt[i] >= 'a' && to_decrypt[i] <= 'z') {
                to_decrypt[i] = 'a' + (to_decrypt[i] - 'a' + offset) % 26; 
            }
            else if (to_decrypt[i] >= 'A' && to_decrypt[i] <= 'Z') {
                to_decrypt[i] = 'A' + (to_decrypt[i] - 'A' + offset) % 26; 
            }
            i++;
        }
        printf("The word now = %s\n", to_decrypt);
        printf("offset = %d\n", offset);
        offset++;
        free(to_decrypt);

    }
    return 0;
}
