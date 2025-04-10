/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:42:37 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/11 00:44:13 by kiwasa           ###   ########.fr       */
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

char	*extract_word(char **line, t_shell *shell)
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
