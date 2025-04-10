/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 00:35:22 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/11 00:53:52 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*tokenize(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_token	*new;

	tokens = NULL;
	while (*line)
	{
		if (is_space(*line))
			line++;
		else if (is_reserved(*line))
		{
			new = tokenize_reserved(&line);
			if (new)
				add_token(&tokens, new);
		}
		else
		{
			new = tokenize_word(&line, shell);
			if (new)
				add_token(&tokens, new);
		}
	}
	new = new_token(TK_EOF, "");
	if (new)
		add_token(&tokens, new);
	return (tokens);
}
