/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:04:53 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/14 18:51:09 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

void	free_all_nodes(t_node *head)
{
	t_node	*current;
	t_node	*next;

	if (head == NULL)
		return ;
	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_node(current);
		current = next;
	}
}

void	free_node(t_node *node)
{
	int			i;
	t_redirect	*redirect;
	t_redirect	*next;

	if (node == NULL)
		return ;
	if (node->command != NULL)
	{
		i = 0;
		while (node->command[i] != NULL)
			free(node->command[i++]);
		free(node->command);
	}
	redirect = node->redirects;
	while (redirect != NULL)
	{
		next = redirect->next;
		if (redirect->filename != NULL)
			free(redirect->filename);
		free(redirect);
		redirect = next;
	}
	free(node);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->word);
		free(tmp);
	}
}
