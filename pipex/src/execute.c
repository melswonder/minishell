/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:55:19 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/25 13:19:43 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pip.h"

int	execute_first_command(t_cmd_element *ce, char **envp, int pipefd[2],
		int cmd_index)
{
	int		infile_fd;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		ft_error(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
		ft_error(FORK_ERROR);
	if (pid == 0)
	{
		infile_fd = open(ce->cmd[0][0], O_RDONLY);
		if (infile_fd < 0)
			ft_infile_error(pipefd);
		if (dup2(infile_fd, STDIN_FILENO) == -1)
			ft_error(DUP_ERROR);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			ft_error(DUP_ERROR);
		close(infile_fd);
		close(pipefd[0]);
		close(pipefd[1]);
		command_execution(ce, envp, cmd_index);
		ft_error(EXECUTE_ERROR);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

int	execute_middle_command(t_cmd_element *ce, char **envp, int cmd_index,
		int input_fd)
{
	int		curr_pipe[2];
	pid_t	pid;

	if (pipe(curr_pipe) == -1)
		ft_error(PIPE_ERROR);
	pid = fork();
	if (pid == -1)
		ft_error(FORK_ERROR);
	if (pid == 0)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			ft_error(DUP_ERROR);
		if (dup2(curr_pipe[1], STDOUT_FILENO) == -1)
			ft_error(DUP_ERROR);
		close(curr_pipe[0]);
		close(curr_pipe[1]);
		command_execution(ce, envp, cmd_index);
		ft_error(EXECUTE_ERROR);
	}
	close(input_fd);
	close(curr_pipe[1]);
	return (curr_pipe[0]);
}

void	execute_last_command(t_cmd_element *ce, char **envp, int input_fd,
		int cmd_index)
{
	int		outfile_fd;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error(FORK_ERROR);
	if (pid == 0)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			ft_error(DUP_ERROR);
		outfile_fd = open(ce->cmd[ce->command_count - 1][0],
				O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (outfile_fd < 0)
			ft_error(OPEN_ERROR);
		if (dup2(outfile_fd, STDOUT_FILENO) == -1)
			ft_error(DUP_ERROR);
		close(outfile_fd);
		close(input_fd);
		command_execution(ce, envp, cmd_index);
	}
	close(input_fd);
	waitpid(pid, NULL, 0);
}

void	command_execution(t_cmd_element *ce, char **envp, int cmd_number)
{
	if (ce->cmd[cmd_number][0][0] == '/' || (ce->cmd[cmd_number][0][0] == '.'
			&& ce->cmd[cmd_number][0][1] == '/'))
	{
		execute_path_or_executable_file(ce, cmd_number);
		return ;
	}
	else
	{
		if (normal_execution(ce, cmd_number, envp))
			return ;
	}
	if (ce->cmd_path == NULL)
		unset_path_error(ce, cmd_number);
	cmd_error(ce, cmd_number);
}

int	normal_execution(t_cmd_element *ce, int cmd_number, char **envp)
{
	int		i;
	char	*cmd_with_slash;
	char	*full_path;

	i = 0;
	if (!ce->cmd_path)
		return (0);
	while (ce->cmd_path[i] != NULL)
	{
		cmd_with_slash = ft_strjoin("/", ce->cmd[cmd_number][0]);
		full_path = ft_strjoin(ce->cmd_path[i], cmd_with_slash);
		free(cmd_with_slash);
		if (execve(full_path, ce->cmd[cmd_number], envp) == -1)
		{
			free(full_path);
			i++;
		}
		else
		{
			free(full_path);
			return (1);
		}
	}
	return (0);
}
