/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetpath_permission_error.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:03:40 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/25 13:02:18 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pip.h"

void	check_file_permissions_exist(t_cmd_element *ce)
{
	if (access(ce->cmd[0][0], F_OK) == -1)
	{
		printf("bash: %s: No such file or directory\n", ce->cmd[0][0]);
	}
	if (access(ce->cmd[0][0], R_OK) == -1)
	{
		printf("bash: %s: Permission denied\n", ce->cmd[0][0]);
	}
}

void	data_validation_check(t_cmd_element *ce)
{
	if (ce->command_count < 4)
	{
		printf("Description Error: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
		free_ce(ce);
		exit(EXIT_FAILURE);
	}
}

int	exit_check_unset_path(t_cmd_element *ce)
{
	if (!ce->cmd_path)
		return (1);
	return (0);
}

void	unset_path_error(t_cmd_element *ce, int cmd_number)
{
	write(2, "bash: ", 6);
	write(2, ce->cmd[cmd_number][0], ft_strlen(ce->cmd[cmd_number][0]));
	write(2, ": No such file or directory\n", 28);
	free_ce(ce);
	exit(127);
}
