/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:49:02 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/12 21:03:37 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	apply_redirections(t_redirect *current, int *fd_in, int *fd_out)
{
	if (current == NULL)
		return (0);
	if (current->kind == RD_INPUT || current->kind == RD_HEREDOC)
		input_heredoc_redirect(current, fd_in);
	else if (current->kind == RD_OUTPUT || current->kind == RD_APPEND)
		output_append_redirect(current, fd_out);
	if (*fd_in == -1 || *fd_out == -1)
		exit(EXIT_FAILURE);
	return (0);
}
