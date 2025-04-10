/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:19:43 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/11 01:20:20 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*handle_redirect(t_node *node, t_token *token, t_shell *shell)
{
	t_redirect_kind	kind;
	t_redirect		*redirect;

	if (strcmp(token->word, "<") == 0)
		kind = RD_INPUT;
	else if (strcmp(token->word, ">") == 0)
		kind = RD_OUTPUT;
	else if (strcmp(token->word, ">>") == 0)
		kind = RD_APPEND;
	else if (strcmp(token->word, "<<") == 0)
		kind = RD_HEREDOC;
	else if (strcmp(token->word, "|") == 0)
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
