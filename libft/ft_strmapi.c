/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:14:34 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:30:27 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;
	size_t	len;

	str = ft_strdup(s);
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

// char ft_strmap(unsigned int i, char c)
// {
// 	if (i % 2 == 0)
// 		return (c - 32);
// 	return (c);
// }

// #include <stdio.h>
// int main()
// {
// 	char *s = "hello world";
// 	char *str = ft_strmapi(s, &ft_strmap);
// 	printf("%s\n", str);
// 	return (0);
// }