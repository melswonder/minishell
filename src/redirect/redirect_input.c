/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:12:50 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/12 21:43:57 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_input_redirect(t_redirect *redirect)
{
	if (!redirect->filename)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (-1);
	}
	if (access(redirect->filename, F_OK) != 0)
	{
		write(2, "bash: ", 6);
		write(2, redirect->filename, strlen(redirect->filename));
		write(2, ": No such file or directory\n", 28);
		return (-1);
	}
	if (access(redirect->filename, R_OK) != 0)
	{
		write(2, "bash: ", 6);
		write(2, redirect->filename, strlen(redirect->filename));
		write(2, ": Permission denied\n", 20);
		return (-1);
	}
	return (open(redirect->filename, O_RDONLY));
}

void	child_redirect(t_redirect *redirect, int *pipe_fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(2, "warning: here-document at line 1 delimited by EOF\n", 50);
			break ;
		}
		if (strcmp(line, redirect->filename) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	exit(0);
}

int	open_heredoc_redirect(t_redirect *redirect)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (!redirect->filename)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (-1);
	}
	if (pipe(pipe_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
		child_redirect(redirect, pipe_fd);
	else if (pid > 0)
	{
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		return (pipe_fd[0]);
	}
	else
	{
		close(pipe_fd[0]);
		return (close(pipe_fd[1]), -1);
	}
	return(0);
}

int	input_heredoc_redirect(t_redirect *current, int *fd_in)
{
	if (current->kind == RD_INPUT)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = open_input_redirect(current);
	}
	else if (current->kind == RD_HEREDOC)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = open_heredoc_redirect(current);
	}
	return (0);
}
