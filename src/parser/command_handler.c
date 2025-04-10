/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:14:09 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/11 01:18:23 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_command_words(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->kind == TK_WORD)
	{
		count ++;
		token = token->next;
	}
	return (count);
}

char	**create_command_array(t_token *token, int count)
{
	char	**command;
	int		i;

	i = 0;
	command = malloc(sizeof(char *) * (count + 1));
	if (!command)
		return (NULL);
	while (i < count)
	{
		command[i] = strdup(token->word);
		if (command[i] == NULL)
		{
			while (--i > 0)
			{
				free(command[i]);
			}
			free(command);
			return (NULL);
		}
		token = token->next;
		i ++;
	}
	command[count] = NULL;
	return (command);
}

t_token	*handle_command(t_node	*node, t_token *token)
{
	int		count;
	char	**command;

	count = count_command_words(token);
	if (!count)
		return (token);
	command = create_command_array(token, count);
	if (command == NULL)
		return (NULL);
	node->command = command;
	while (count > 0)
	{
		token = token->next;
		count --;
	}
	return (token);
}
