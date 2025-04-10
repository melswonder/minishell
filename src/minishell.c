/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/04/10 21:44:50 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	init_shell(t_shell *shell, t_env *env)
{
	shell->env = env;
	shell->head = NULL;
	shell->syntax_error = false;
	shell->status = 0;
}

bool	check_syntax_error(t_shell *shell, t_node *node, t_token *tokens)
{
	if (shell->syntax_error)
	{
		shell->status = 2;
		printf("syntax_error near unexpected token `  '\n");
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
	add_history(line);
	tokens = tokenize(line, shell);
	node = parse(tokens, shell);
	if (check_syntax_error(shell, node, tokens))
		return ;
	expand_variable(shell);
	print_node(shell->head);
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

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	*tail;
	t_env	*new_node;
	int		i;
	char	*equal_sign;
	char	*key;
	char	*value;

	head = NULL;
	tail = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		equal_sign = strchr(envp[i], '=');
		if (equal_sign)
		{
			key = strndup(envp[i], equal_sign - envp[i]);
			value = strdup(equal_sign + 1);
		}
		else
		{
			key = strdup(envp[i]);
			value = strdup("");
		}
		new_node->key = key;
		new_node->value = value;
		new_node->next = NULL;
		if (!head)
		{
			head = new_node;
			tail = new_node;
		}
		else
		{
			tail->next = new_node;
			tail = new_node;
		}
		i++;
	}
	return (head);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	t_shell	*shell;

	if (argc != 1)
	{
		exit(1);
	}
	(void)argc;
	(void)argv;
	env = init_env(envp);
	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	init_shell(shell, env);
	minishell_loop(env, shell);
	free(shell);
	free_env(env);
	return (0);
}
