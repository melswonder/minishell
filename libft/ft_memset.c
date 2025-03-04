/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 22:06:26 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 19:54:56 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// set character for size_t n element
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	char_c;

	ptr = (unsigned char *)s;
	char_c = (unsigned char)c;
	while (n--)
	{
		*ptr = char_c;
		ptr++;
	}
	return ((void *)s);
}
