/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:11:22 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/11 01:12:35 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*parse_command_node(t_token **token_ptr, t_shell *shell)
{
	t_node	*node;
	t_token	*token;

	node = new_node();
	if (node == NULL)
		return (NULL);
	token = *token_ptr;
	token = handle_command(node, token);
	if (token == NULL)
	{
		free_node(node);
		return (NULL);
	}
	while (token != NULL && token->kind == TK_RESERVED)
	{
		if (strcmp(token->word, "|") == 0)
			break ;
		token = handle_redirect(node, token, shell);
		if (!token)
		{
			free_node(node);
			return (NULL);
		}
	}
	*token_ptr = token;
	return (node);
}
