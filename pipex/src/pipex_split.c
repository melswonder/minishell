/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:08:23 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/21 19:27:48 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pip.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	size_t			i;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (len--)
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static size_t	split_countwords(const char *s, char c)
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
	const size_t	words_len = split_countwords(s, c);
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

char	**envp_split(char **envp, int path_index)
{
	char		**path;
	int			i;
	const int	words_len = countwords(envp[path_index]);

	path = (char **)malloc((words_len + 1) * sizeof(char *));
	if (!(path))
		return (0);
	i = 0;
	while (i < words_len)
	{
		path[i] = add_path(envp[path_index], i);
		i++;
	}
	path[i - 1] = after_path(envp[path_index]);
	path[i] = NULL;
	return (path);
}
