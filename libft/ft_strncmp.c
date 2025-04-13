/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:14:37 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/27 16:03:26 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char s1[100] = "hello";
// 	char s2[100] = "hello";
// 	printf("%d\n", ft_strncmp(s1, s2, 5));
// 	printf("%d\n", ft_strncmp(s1, s2, 3));
// 	printf("%d\n", ft_strncmp(s1, s2, 10));

// 	printf("%d\n", strncmp(s1, s2, 5));
// 	printf("%d\n", strncmp(s1, s2, 3));
// 	printf("%d\n", strncmp(s1, s2, 10));
// 	char s3[100] = "hell";
// 	char s4[100] = "hel";
// 	printf("%d\n", ft_strncmp(s3, s4, 5));
// 	printf("%d\n", ft_strncmp(s3, s4, 3));
// 	printf("%d\n", ft_strncmp(s3, s4, 10));
// 	printf("%d\n", strncmp(s3, s4, 5));
// 	printf("%d\n", strncmp(s3, s4, 3));
// 	printf("%d\n", strncmp(s3, s4, 10));
// 	return (0);
// }