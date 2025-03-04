/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:02:33 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 19:57:35 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// sartch to c for last word s
char	*ft_strrchr(const char *s, int c)
{
	char	*last_wold;
	int		i;

	last_wold = NULL;
	if (s == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			last_wold = (char *)&s[i];
		i++;
	}
	if (c == (int)'\0')
		return ((char *)&s[i]);
	return (last_wold);
}
