/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:13:29 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:24:38 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	while (n > 0)
	{
		*d++ = *s++;
		n--;
	}
	return (dst);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char s1[] = "Hello, World!";
// 	char s2[100];
// 	ft_memcpy(s2, s1, 13);
// 	printf("%s\n", s2);
// 	char s4[] = "Hello, World!";
// 	char s3[100];
// 	memcpy(s3, s4, 13);
// 	printf("%s\n", s3);
// 	return (0);
// }