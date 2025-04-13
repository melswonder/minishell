/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:25:28 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 03:13:13 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	unset_env(t_env **env, char *unset_key)
{
	t_env	*prev;
	t_env	*curr;

	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (strcmp(curr->key, unset_key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	buildin_unset(t_node *node, t_env **env)
{
	int	i;

	i = 1;
	if (node->command[i] == NULL)
		return (0);
	while (node->command[i] != NULL)
	{
		unset_env(env, node->command[i]);
		i++;
	}
	return (0);
}
