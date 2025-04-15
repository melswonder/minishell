/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:08:36 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/15 20:08:30 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	wifexited(int status)
{
	return ((status & 0x7F) == 0);
}

int	wexitstatus(int status)
{
	return ((status >> 8) & 0xff);
}

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

char	*join_three_strings(char const *s1, char const *s2, char const *s3)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	return (ret);
}

int	is_directry(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/' && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}
