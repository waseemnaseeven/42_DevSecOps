#ifndef LIBASM_TESTER_H
# define LIBASM_TESTER_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

// typedef struct  s_list
// {
//     void *data;
//     struct s_list *next;

// }               t_list;

void ft_list_size_test(void);
void ft_list_push_front_test(void);

#endif // LIBASM_TESTER_H