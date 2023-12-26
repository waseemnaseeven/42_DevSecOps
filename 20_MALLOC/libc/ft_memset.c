/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaseeve <wnaseeve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:28:18 by wnaseeve          #+#    #+#             */
/*   Updated: 2023/12/26 12:15:31 by wnaseeve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*tmp;

	tmp = s;
	while (n--)
		*tmp++ = (unsigned char) c;
	return (s);
}
/*
int main()
{
	int arr[30] = {48,468,61,489,3};
	size_t size = sizeof( int ) * 5;
    	int length;
	void *a = arr;

    	// Display the initial values 
    	for( length=0; length<5; length++)
        	printf( "%d ", arr[ length ] );
    	printf( "\n" );

    	// Reset the memory bloc
    	ft_memset(arr, 0, size);

    	//Display the new values 
    	for( length=0; length<5; length++)
        	printf( "%d ", arr[ length ] );
    printf( "\n" );

    	for( length=0; length<5; length++)
		printf("%p ", &a);
    return 0;
}
*/