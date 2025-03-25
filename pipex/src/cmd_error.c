/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:00:56 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/25 13:19:49 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pip.h"

void	cmd_error(t_cmd_element *ce, int cmd_number)
{
	if (ce->cmd[cmd_number][0][0] == '/' || ce->cmd[cmd_number][0][0] == '.'
		&& ce->cmd[cmd_number][0][1] == '/')
	{
		write(2, "bash:", 6);
		write(2, ce->cmd[cmd_number][0], ft_strlen(ce->cmd[cmd_number][0]));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, ce->cmd[cmd_number][0], ft_strlen(ce->cmd[cmd_number][0]));
		write(2, ": command not found\n", 20);
	}
	free_ce(ce);
	exit(127);
}

void	execute_path_or_executable_file(t_cmd_element *ce, int cmd_number)
{
	if (ce->cmd[cmd_number][0][0] == '/')
	{
		if (execve(ce->cmd[cmd_number][0], ce->cmd[cmd_number], NULL) == -1)
		{
			cmd_error(ce, cmd_number);
		}
	}
	else
	{
		if (execve(ce->cmd[cmd_number][0], ce->cmd[cmd_number], NULL) == -1)
		{
			execute_file_error(ce, cmd_number);
		}
	}
	return ;
}

void	ft_error(int error_number)
{
	if (error_number == DUP_ERROR)
		perror("dup2");
	else if (error_number == OPEN_ERROR)
		perror("open");
	else if (error_number == PIPE_ERROR)
		perror("pipe");
	else if (error_number == FORK_ERROR)
		perror("fork");
	else if (error_number == EXECUTE_ERROR)
		perror("execute");
	else
		perror("WTF_ERROR");
	exit(EXIT_FAILURE);
}

void	execute_file_error(t_cmd_element *ce, int cmd_number)
{
	write(2, "bash:", 6);
	write(2, ce->cmd[cmd_number][0], ft_strlen(ce->cmd[cmd_number][0]));
	write(2, ": No such file or directory\n", 29);
	free_ce(ce);
	exit(127);
}

void	ft_infile_error(int pipefd[2])
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(1);
}
