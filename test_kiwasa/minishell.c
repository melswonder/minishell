/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/04/06 15:59:47 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

void	signal_handler(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

static void	process_input(char *line, t_env *env)
{
	t_token	*tokens;
	t_node	*node;

	if (line[0] == '\0')
		return ;
	add_history(line);
	tokens = tokenize(line);
	node = parse(tokens);
	// stop
	return;
	execute(node, env);
	free_tokens(tokens);
	free_node(node);
}

void	minishell_loop(t_env *env)
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
		process_input(line, env);
		//stop
		exit(0);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	if (argc != 1)
	{
		exit(1);
	}
	(void)argc;
	(void)argv;
	env = init_env(envp);
	minishell_loop(env);
	free_env(env);
	return (0);
}

