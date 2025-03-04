/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 16:12:54 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/30 21:47:06 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

//まだじぞう
void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	size_t	i;

	if (!size || !count)
		return (malloc(0));
	if (4294967295 / size < count)
		return (NULL);
	p = (char *)malloc(count * size);
	if (!p)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}
