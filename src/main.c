/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:24:01 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/10 22:41:10 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (!env)
		return (1);
	shell = init_shell(env);
	if (!shell)
		return (1);
	minishell_loop(env, shell);
	free(shell);
	free_env(env);
	return (0);
}
