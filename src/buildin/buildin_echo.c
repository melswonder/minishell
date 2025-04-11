/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:19:17 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/11 13:19:27 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	option_check(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[i] != '-')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

int	buildin_echo(t_node *node)
{
	int	i;
	int	var_pos;
	int	new_line;

	i = 1;
	new_line = 1;
	if (option_check(node->command[1]))
	{
		new_line = 0;
		i++;
	}
	while (node->command[i] != NULL)
	{
		printf("%s", node->command[i]);
		if (node->command[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
