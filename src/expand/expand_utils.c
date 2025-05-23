/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:33:48 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/14 01:12:17 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_alpha_under(char c)
{
	return (ft_isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}

void	append_char(char **dst, char c)
{
	size_t	len;
	char	*new;

	len = ft_strlen(*dst);
	new = ft_calloc(len + 2, sizeof(char));
	if (new == NULL)
		printf("calloc");
	ft_strlcpy(new, *dst, len + 1);
	new[len] = c;
	new[len + 1] = '\0';
	free(*dst);
	*dst = new;
}

bool	is_metacharacter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '|' || c == '<' || c == '>');
}
