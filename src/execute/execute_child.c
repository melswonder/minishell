/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 02:57:12 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 13:15:00 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execute_single_child(t_shell *shell, int fd_in, int fd_out)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (fd_in != STDIN_FILENO)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out != STDOUT_FILENO)
		dup2(fd_out, STDOUT_FILENO);
	execute_normal(shell->head, shell->env);
}

void	setup_io_descriptors(int *local_fd_in,int *local_fd_out,int *pipe_out)
{
    if (*local_fd_out == STDOUT_FILENO && *pipe_out != STDOUT_FILENO)
    {
        dup2(*pipe_out, STDOUT_FILENO);
        close(*pipe_out);
    }
	else
	{
		if (*pipe_out != STDOUT_FILENO)
			close(*pipe_out);
	}
	if (*local_fd_in != STDIN_FILENO)
	{
		dup2(*local_fd_in, STDIN_FILENO);
		close(*local_fd_in);
	}
	if (*local_fd_out != STDOUT_FILENO)
	{
		dup2(*local_fd_out, STDOUT_FILENO);
		close(*local_fd_out);
	}	
}


void	execute_child_process(t_node *node, t_env *env, int fd_in, int *pipe_fd)
{
	int	local_fd_in;
	int	local_fd_out;
	int	pipe_out;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	local_fd_in = fd_in;
	local_fd_out = STDOUT_FILENO;
	pipe_out = STDOUT_FILENO;
	if (node->next)
	{
		close(pipe_fd[0]);
		pipe_out = pipe_fd[1];
	}
	setup_redirections(node->redirects, &local_fd_in, &local_fd_out);
	setup_io_descriptors(&local_fd_in,&local_fd_out,&pipe_out);
	if (is_builtin(node->command[0]))
		exit(execute_builtin_command(node, env));
	else
		execute_normal(node, env);
}

int	execute_single(t_shell *shell, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		execute_single_child(shell, fd_in, fd_out);
	else
	{
		waitpid(pid, &status, 0);
		if (wifexited(status))
			status = wexitstatus(status);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (status);
}
