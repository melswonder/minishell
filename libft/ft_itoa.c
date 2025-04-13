/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:12:17 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:16:34 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			buf[12];
	int				i;
	unsigned int	num;

	i = 12;
	buf[--i] = '\0';
	if (n >= 0)
		num = n;
	else
		num = -n;
	while (1)
	{
		buf[--i] = num % 10 + '0';
		num /= 10;
		if (num == 0)
			break ;
	}
	if (n < 0)
		buf[--i] = '-';
	return (ft_strdup(&buf[i]));
}

// #include <stdio.h>
// int main()
// {
// 	int n = 123;
// 	printf("%s\n", ft_itoa(n));
// 	int n2 = -123;
// 	printf("%s\n", ft_itoa(n2));
// 	int n3 = 0;
// 	printf("%s\n", ft_itoa(n3));
// 	return (0);
// }
