/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaseeve <wnaseeve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:25:57 by wnaseeve          #+#    #+#             */
/*   Updated: 2023/12/26 12:17:04 by wnaseeve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned const char	*s;
	size_t				i;

	d = dest;
	s = src;
	i = 0;
	if (d < s)
	{
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else if (d > s)
		while (n-- > 0)
			d[n] = s[n];
	return (d);
}
/*
int main() 
{
    char dest[] = "Aticleworfeioshfsoigs";
    const char src[]  = "iwaohifho";
    //Source and destination before memmove
    printf("Before memmove >> dest = %s, src = %s\n\n", dest, src);
    ft_memmove(dest, src, 9);
    //Source and destination after memmove
    printf("After memmove >> dest = %s, src = %s\n\n", dest, src);
    return 0;
}
*/