#ifndef LIBASM_H
# define LIBASM_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stddef.h>
# include <sys/types.h>

typedef struct  s_list
{
    void *data;
    struct s_list *next;
}               t_list;

void    ft_list_push_front(t_list **begin_lst, void *data);

int     ft_list_size(t_list *begin_lst);

#endif // LIBASM_BONUS_H