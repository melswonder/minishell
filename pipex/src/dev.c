/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 19:14:09 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/21 19:27:48 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pip.h"

void	print_command(t_cmd_element *ce)
{
	int	i;
	int	j;

	printf("\n---DEBUG START---\n");
	j = 0;
	i = 0;
	while (ce->cmd[i] != NULL)
	{
		printf("[%d]", i);
		j = 0;
		while (ce->cmd[i][j] != NULL)
		{
			printf("\"%s\"", ce->cmd[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("command_count = %d\n", ce->command_count);
	printf("---DEBUG END---\n\n");
	return ;
}
