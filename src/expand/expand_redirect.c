/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:59:48 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/14 02:46:06 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	expand_redirects(t_shell *shell, t_redirect *redirect)
{
	char	*expanded;

	while (redirect != NULL)
	{
		if (redirect->kind != RD_HEREDOC && redirect->filename != NULL)
		{
			expanded = expand_string(shell, redirect->filename);
			if (expanded != NULL)
				free(redirect->filename);
			redirect->filename = expanded;
		}
		redirect = redirect->next;
	}
}
