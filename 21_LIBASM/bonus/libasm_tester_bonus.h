#ifndef LIBASM_TESTER_H
# define LIBASM_TESTER_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>



void ft_list_size_test(void);
void ft_list_push_front_test(void);
void list_push_front(t_list **begin_list, void *data);

#endif // LIBASM_TESTER_H