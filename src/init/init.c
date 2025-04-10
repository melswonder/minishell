/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:00:20 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/10 22:45:25 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_shell	*init_shell(t_env *env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = env;
	shell->head = NULL;
	shell->syntax_error = false;
	shell->status = 0;
	return (shell);
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
