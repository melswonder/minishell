/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:14:46 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/27 17:40:57 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	char *s = "Hello, World!";
// 	char c = 'o';
// 	printf("ft_strrchr: %s\n", ft_strrchr(s, c));
// 	printf("   strrchr: %s\n", strrchr(s, c));
// 	return (0);
// }