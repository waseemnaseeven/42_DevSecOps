#include "../functions/includes/libasm_bonus.h"
#include "libasm_tester_bonus.h"
#include "../colors.h"
#include <stdlib.h>

#include <string.h> // Pour utiliser strdup


t_list *ft_create_elem(void *data)
{
    t_list *new;

    if (!(new = malloc(sizeof(t_list))))
        return (NULL);
    new->data = data;
    new->next = NULL;
    return (new);
}

void list_push_front(t_list **begin_list, void *data)
{
    t_list *f;

    if (*begin_list)
    {
        f = ft_create_elem(data);
        f->next = *begin_list;
        *begin_list = f;
    }
    else
        *begin_list = ft_create_elem(data);
}

void ft_list_push_front_test(void)
{
    printf(BOLDWHITE "Testing chain list function\n" RESET);

    t_list *lst = NULL;
    int array[] = {3, 4, 6 , 7, 8};
    // list_push_front(&lst, strdup("Coucou"));
    for (int i = 0; i < 5; i++)
    {
        list_push_front(&lst, &array[i]);
    }
    

    // Affichage de la liste
    printf(BOLDMAGENTA "Here is my list from the C function: {");

    t_list *tmp = lst;
    while (tmp != NULL)
    {
        printf("%d, ", *(int *)(tmp->data));
        tmp = tmp->next;
    }
    printf("}\n" RESET);

    t_list *lst2 = NULL;
    
    ft_list_push_front(&lst2, strdup("Coucou2"));
    printf(BOLDCYAN "Here is my list from my assembly function: {");
    t_list *tmp2 = lst2;
    while (tmp2 != NULL)
    {
        printf("%s, ", (char *)(tmp2->data));
        tmp2 = tmp2->next;
    }
    printf("}\n" RESET);

    // Libération de la mémoire
    while (lst != NULL)
    {
        t_list *next = lst->next;
        free(lst->data); // Libération de la mémoire allouée par strdup
        free(lst);
        lst = next;
    }
    while (lst2 != NULL)
    {
        t_list *next = lst2->next;
        free(lst2->data); // Libération de la mémoire allouée par strdup
        free(lst2);
        lst2 = next;
    }
}
