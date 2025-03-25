/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:17:01 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/21 19:27:48 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pip.h"

char	*first_path(char *str)
{
	int		i;
	int		path_len;
	char	*path;
	int		k;

	i = 0;
	path_len = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	while (str[i + path_len] && str[i + path_len] != ':')
		path_len++;
	path = (char *)malloc((path_len + 1) * sizeof(char));
	if (!path)
		return (NULL);
	k = 0;
	while (k < path_len)
	{
		path[k] = str[i + k];
		k++;
	}
	path[path_len] = '\0';
	return (path);
}

char	*after_path(char *str)
{
	int		i;
	int		len;
	int		start;
	char	*ret;

	start = 0;
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == ':')
			start = i + 1;
		i++;
	}
	len = i - start;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, str + start, len);
	ret[len] = '\0';
	return (ret);
}

char	*copy_path(const char *str, int start, int end)
{
	int		len;
	char	*ret;

	len = end - start;
	ret = (char *)malloc(len + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, str + start, len);
	ret[len] = '\0';
	return (ret);
}

char	*add_path(char *str, int number)
{
	int	i;
	int	count;
	int	start;

	i = 0;
	count = 0;
	start = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	start = i;
	while (str[i])
	{
		if (str[i] == ':')
		{
			if (count == number)
				return (copy_path(str, start, i));
			count++;
			i++;
			start = i;
		}
		else
			i++;
	}
	return (NULL);
}

void	add_cmd_path(t_cmd_element *ce, char **envp, int path_index)
{
	int	index;

	index = 0;
	ce->cmd_path = envp_split(envp, path_index);
	if (!ce->cmd_path)
	{
		free(ce);
		return ;
	}
}
