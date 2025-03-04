/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:47:59 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/04 22:07:04 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../inc/minishell.h>

int	main(void)
{
	char *line;
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minihell$");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		free(line);
	}
	exit(0);
}