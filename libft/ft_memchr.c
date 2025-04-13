/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:13:22 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:13:24 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*ptr;
	unsigned char		ch;

	ptr = (const unsigned char *)s;
	ch = (unsigned char)c;
	while (n > 0)
	{
		if (*ptr == ch)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char s[] = "Hello, World!";
// 	char *p = ft_memchr(s, 'W', 13);
// 	char *p2 = memchr(s, 'W', 13);
// 	if (p == NULL )
// 	{
// 		printf("Not found\n");
// 		return 1;
// 	}
// 	if (p2 == NULL)
// 	{
// 		printf("Not found\n");
// 		return 1;
// 	}
// 	printf("%s\n", p);
// 	printf("%s\n", p2);
// 	return 0;
// }