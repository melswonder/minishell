/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/04/12 03:31:53 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

volatile sig_atomic_t	g_signal = 0;

bool	check_syntax_error(t_shell *shell, t_node *node, t_token *tokens)
{
	if (shell->syntax_error)
	{
		shell->status = 2;
		printf("syntax_error\n");
		if (node)
			free_all_nodes(node);
		if (tokens)
			free_tokens(tokens);
		return (true);
	}
	return (false);
}

static void	process_input(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_node	*node;

	if (line[0] == '\0')
		return ;
	shell->syntax_error = false;
	tokens = tokenize(line, shell);
	node = parse(tokens, shell);
	if (!node)
	{
		free_tokens(tokens);
		return ;
	}
	add_history(line);
	if (check_syntax_error(shell, node, tokens))
		return ;
	expand_variable(shell);
	execute(shell);
	free_tokens(tokens);
	free_all_nodes(shell->head);
}

void	minishell_loop(t_env *env, t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_signal();
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		process_input(line, shell);
		free(line);
	}
}
