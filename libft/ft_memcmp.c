/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:54:51 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 19:52:51 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// diff for n
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s_1;
	const unsigned char	*s_2;
	int					i;

	s_1 = (const unsigned char *)s1;
	s_2 = (const unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (s_1[i] != s_2[i])
			return (s_1[i] - s_2[i]);
		i++;
	}
	return (0);
}
