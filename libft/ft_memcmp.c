/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:13:26 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/26 19:24:21 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	while (n > 0)
	{
		if (*ptr1 != *ptr2)
			return ((int)(*ptr1 - *ptr2));
		ptr1++;
		ptr2++;
		n--;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char s1[] = "Hello, World!";
// 	char s2[] = "Hello,World!";
// 	int n = 13;
// 	int ret = ft_memcmp(s1, s2, n);
// 	int ret2 = memcmp(s1, s2, n);
// 	if (ret == 0)
// 	{
// 		printf("s1 and s2 are equal\n");
// 	}
// 	else
// 	{
// 		printf("s1 and s2 are not equal\n");
// 	}
// 	printf("%d\n", ret);
// 	printf("%d\n", ret2);
// 	return 0;
// }