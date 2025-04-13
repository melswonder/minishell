/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:19:43 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/14 02:06:54 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*handle_redirect(t_node *node, t_token *token, t_shell *shell)
{
	t_redirect_kind	kind;
	t_redirect		*redirect;

	if (ft_strncmp(token->word, "<", 1) == 0)
		kind = RD_INPUT;
	else if (ft_strncmp(token->word, ">", 1) == 0)
		kind = RD_OUTPUT;
	else if (ft_strncmp(token->word, ">>", 2) == 0)
		kind = RD_APPEND;
	else if (ft_strncmp(token->word, "<<", 2) == 0)
		kind = RD_HEREDOC;
	else if (ft_strncmp(token->word, "|", 1) == 0)
		return (token);
	token = token->next;
	if (!token || token->kind != TK_WORD)
	{
		shell->syntax_error = true;
		return (NULL);
	}
	redirect = new_redirect(kind, token->word);
	if (redirect == NULL)
		return (NULL);
	add_redirect_to_node(node, redirect);
	return (token->next);
}

t_node	*create_redirect_node(t_token **token_ptr, t_shell *shell)
{
	t_node	*node;
	t_token	*token;

	node = new_node();
	if (node == NULL)
		return (NULL);
	token = *token_ptr;
	token = handle_redirects(node, token, shell);
	token = handle_command(node, token);
	if (token == NULL)
	{
		free_node(node);
		return (NULL);
	}
	token = handle_redirects(node, token, shell);
	*token_ptr = token;
	return (node);
}
