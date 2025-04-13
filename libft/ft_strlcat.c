/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:14:23 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:29:07 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	j = 0;
	dst_len = ft_strlen((const char *)dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (src_len + size);
	while (dst[j] && j < size)
		j++;
	while (src[i] && j < size - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (dst_len + src_len);
}

// #include <stdio.h>
// #include <string.h>

// int main ()
// {
// 	char dst[100] = "hello";
// 	char src[100] = "world";
// 	printf("%lu\n", ft_strlcat(dst, src, 100));
// 	printf("%s\n", dst);
// 	char dst2[100] = "hello";
// 	char src2[100] = "world";
// 	printf("%lu\n", strlcat(dst2, src2, 100));
// 	printf("%s\n", dst2);
// 	char dst3[100] = "hello ";
// 	char src3[100] = "world";
// 	printf("%lu\n", ft_strlcat(dst3, src3, 20));
// 	printf("%s\n", dst3);
// 	char dst4[100] = "hello ";
// 	char src4[100] = "world";
// 	printf("%lu\n", strlcat(dst4, src4, 20));
// 	printf("%s\n", dst4);
// 	return (0);
// }