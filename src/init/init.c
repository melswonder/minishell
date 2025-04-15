/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 22:00:20 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/15 20:02:11 by kiwasa           ###   ########.fr       */
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

t_env	*create_init_env_node(char *env_str)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(env_str, '=');
	if (equal_sign)
	{
		new_node->key = strndup(env_str, equal_sign - env_str);
		new_node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new_node->key = ft_strdup(env_str);
		new_node->value = ft_strdup("");
	}
	new_node->next = NULL;
	return (new_node);
}

t_env	*init_env(char **envp)
{
	t_env		*head;
	t_env		*tail;
	t_env		*new_node;
	static int	i = 0;

	head = NULL;
	tail = NULL;
	while (envp[i])
	{
		new_node = create_init_env_node(envp[i]);
		if (!new_node)
			return (NULL);
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

void	init_parse(t_node **current, t_node **head, t_node **next_node)
{
	*current = NULL;
	*head = NULL;
	*next_node = NULL;
}
