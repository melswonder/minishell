/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:49:44 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/15 19:55:34 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_special_parameter(char *s)
{
	return (s[0] == '$' && s[1] == '?');
}

void	expand_special_parameter_str(char **dst, char **rest, \
	char *p, t_shell *shell)
{
	if (!is_special_parameter(p))
		printf("Expected special parameter");
	if (g_signal == 130)
	{
		g_signal = 0;
		shell->status = 130;
		p += 2;
		append_num(dst, shell->status);
		*rest = p;
		shell->status = 0;
	}
	else
	{
		p += 2;
		append_num(dst, shell->status);
		*rest = p;
	}
}

void	append_num(char **dst, unsigned int num)
{
	if (num == 0)
	{
		append_char(dst, '0');
		return ;
	}
	if (num / 10 != 0)
		append_num(dst, num / 10);
	append_char(dst, '0' + (num % 10));
}
