/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:09:15 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/11 01:10:13 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_node	*parse_pipeline(t_token **token, t_shell *shell)
{
	t_node	*current;
	t_node	*head;
	t_node	*next_node;

	head = NULL;
	current = NULL;
	if (*token != NULL && strcmp((*token)->word, "|") == 0)
	{
		shell->syntax_error = true;
		return (NULL);
	}
	while (*token != NULL && (*token)->kind != TK_EOF)
	{
		next_node = parse_command_node(token, shell);
		if (next_node == NULL)
			return (head);
		if (head == NULL)
			head = next_node;
		else
			current->next = next_node;
		current = next_node;
		if (*token != NULL && strcmp((*token)->word, "|") == 0)
		{
			if ((*token)->next->word && \
					(strcmp((*token)->next->word, "|") == 0))
			{
				shell->syntax_error = true;
				return (head);
			}
			else if ((*token)->next->kind == TK_EOF)
			{
				shell->syntax_error = true;
				return (head);
			}
			*token = (*token)->next;
		}
	}
	shell->head = head;
	return (head);
}

t_node	*parse(t_token *tokens, t_shell *shell)
{
	if (!tokens || tokens->kind == TK_EOF)
	{
		return (NULL);
	}
	return (parse_pipeline(&tokens, shell));
}
