/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:31:19 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 19:25:01 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execute_normal(t_node *node, t_env *env)
{
	char	**path;

	if (!node->command || !node->command[0])
	{
		write(2, "bash: command not found\n", 24);
		exit(EXIT_FAILURE);
	}
	if (node->command[0][0] == '/' || (node->command[0][0] == '.'
			&& node->command[0][1] == '/'))
	{
		execute_direct_path(node, env);
		exit(0);
	}
	path = create_path_array(env);
	search_command_in_path(node, env, path);
	write(2, node->command[0], strlen(node->command[0]));
	write(2, ": command not found", 19);
	write(2, "\n", 1);
	exit(127);
}

// リダイレクトを適用する
void	setup_redirections(t_redirect *redirect, int *local_fd_in,
		int *local_fd_out)
{
	while (redirect)
	{
		if (apply_redirections(redirect, local_fd_in, local_fd_out) != 0)
			exit(EXIT_FAILURE);
		redirect = redirect->next;
	}
}

pid_t	execute_pipeline_node(t_node *node, t_env *env, int fd_in,
		int *pipe_read_fd)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (node->next && pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (node->next)
			execute_child_process(node, env, fd_in, pipe_fd);
		else
			execute_child_process(node, env, fd_in, pipe_read_fd);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (node->next)
	{
		close(pipe_fd[1]);
		*pipe_read_fd = pipe_fd[0];
	}
	return (pid);
}

int	execute_pipeline(t_shell *shell)
{
	pid_t	pid;
	t_node	*current;
	int		pipe_read_fd;

	current = shell->head;
	pipe_read_fd = STDIN_FILENO;
	while (current)
	{
		pid = execute_pipeline_node(current, shell->env, pipe_read_fd,
				&pipe_read_fd);
		current = current->next;
	}
	while (waitpid(pid, &shell->status, 0) > 0)
	{
		if (wifexited(shell->status))
			shell->status = wexitstatus(shell->status);
	}
	return (EXIT_SUCCESS);
}

int	execute(t_shell *shell)
{
	int			fd_in;
	int			fd_out;
	t_redirect	*current;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (shell->head->next != NULL)
		return (execute_pipeline(shell), EXIT_SUCCESS);
	current = shell->head->redirects;
	while (current != NULL)
	{
		if (apply_redirections(current, &fd_in, &fd_out) != 0)
			return (EXIT_FAILURE);
		current = current->next;
	}
	if (shell->head->command && shell->head->command[0])
	{
		if (is_builtin(shell->head->command[0]))
			execute_builtin_with_redirect(shell, &fd_in, &fd_out);
		else
			execute_single(shell, fd_in, fd_out);
	}
	return (EXIT_SUCCESS);
}
