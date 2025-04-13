/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:14:49 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/27 17:43:40 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != 0)
		i++;
	while (len > i && ft_strchr(set, s1[len - 1]) != 0)
		len--;
	str = (char *)malloc(len - i + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, &s1[i], len - i + 1);
	return (str);
}

// #include <stdio.h>

// int main()
// {
// 	char *s1 = "   Hello World!   ";
// 	char *set = " ";
// 	printf("%s\n", ft_strtrim(s1, set));
// 	return (0);
// }