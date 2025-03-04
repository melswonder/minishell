/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:06:05 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 19:56:32 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// all copy and return to first pointer
char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*start;

	dest = (char *)malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	start = dest;
	while (*s)
	{
		*dest = *s;
		dest++;
		s++;
	}
	*dest = '\0';
	return (start);
}
