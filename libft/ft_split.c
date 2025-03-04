/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:01:19 by hirwatan          #+#    #+#             */
/*   Updated: 2024/10/31 19:55:39 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	countwords(const char *s, char c)
{
	size_t	count;
	int		flag;
	int		i;

	count = 0;
	flag = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c && flag == 0)
		{
			flag = 1;
			count++;
		}
		else if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static void	*mem_free(char **split, size_t word_i)
{
	size_t	i;

	i = 0;
	while (i < word_i)
	{
		free(split[i]);
		i++;
	}
	return (free(split), NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**split;
	const size_t	words_len = countwords(s, c);
	size_t			i;
	size_t			word_i;
	size_t			word_start;

	split = malloc((words_len + 1) * sizeof(char *));
	if (!s || !(split))
		return (0);
	word_i = 0;
	i = 0;
	while (word_i < words_len)
	{
		while (s[i] == c)
			i++;
		word_start = i;
		while ((s[i] != c) && s[i])
			i++;
		split[word_i] = ft_substr(s, word_start, i - word_start);
		if (!split[word_i])
			return (mem_free(split, word_i));
		word_i++;
	}
	split[word_i] = NULL;
	return (split);
}
