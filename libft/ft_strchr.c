/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:07:12 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 19:55:43 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// srtch to c return to
char	*ft_strchr(const char *s, int c)
{
	unsigned char	char_c;
	size_t			i;

	char_c = (char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == char_c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == char_c)
		return ((char *)(s + i));
	return (NULL);
}
