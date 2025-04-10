/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/10 22:13:21 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	redirect->filename = strdup(filename);
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
