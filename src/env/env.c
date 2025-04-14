/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:12:52 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 21:38:56 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_path_segments(char *path)
{
	int	count;
	int	i;

	count = 1;
	i = 0;
	if (!path)
		return (0);
	while (path[i])
	{
		if (path[i++] == ':')
			count++;
	}
	return (count);
}

void	fill_path_array(char **result, char *path)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_strtok(path, ":");
	while (token)
	{
		result[i++] = ft_strdup(token);
		token = ft_strtok(NULL, ":");
	}
	result[i] = NULL;
}

char	**split_path_env(char *path)
{
	char	*path_dup;
	char	**result;
	int		count;

	if (!path)
		return (NULL);
	count = count_path_segments(path);
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	path_dup = ft_strdup(path);
	if (!path_dup)
	{
		free(result);
		return (NULL);
	}
	fill_path_array(result, path_dup);
	free(path_dup);
	return (result);
}

char	*env_print_join(char *line, char *key, char *value)
{
	int	key_len;
	int	value_len;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	ft_strlcpy(line, key, key_len + 1);
	line[key_len] = '=';
	ft_strlcpy(line + key_len + 1, value, value_len + 1);
	return (line);
}

char	**convert_env_to_array(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	char	*line;
	int		i;
	int		count;

	count = 0;
	tmp = env;
	while (tmp && ++count)
		tmp = tmp->next;
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		line = malloc(strlen(tmp->key) + ft_strlen(tmp->value) + 2);
		if (!line)
			break ;
		envp[i++] = env_print_join(line, tmp->key, tmp->value);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
