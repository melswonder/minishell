/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/04/06 20:20:07 by hirwatan         ###   ########.fr       */
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
	print_node(node); // debug　nodeを全部プリントする関数
	// stop
	execute(node, env);
	return ;
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
		// stop
		// exit(0);
		// free(line);
	}
}

t_env	*init_env(char **envp)
{
    t_env	*head = NULL;
    t_env	*tail = NULL;
    t_env	*new_node;
    int		i;
    char	*equal_sign;
    char	*key;
    char	*value;

    i = 0;
    while (envp[i])
    {
        new_node = malloc(sizeof(t_env));
        if (!new_node)
            return (NULL); // エラー時は必要に応じてリスト全体の解放処理を追加
        // envp[i]から '=' の位置を探す
        equal_sign = strchr(envp[i], '=');
        if (equal_sign)
        {
            // key は '=' の左側、value は '=' の右側
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
