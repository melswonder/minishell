/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:22:06 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 03:09:22 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	set_to_env_value(t_env *env, char *key, char *set_value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(set_value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

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

int	buildin_cd(t_node *node, t_env *env)
{
	char	*dir;
	char	old_pwd[1024];
	char	current_pwd[1024];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		old_pwd[0] = '\0';
	if (node->command[1] == NULL)
		dir = get_home_path(env);
	else
		dir = node->command[1];
	if (chdir(dir) != 0 && dir != NULL)
	{
		if (elements_check(node->command) == 1)
			printf("bash: cd: too many arguments\n");
		else
			printf("bash: cd: %s: No such file or directory\n",
				node->command[1]);
		return (1);
	}
	if (old_pwd[0] != '\0')
		set_to_env_value(env, "OLDPWD", old_pwd);
	if (getcwd(current_pwd, sizeof(current_pwd)) != NULL)
		set_to_env_value(env, "PWD", current_pwd);
	return (0);
}
