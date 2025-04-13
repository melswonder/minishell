/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:20:50 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/14 01:27:36 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*new_node(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->command = NULL;
	node->redirects = NULL;
	node->next = NULL;
	return (node);
}

t_redirect	*new_redirect(t_redirect_kind kind, char *filename)
{
	t_redirect	*redirect;

	redirect = malloc(sizeof(t_redirect));
	if (redirect == NULL)
		return (NULL);
	redirect->kind = kind;
	redirect->filename = (filename);
	if (redirect->filename == NULL)
	{
		free(redirect);
		return (NULL);
	}
	redirect->next = NULL;
	return (redirect);
}

void	add_redirect_to_node(t_node *node, t_redirect *redirect)
{
	t_redirect	*current;

	if (node->redirects == NULL)
	{
		node->redirects = redirect;
		return ;
	}
	current = node->redirects;
	while (current->next != NULL)
		current = current->next;
	current->next = redirect;
}
