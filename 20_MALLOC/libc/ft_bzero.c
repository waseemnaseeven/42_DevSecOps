/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaseeve <wnaseeve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:56:30 by wnaseeve          #+#    #+#             */
/*   Updated: 2023/12/26 12:14:51 by wnaseeve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp;

	if ((!s) || (!n))
		return ;
	tmp = s;
	while (n--)
		*tmp++ = '\0';
}
/*
int main(void)
{
	char str[50] = "This is string.h library function";
	printf("%s\n", str);
	ft_bzero(str, 9);
	printf("%s\n", str);

	int *tab = malloc(10 *sizeof(int));
	int i = 0;
	 for ( i=0; i<10; i++ ) {
        tab[i] = i;
    }
	i = 0;
	while (i < 10)
	{
		ft_bzero(tab,6);
		printf("%d", tab[i]);
		i++;
	}
	return (0);
}
*/