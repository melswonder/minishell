/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:19:17 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/11 16:34:15 by hirwatan         ###   ########.fr       */
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

int	option_check_print(t_node *node, int new_line, int *i_ptr)
{
	if (option_check(node->command[1]))
	{
		new_line = 0;
		(*i_ptr)++;
	}
	else if (check_special_option(node->command[1], &new_line))
	{
		if (node->command[2])
			printf(" ");
		(*i_ptr)++;
	}
	else
		printf("%s", node->command[*i_ptr]);
	return (new_line);
}

int	buildin_echo(t_node *node)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (node->command[1])
	{
		new_line = option_check_print(node, new_line, &i);
		if (i == 1)
			i++;
	}
	while (node->command[i])
	{
		printf("%s", node->command[i]);
		if (node->command[i + 1])
			printf(" ");
		i++;
	}
	if (new_line)
		printf("\n");
	return (0);
}
