/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:41:25 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/31 17:50:11 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// undefine ; | > ' "
//※ ''  "" ok

//	↓-- split--↓

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	char	*start;

	dest = (char *)malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	start = dest;
	while (*s)
	{
		*dest = *s;
		dest++;
		s++;
	}
	*dest = '\0';
	return (start);
}

int	quote_check(char *str, char quote)
{
	int	i;
	int	count;
	int	is_open;

	i = 0;
	count = 0;
	is_open = 0;
	while (str[i] != '\0')
	{
		if (str[i] == quote)
		{
			if (is_open)
			{
				count++;
				is_open = 0;
			}
			else
				is_open = 1;
		}
		i++;
	}
	if (is_open)
		return (-1);
	return (count);
}

int	argv_command_number(char *str)
{
	int	count;
	int	singl_count;
	int	double_count;

	count = 1;
	singl_count = quote_check(str, '\'');
	double_count = quote_check(str, '\"');
	if (singl_count == -1 || double_count == -1)
		return (-1);
	return (count);
}

char	**lexer(char *argv[])
{
	int		i;
	int		cmd_count;
	char	**cmd;

	cmd_count = 0;
	i = 0;
	while (argv[i] != NULL)
	{
		cmd_count += argv_command_number(argv[i]);
		i++;
	}
	cmd = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!cmd)
		return (NULL);
	i = 1;
	cmd_count = 0;
	while (argv[i] != NULL)
	{
		cmd[cmd_count] = ft_strdup(argv[i]);
		cmd_count++;
		i++;
	}
	cmd[cmd_count] = NULL;
	return (cmd);
}

void	cmd_print(char **cmd)
{
	int	i;

	printf("\n---DEBUG START---\n");
	i = 0;
	while (cmd[i] != NULL)
	{
		printf("[%d]", i);
		printf("%s", cmd[i]);
		printf("$");
		printf("\n");
		i++;
	}
	printf("---DEBUG END---\n\n");
	return ;
}
void	cmd_free(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

int	main(int argc, char *argv[])
{
	char **cmd;
	if (argc < 2)
		return (0);
	cmd = lexer(argv);
	cmd_print(cmd);
	cmd_free(cmd);
	return (0);
}
