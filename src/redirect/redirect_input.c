/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:12:50 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 21:35:02 by hirwatan         ###   ########.fr       */
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
		write(2, redirect->filename, ft_strlen(redirect->filename));
		write(2, ": No such file or directory\n", 28);
		return (-1);
	}
	if (access(redirect->filename, R_OK) != 0)
	{
		write(2, "bash: ", 6);
		write(2, redirect->filename, ft_strlen(redirect->filename));
		write(2, ": Permission denied\n", 20);
		return (-1);
	}
	return (open(redirect->filename, O_RDONLY));
}

void	heredoc_eof_error(char *name, int i)
{
	char	*num_str;

	write(2, "bash: warning: here-document at line ", 37);
	num_str = ft_itoa(i);
	if (num_str)
	{
		write(2, num_str, ft_n_len(i));
		free(num_str);
	}
	write(2, " delimited by end-of-file (wanted `", 35);
	write(2, name, strlen(name));
	write(2, "')\n", 3);
}

void	child_redirect(t_redirect *redirect, int *pipe_fd)
{
	char		*line;
	static int	i = 1;

	// signal(SIGINT, SIG_DFL);
	signal(SIGINT, signal_handler_exit);
	close(pipe_fd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			heredoc_eof_error(redirect->filename, i);
			break ;
		}
		if (ft_strcmp(line, redirect->filename) == 0)
		{
			free(line);
			break ;
		}
		i++;
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	exit(close(pipe_fd[1]));
}

int	open_heredoc_redirect(t_redirect *redirect)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		status;

	if (!redirect->filename)
		return (write(2, "syntax error near unexpected token `newline'\n", 45),
			-1);
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
	return (0);
}

int	input_heredoc_redirect(t_redirect *current, int *fd_in)
{
	int	fd;

	fd = -1;
	if (current->kind == RD_INPUT)
		fd = open_input_redirect(current);
	else if (current->kind == RD_HEREDOC)
		fd = open_heredoc_redirect(current);
	if (fd != -1)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = fd;
	}
	if (fd == -1)
		return (-1);
	return (0);
}
