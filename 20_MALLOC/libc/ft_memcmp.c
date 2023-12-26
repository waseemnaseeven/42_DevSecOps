/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaseeve <wnaseeve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:39:55 by wnaseeve          #+#    #+#             */
/*   Updated: 2023/12/26 12:16:58 by wnaseeve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned int	res;

	i = 0;
	res = 0;
	while (i < n)
	{
		res = *(unsigned char *)s1++ - *(unsigned char *)s2++;
		if (res)
			return (res);
		i++;
	}
	return (0);
}
/*
int main(void)
{
	int array1 [] = { 54, 85, 20, 63, 21 };
    	int array2 [] = { 54, 85, 19, 63, 21 };
    	unsigned int size = sizeof( int ) * 5;
    	assert( memcmp( array1, array2, size) == ft_memcmp( array1, array2, size) );
    	assert( memcmp( array1, array1, size) == ft_memcmp( array1, array1, size) );
    	assert( memcmp( array2, array1, size) == ft_memcmp( array2, array1, size) );
    	printf( "Test is ok\n" );
    	return 0;
}
*/
