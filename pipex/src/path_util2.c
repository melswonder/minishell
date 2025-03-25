/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_util2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:19:00 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/21 19:27:48 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pip.h"

void	path_new(t_cmd_element *ce, char **envp)
{
	int	path_index;

	path_index = sarch_path_index(envp, ce);
	if (path_index == -1)
	{
		ce->cmd_path = NULL;
		return ;
	}
	add_cmd_path(ce, envp, path_index);
	return ;
}

int	sarch_path_index(char *envp[], t_cmd_element *ce)
{
	char	**cmd_path;
	int		i;
	int		flg;

	flg = 0;
	cmd_path = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strstr(envp[i], "PATH="))
		{
			flg = 1;
			break ;
		}
		i++;
	}
	if (!flg)
		return (-1);
	return (i);
}
