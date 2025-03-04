/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 20:54:24 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 19:53:05 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// dest cpy src n_size to much!
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ds;
	unsigned char	*sr;

	ds = (unsigned char *)dest;
	sr = (unsigned char *)src;
	while (n--)
	{
		*ds++ = *sr++;
	}
	return ((void *)dest);
}
