/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:09:15 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/14 02:30:03 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static bool	check_pipeline_start(t_token **token, t_shell *shell)
{
	if (*token != NULL && ft_strncmp((*token)->word, "|", 1) == 0)
	{
		shell->syntax_error = true;
		return (true);
	}
	return (false);
}

static t_node	*parse_command(t_token **token, t_shell *shell)
{
	t_node	*next_node;

	next_node = parse_command_node(token, shell);
	if (next_node == NULL)
		return (NULL);
	return (next_node);
}

static bool	check_and_advance_pipeline_token(t_token **token, t_shell *shell)
{
	if (*token != NULL && ft_strncmp((*token)->word, "|", 1) == 0)
	{
		if ((*token)->next->word && \
			ft_strncmp((*token)->next->word, "|", 1) == 0)
		{
			shell->syntax_error = true;
			return (true);
		}
		else if ((*token)->next->kind == TK_EOF)
		{
			shell->syntax_error = true;
			return (true);
		}
		*token = (*token)->next;
	}
	return (false);
}

static t_node	*parse_pipeline(t_token **token, t_shell *shell)
{
	t_node	*current;
	t_node	*head;
	t_node	*next_node;

	current = NULL;
	head = NULL;
	if (check_pipeline_start(token, shell))
		return (NULL);
	while (*token != NULL && (*token)->kind != TK_EOF)
	{
		if (*token != NULL && (*token)->kind == TK_RESERVED && head == NULL)
			next_node = create_redirect_node(token, shell);
		else
			next_node = parse_command(token, shell);
		if (next_node == NULL)
			return (head);
		if (head == NULL)
			head = next_node;
		else
			current->next = next_node;
		current = next_node;
		if (check_and_advance_pipeline_token(token, shell))
			return (head);
	}
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
