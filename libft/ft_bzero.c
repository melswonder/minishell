/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loremipsum <loremipsum@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:32:53 by hirwatan          #+#    #+#             */
/*   Updated: 2024/11/01 14:11:24 by loremipsum       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// bzero is all contents of array null
void	ft_bzero(void *s, size_t n)
{
	unsigned char *p;
	int i;

	i = 0;
	p = (unsigned char *)s;
	if (n == 0 || !s)
		return ;
	while (n--)
	{
		p[i] = '\0';
		i++;
	}
}
