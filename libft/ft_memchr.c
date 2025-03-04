/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:45:00 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 19:52:38 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
// sartch to int c == *s walnig diff kata
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	cp;

	cp = (unsigned char)c;
	ptr = (unsigned char *)s;
	while (n--)
	{
		if (*ptr == cp)
			return ((void *)ptr);
		ptr++;
	}
	return (0);
}
