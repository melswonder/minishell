/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:19:50 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/11 13:21:33 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoull(const char *str, unsigned long long *result)
{
	unsigned long long	res;
	int					i;
	unsigned long long	prev;

	res = 0;
	i = 0;
	while (isspace(str[i]))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = res;
		res = res * 10 + (str[i] - '0');
		if (res < prev)
		{
			*result = 0;
			return (0);
		}
		i++;
	}
	if (str[i] != '\0')
		return (0);
	*result = res;
	return (1);
}

static char	*extract_arg(char *line, int *index)
{
	char	buffer[1024];
	int		i;
	int		j;

	i = *index;
	j = 0;
	while (line[i] != '\0' && line[i] != ' ')
		buffer[j++] = line[i++];
	buffer[j] = '\0';
	*index = i;
	return (strdup(buffer));
}

int	is_valid_number(char *arg, unsigned long long *num)
{
	char	*num_start;
	int		sign_present;

	num_start = arg;
	sign_present = 0;
	if (*num_start == '-' || *num_start == '+')
	{
		sign_present = 1;
		num_start++;
	}
	if (!is_numeric(arg))
		return (0);
	if (!ft_atoull(num_start, num))
		return (0);
	if (sign_present && *num_start == '\0')
		return (0);
	return (1);
}

int	buildin_exit(t_node *node)
{
	char				*arg;
	unsigned long long	num;
	int					i;

	i = 0;
	printf("exit\n");
	if (node->command[1] == NULL)
		exit(0);
	arg = extract_arg(node->command[1], &i);
	if (!is_valid_number(arg, &num))
	{
		printf("bash: exit: %s: numeric argument required\n", arg);
		free(arg);
		exit(2);
	}
	if (node->command[2] != NULL)
	{
		free(arg);
		return (printf("bash: exit: too many arguments\n"), 1);
	}
	if (arg[0] == '-')
		exit(256 - (num % 256) % 256);
	else
		exit(num % 256);
	return (0);
}
