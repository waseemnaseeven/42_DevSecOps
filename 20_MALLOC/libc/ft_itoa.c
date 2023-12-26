/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnaseeve <wnaseeve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 10:20:22 by wnaseeve          #+#    #+#             */
/*   Updated: 2023/12/26 12:14:39 by wnaseeve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	count(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = (unsigned int) n * (-1);
	}
	while ((unsigned int)n > 0)
	{
		len++;
		n = (unsigned int) n / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = count(n);
	str = (malloc(sizeof(char) * (len + 1)));
	if (!str)
		return (0);
	str[len] = '\0';
	len--;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		str[0] = '-';
		n *= -1;
	}
	while ((unsigned int) n > 0)
	{
		str[len] = ((unsigned int)n % 10) + '0';
		n = (unsigned int) n / 10;
		len--;
	}
	return (str);
}
/*
int main(void)
{
	printf("%s\n", ft_itoa(-2147483648));
	printf("%s\n", ft_itoa(2147483647));
	printf("%s\n", ft_itoa(-21474));
	printf("%s\n", ft_itoa(42));
	printf("%s\n", ft_itoa(0));
	printf("%p\n", NULL);
}
*/
