/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:19:17 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/13 04:33:34 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	option_check(char *str)
{
	int	i;

	if (!str || str[0] != '-')
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

int	check_special_option(char *arg, int *new_line)
{
	int	k;

	if (arg[0] != '-' || arg[1] != 'n')
		return (0);
	k = 2;
	while (arg[k] && arg[k] == 'n')
		k++;
	if (arg[k] && arg[k] == ' ')
	{
		*new_line = 0;
		printf("%s", &arg[k + 1]);
		return (1);
	}
	return (0);
}
int	buildin_echo(t_node *node)
{
	int	i;
	int	new_line;
	int	first_arg;

	if (!node->command[1])
		return (printf("\n"),0);
	i = 1;
	new_line = 1; 
	first_arg = 1;
	while (node->command[i] && option_check(node->command[i]))
	{
		new_line = 0; 
		i++;
	}
	while (node->command[i])
	{
		if (!first_arg)
			printf(" ");
		printf("%s", node->command[i]);
		first_arg = 0;
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
