/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:14:01 by kiwasa            #+#    #+#             */
/*   Updated: 2024/10/27 16:22:31 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*allocate_and_copy_word(char const *s, char c)
{
	size_t	i;
	size_t	len;
	char	*word;

	len = 0;
	while (s[len] != '\0' && s[len] != c)
		len++;
	word = (char *)ft_calloc(len + 1, sizeof(char));
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i ++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	size_t	i;
	size_t	j;

	if (s == NULL)
		return (NULL);
	strs = (char **)ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			strs[j] = allocate_and_copy_word(s + i, c);
			if (strs[j] == NULL)
				return (free_strs(strs));
			j++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
			i++;
	}
	strs[j] = NULL;
	return (strs);
}

// #include <stdio.h>
// int main()
// {
// 	char *s = "Hello World!";
// 	char **strs = ft_split(s, ' ');
// 	int i = 0;
// 	while (strs[i] != NULL)
// 	{
// 		printf("%s\n", strs[i]);
// 		i++;
// 	}
// 	while(i >= 0)
// 	{
// 		free(strs[i]);
// 		i--;
// 	}
// 	free(strs);
// 	return (0);
// }
