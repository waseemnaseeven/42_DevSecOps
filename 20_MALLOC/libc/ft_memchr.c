/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaseeve <wnaseeve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:31:10 by wnaseeve          #+#    #+#             */
/*   Updated: 2023/12/26 12:16:52 by wnaseeve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t size)
{
	unsigned const char	*tmp;
	unsigned char		ch;

	tmp = s;
	ch = c;
	while (size--)
	{
		if (*tmp++ == ch)
			return ((void *)(tmp - 1));
	}
	return (NULL);
}
