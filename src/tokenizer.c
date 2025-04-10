/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/10 22:13:33 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*new_token(t_token_kind kind, char *word)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->kind = kind;
	token->word = strdup(word);
	if (!token->word)
	{
		free(token);
		return (NULL);
	}
	token->next = NULL;
	return (token);
}

static void	add_token(t_token **tokens, t_token *new)
{
	t_token	*last;

	if (!*tokens)
	{
		*tokens = new;
		return ;
	}
	last = *tokens;
	while (last->next)
		last = last->next;
	last->next = new;
}

static int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

static int	is_reserved(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static t_token	*tokenize_reserved(char **line)
{
	t_token	*token;
	char	word[3];

	word[0] = **line;
	word[1] = '\0';
	word[2] = '\0';
	(*line)++;
	if ((**line == '<' && word[0] == '<') || (**line == '>' && word[0] == '>'))
	{
		word[1] = **line;
		(*line)++;
	}
	token = new_token(TK_RESERVED, word);
	return (token);
}

static char	*extract_word(char **line, t_shell *shell)
{
	char	*start;
	char	quote;
	int		len;
	char	*word;

	start = *line;
	quote = '\0';
	while (**line && (quote || (!is_space(**line) && !is_reserved(**line))))
	{
		if (**line == '\'' || **line == '\"')
		{
			if (!quote)
				quote = **line;
			else if (quote == **line)
				quote = '\0';
		}
		(*line)++;
	}
	len = *line - start;
	if (len == 0)
		return (NULL);
	if (quote != '\0')
		shell->syntax_error = true;
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	strncpy(word, start, len);
	word[len] = '\0';
	return (word);
}

static t_token	*tokenize_word(char **line, t_shell *shell)
{
	t_token	*token;
	char	*word;

	word = extract_word(line, shell);
	if (!word)
		return (NULL);
	token = new_token(TK_WORD, word);
	free(word);
	return (token);
}

t_token	*tokenize(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_token	*new;

	tokens = NULL;
	while (*line)
	{
		if (is_space(*line))
		{
			line++;
			continue ;
		}
		if (is_reserved(*line))
		{
			new = tokenize_reserved(&line);
			if (new)
				add_token(&tokens, new);
			continue ;
		}
		new = tokenize_word(&line, shell);
		if (new)
			add_token(&tokens, new);
	}
	new = new_token(TK_EOF, "");
	if (new)
		add_token(&tokens, new);
	return (tokens);
}

