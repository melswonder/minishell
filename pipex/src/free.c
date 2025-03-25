/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:13:11 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/21 19:27:48 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pip.h"

void	free_token_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_ce(t_cmd_element *ce)
{
	int	i;

	i = 0;
	while (ce->cmd[i] != NULL)
	{
		free_token_array(ce->cmd[i]);
		i++;
	}
	free(ce->cmd);
	i = 0;
	if (ce->cmd_path)
	{
		while (ce->cmd_path[i] != NULL)
		{
			free(ce->cmd_path[i]);
			i++;
		}
	}
	free(ce->cmd_path);
	free(ce);
}
