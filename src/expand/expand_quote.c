/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:57:10 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/12 03:18:35 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	append_single_quote(char **dst, char **rest, char *p)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		p ++;
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				printf("Unclosed single quote");
			append_char(dst, *p++);
		}
		p ++;
		*rest = p;
	}
	else
		printf("Expected single quote");
}

void	append_double_quote(char **dst, char **rest, char *p, t_shell *shell)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		p++;
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				printf("Unclosed double quote");
			else if (is_variable(p))
				expand_variable_str(dst, &p, p, shell);
			else if (is_special_parameter(p))
				expand_special_parameter_str(dst, &p, p, shell);
			else
				append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		printf("Expected double quote");
}

char	*expand_string(t_shell *shell, char *word)
{
	char	*new_word;
	char	*p;

	if (word == NULL)
		return (NULL);
	p = word;
	new_word = calloc(1, sizeof(char));
	if (new_word == NULL)
		printf("calloc");
	while (*p && !is_metacharacter(*p))
	{
		if (*p == SINGLE_QUOTE_CHAR)
			append_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			append_double_quote(&new_word, &p, p, shell);
		else if (is_variable(p))
			expand_variable_str(&new_word, &p, p, shell);
		else if (is_special_parameter(p))
			expand_special_parameter_str(&new_word, &p, p, shell);
		else
			append_char(&new_word, *p++);
	}
	return (new_word);
}
