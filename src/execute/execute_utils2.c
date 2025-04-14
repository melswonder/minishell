/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:36 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 17:52:57 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*next;
	char		*start;
	const char	*d;

	if (str != NULL)
		next = str;
	if (next == NULL || *next == '\0')
		return (NULL);
	start = next;
	d = delim;
	while (*d != '\0')
	{
		if (*next == *d)
		{
			*next = '\0';
			next++;
			if (start == next - 1)
				return ft_strtok(NULL, delim);
			return (start);
		}
		d++;
	}
	next++;
	return ft_strtok(NULL, delim);
}

int	ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	if (to_find[0] == '\0')
		return (str);
	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0')
		{
			if (str[i + j] == to_find[j])
			{
				j++;
			}
			else
				break ;
		}
		if (to_find[j] == '\0')
		{
			return (str + i);
		}
		i++;
	}
	return (0);
}

int	ft_n_len(int n)
{
	int	result;

	if (n == 0)
		return (1);
	result = 0;
	if (n < 0)
		result++;
	while (n != 0)
	{
		n = n / 10;
		result++;
	}
	return (result);
}

size_t ft_strnlen(const char *s, size_t n)
{
    size_t i;

    i = 0;
    while (i < n && s[i] != '\0')
        i++;
    return (i);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*new;
	size_t	len;

	len = ft_strnlen(s, n);
	new = (char *)malloc(len + 1);
	if (!new)
		return (NULL);
	new[len] = '\0';
	while (len-- > 0)
		new[len] = s[len];
	return (new);
}