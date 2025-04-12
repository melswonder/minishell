/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:48:57 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/12 21:02:41 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_output_redirect(t_redirect *redirect)
{
	int	fd;

	if (!redirect->filename)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (-1);
	}
	if (access(redirect->filename, F_OK) == 0 && access(redirect->filename,
			W_OK) != 0)
	{
		write(2, "bash: ", 6);
		write(2, redirect->filename, strlen(redirect->filename));
		write(2, ": Permission denied\n", 20);
		return (-1);
	}
	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("bash");
		return (-1);
	}
	return (fd);
}

int	open_append_redirect(t_redirect *redirect)
{
	int	fd;

	if (!redirect->filename)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (-1);
	}
	if (access(redirect->filename, F_OK) == 0 && access(redirect->filename,
			W_OK) != 0)
	{
		write(2, "bash: ", 6);
		write(2, redirect->filename, strlen(redirect->filename));
		write(2, ": Permission denied\n", 20);
		return (-1);
	}
	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("bash");
		return (-1);
	}
	return (fd);
}

int	output_append_redirect(t_redirect *current, int *fd_out)
{
	if (current->kind == RD_OUTPUT)
	{
		if (*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out = open_output_redirect(current);
	}
	else if (current->kind == RD_APPEND)
	{
		if (*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out = open_append_redirect(current);
	}
	return (0);
}
