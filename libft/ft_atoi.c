/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:07:33 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/27 17:01:10 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (sign == 1 && result > (LONG_MAX - (str[i] - '0')) / 10)
			return ((int)LONG_MAX);
		else if (sign == -1 && result > (LONG_MAX - (str[i] - '0')) / 10)
			return ((int)LONG_MIN);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(void)
// {
// 	char str[100] = "+123";
// 	printf("%d\n", ft_atoi(str));
// 	printf("%d\n", atoi(str));
// 	char str2[100] = "   123";
// 	printf("%d\n", ft_atoi(str2));
// 	printf("%d\n", atoi(str2));
// 	char str3[100] = "-123";
// 	printf("%d\n", ft_atoi(str3));
// 	printf("%d\n", atoi(str3));
// 	char str4[100] = "123afda";
// 	printf("%d\n", ft_atoi(str4));
// 	printf("%d\n", atoi(str4));
// 	return (0);
// }