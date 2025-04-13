/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 21:16:10 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 03:19:56 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**create_path_array(t_env *env)
{
	char	**path;

	path = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", ft_strlen(env->key)) == 0)
			path = split_path_env(env->value);
		env = env->next;
	}
	if (!path)
		return (NULL);
	return (path);
}

void	print_is_directory(char *str)
{
	write(2, "bash: ", 6);
	write(2, str, strlen(str));
	write(2, ": Is a directory\n", 17);
	exit(126);
}

void	execute_direct_path(t_node *node, t_env *env)
{
	char	**envp;

	envp = convert_env_to_array(env);
	if (execve(node->command[0], node->command, envp) == -1)
	{
		if (is_directry(node->command[0]))
			print_is_directory(node->command[0]);
		else if (access(node->command[0], F_OK) != 0)
		{
			write(2, "bash:  ", 7);
			write(2, node->command[0], strlen(node->command[0]));
			write(2, ":  No such file or directory\n", 29);
		}
		else if (access(node->command[0], X_OK) != 0)
		{
			write(2, "bash:", 5);
			write(2, node->command[0], strlen(node->command[0]));
			write(2, "Permission denied\n", 18);
		}
		free_env_array(envp);
	}
	free_env_array(envp);
}

void	search_command_in_path(t_node *node, t_env *env, char **path)
{
	int		i;
	char	*cmd_path;
	char	**envp;

	i = 0;
	envp = convert_env_to_array(env);
	while (path && path[i])
	{
		cmd_path = join_three_strings(path[i], "/", node->command[0]);
		if (!cmd_path)
		{
			i++;
			continue ;
		}
		if (access(cmd_path, X_OK) == 0)
			execve(cmd_path, node->command, envp);
		free(cmd_path);
		i++;
	}
	if (path)
		free_path_array(path);
	if (envp)
		free_env_array(envp);
}
