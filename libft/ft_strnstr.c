/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:14:42 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:31:09 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
		{
			if (!needle[j + 1])
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
// #include <string.h>
// #include <stdio.h>
// int main(void)
// {
// 	char *haystack = "Hello, World!";
// 	char *needle = "World";
// 	size_t len = 13;
// 	printf("ft_strnstr: %s\n", ft_strnstr(haystack, needle, len));
// 	printf("   strnstr: %s\n", strnstr(haystack, needle, len));
// 	return (0);
// }
