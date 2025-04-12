/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:58:15 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/12 21:08:01 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(char *str)
{
	if (!str)
		return (0);
	if (strcmp(str, "echo") == 0)
		return (1);
	else if (strcmp(str, "exit") == 0)
		return (1);
	else if (strcmp(str, "cd") == 0)
		return (1);
	else if (strcmp(str, "pwd") == 0)
		return (1);
	else if (strcmp(str, "export") == 0)
		return (1);
	else if (strcmp(str, "unset") == 0)
		return (1);
	else if (strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int	execute_builtin_command(t_node *node, t_env *env)
{
	char	*cmd;

	cmd = node->command[0];
	if (strcmp(cmd, "echo") == 0)
		return (buildin_echo(node));
	else if (strcmp(cmd, "exit") == 0)
		return (buildin_exit(node));
	else if (strcmp(cmd, "cd") == 0)
		return (buildin_cd(node, env));
	else if (strcmp(cmd, "pwd") == 0)
		return (buildin_pwd());
	else if (strcmp(cmd, "export") == 0)
		return (buildin_export(node, env));
	else if (strcmp(cmd, "unset") == 0)
		return (buildin_unset(node, &env));
	else if (strcmp(cmd, "env") == 0)
		return (buildin_env(env));
	return (1);
}

int	execute_builtin_with_redirect(t_shell *shell, int *fd_in, int *fd_out)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (*fd_in != STDIN_FILENO)
		dup2(*fd_in, STDIN_FILENO);
	if (*fd_out != STDOUT_FILENO)
		dup2(*fd_out, STDOUT_FILENO);
	execute_builtin_command(shell->head, shell->env);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	if (*fd_in != STDIN_FILENO)
	{
		close(*fd_in);
		*fd_in = STDIN_FILENO;
	}
	if (*fd_out != STDOUT_FILENO)
	{
		close(*fd_out);
		*fd_out = STDOUT_FILENO;
	}
	return (0);
}
