/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:30:14 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 21:32:57 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_home_path(t_env *env)
{
	char	*home;
	char	*dir;

	home = ft_getenv("HOME", env);
	if (home == NULL)
	{
		printf("bash: cd: HOME not set\n");
		return (NULL);
	}
	dir = home;
	return (dir);
}

char	*ft_getenv(char *str, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(str, tmp->key, ft_strlen(tmp->key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	elements_check(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	if (i > 2)
		return (1);
	return (0);
}

char	*get_array_path(char *str, t_env *env)
{
	char	*dir;
	char	*pwd;
	char	*last_slash;

	if (strncmp(str, "..", ft_strlen(str)) == 0)
	{
		pwd = ft_getenv("PWD", env);
		if (pwd == NULL)
			return (str);
		dir = ft_strdup(pwd);
		if (dir == NULL)
			return (str);
		last_slash = ft_strrchr(dir, '/');
		if (last_slash == dir)
			*(last_slash + 1) = '\0';
		else
			*last_slash = '\0';
		return (dir);
	}
	return (str);
}
