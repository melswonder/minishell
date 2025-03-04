/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:15:04 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/24 19:49:18 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		s1_size;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_size = ft_strlen(s1);
	dest = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		dest[s1_size + i] = s2[i];
		i++;
	}
	dest[s1_size + i] = '\0';
	return (dest);
}
