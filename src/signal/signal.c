/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:17:02 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/15 19:39:35 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	setup_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

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

void	signal_exit(int sig)
{
	(void)sig;
	exit(1);
}

void	signal_handler_exit(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\b", 1);
	}
	exit(130);
}

void	signal_pipe(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		write(1, "\b\n", 2);
	}
	if (sig == SIGQUIT)
	{
		write(1, "\bQuit (core dumped)\n", 20);
	}
}
