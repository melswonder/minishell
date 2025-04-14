/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:22:06 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 21:32:58 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static int	buildin_error_print(t_node *node, char *dir)
{
	if (elements_check(node->command) == 1)
		printf("bash: cd: too many arguments\n");
	else
		printf("bash: cd: %s: No such file or directory\n", node->command[1]);
	if (dir != node->command[1] && dir != NULL)
		free(dir);
	return (1);
}

int	buildin_cd(t_node *node, t_env *env)
{
	char	*dir;
	char	old_pwd[1024];
	char	current_pwd[1024];
	char	*temp_dir;

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		old_pwd[0] = '\0';
	if (node->command[1] == NULL)
		dir = get_home_path(env);
	else if (node->command[1] && strncmp(node->command[1], "..", 2) == 0)
	{
		temp_dir = get_array_path(node->command[1], env);
		dir = temp_dir;
	}
	else
		dir = node->command[1];
	if (chdir(dir) != 0 && dir != NULL)
		return (buildin_error_print(node, dir));
	if (dir != node->command[1] && dir != get_home_path(env))
		free(dir);
	if (old_pwd[0] != '\0')
		set_to_env_value(env, "OLDPWD", old_pwd);
	if (getcwd(current_pwd, sizeof(current_pwd)) != NULL)
		set_to_env_value(env, "PWD", current_pwd);
	return (0);
}
