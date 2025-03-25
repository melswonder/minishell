/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:36:13 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/21 19:21:04 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pip.h"

int	countwords(char *str)
{
	size_t	i;
	int		count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ':')
			count++;
		i++;
	}
	count++;
	return (count);
}

t_cmd_element	*argv_to_exec_args(int argc, char *argv[], char *envp[])
{
	t_cmd_element	*ce;
	int				i;

	ce = (t_cmd_element *)malloc(sizeof(t_cmd_element));
	if (!ce)
		return (NULL);
	ce->cmd = (char ***)malloc(sizeof(char **) * (argc));
	if (!ce->cmd)
	{
		free(ce);
		return (NULL);
	}
	i = 0;
	while (i < argc - 1)
	{
		ce->cmd[i] = ft_split(argv[i + 1], ' ');
		i++;
	}
	ce->command_count = i;
	ce->cmd[i] = NULL;
	path_new(ce, envp);
	return (ce);
}

void	main_command_execution(t_cmd_element *ce, char **envp)
{
	int	input_fd;
	int	pipefd[2];
	int	i;

	input_fd = execute_first_command(ce, envp, (int [2]){0}, 1);
	i = 2;
	while (i < ce->command_count - 2)
	{
		input_fd = execute_middle_command(ce, envp, i, input_fd);
		i++;
	}
	execute_last_command(ce, envp, input_fd, ce->command_count - 2);
	if (exit_check_unset_path(ce))
	{
		free_ce(ce);
		exit(127);
	}
	return ;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_cmd_element	*ce;
	int				i;

	i = 0;
	if (argc < 2)
		return (0);
	ce = argv_to_exec_args(argc, argv, envp);
	data_validation_check(ce);
	check_file_permissions_exist(ce);
	main_command_execution(ce, envp);
	free_ce(ce);
	return (0);
}
