/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:51:43 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 19:50:18 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

int	ft_n_len(int n)
{
	int	result;

	if (n == 0)
		return (1);
	result = 0;
	if (n < 0)
		result++;
	while (n != 0)
	{
		n = n / 10;
		result++;
	}
	return (result);
}

char	*ft_itoa(int n)
{
	char	*dest;
	int		len;
	long	num;
	int		i;

	num = n;
	len = ft_n_len(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	if (num < 0)
	{
		dest[0] = '-';
		num = -num;
	}
	i = len - 1;
	while (num >= 10)
	{
		dest[i--] = (num % 10) + '0';
		num = num / 10;
	}
	dest[i] = num + '0';
	return (dest);
}
