/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/06 00:38:50 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*new_node()
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

t_token	*handle_redirect(t_node *node, t_token *token)
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
	{
		if (token->next)
			return (token->next);
		return (token);
	}
	token = token->next;
	if (!token || token->kind != TK_WORD)
		return (NULL);
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
	char 	**command;
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
	int	 count;
	char **command;

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

void	free_node(t_node *node)
{
	int			i;
	t_redirect	*redirect;
	t_redirect	*next;

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
		free(redirect->filename);
		free(redirect);
		redirect = next;
	}
	free(node);
}

t_node	*parse_command_node(t_token **token_ptr)
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
		token = handle_redirect(node, token);
		if (!token)
		{
			free_node(node);
			return (NULL);
		}
	}
	*token_ptr = token;
	return (node);
}

void	free_all_nodes(t_node *head)
{
	t_node	*current;
	t_node	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free_node(current);
		current = next;
	}
}

static t_node	*parse_pipeline(t_token **token)
{
	t_node	*current;
	t_node	*head;
	t_node	*next_node;

	head = NULL;
	current = NULL;
	while (*token != NULL && (*token)->kind != TK_EOF)
	{
		next_node = parse_command_node(token);
		if (next_node == NULL)
		{
			free_all_nodes(head);
			return (NULL);
		}
		if (head == NULL)
			head = next_node;
		else
			current->next = next_node;
		current = next_node;
		if (*token != NULL && strcmp((*token)->word, "|") == 0)
			*token = (*token)->next;
	}
	return (head);
}


t_node	*parse(t_token *tokens)
{
	if (!tokens || tokens->kind == TK_EOF)
	{
		// executorの処理によって戻り値、freeを考える
		return (NULL);
	}
	return (parse_pipeline(&tokens));
}
