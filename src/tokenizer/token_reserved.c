/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_reserved.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:40:35 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/11 00:41:59 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_reserved(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token	*tokenize_reserved(char **line)
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
