/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:42:37 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/14 02:56:41 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*tokenize_word(char **line, t_shell *shell)
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

static char	*get_word_end(char *line, char *quote)
{
	while (*line && (*quote || (!is_space(*line) && !is_reserved(*line))))
	{
		if (*line == '\'' || *line == '\"')
		{
			if (!*quote)
				*quote = *line;
			else if (*quote == *line)
				*quote = '\0';
		}
		line++;
	}
	return (line);
}

static char	*copy_word(const char *start, int len)
{
	char	*word;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	word[len] = '\0';
	return (word);
}

char	*extract_word(char **line, t_shell *shell)
{
	char	*start;
	char	*end;
	char	quote;
	int		len;
	char	*word;

	start = *line;
	quote = '\0';
	end = get_word_end(*line, &quote);
	len = end - start;
	if (len == 0)
		return (NULL);
	if (quote != '\0')
		shell->syntax_error = true;
	word = copy_word(start, len);
	if (!word)
		return (NULL);
	*line = end;
	return (word);
}
