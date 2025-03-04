/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 21:33:11 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 20:34:09 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// memomove is memecopy v2 is sefty
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*ds;
	unsigned char	*sr;

	ds = (unsigned char *)dest;
	sr = (unsigned char *)src;
	if (ds < sr)
	{
		while (n--)
		{
			*ds++ = *sr++;
		}
	}
	else if (ds > sr)
	{
		ds += n;
		sr += n;
		while (n--)
			*(--ds) = *(--sr);
	}
	return (dest);
}
