/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 01:40:00 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/14 02:05:39 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

bool	is_variable(char *s)
{
	return (s[0] == '$' && is_alpha_under(s[1]));
}

char	*get_env_values(t_shell *shell, const char *key)
{
	t_env	*env;
	int		len;

	env = shell->env;
	len = ft_strlen(key);
	while (env)
	{
		if (ft_strncmp(env->key, key, len) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	expand_variable_str(char **dst, char **rest, char *p, t_shell *shell)
{
	char	*name;
	char	*value;

	name = ft_calloc(1, sizeof(char));
	if (name == NULL)
		printf("calloc");
	if (*p != '$')
		printf("Expected dollar sign");
	p++;
	if (!is_alpha_under(*p))
		printf("Variable must starts with alphabetic character or underscore.");
	append_char(&name, *p++);
	while (is_alpha_num_under(*p))
		append_char(&name, *p++);
	value = get_env_values(shell, name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*rest = p;
}

void	expand_command(t_shell *shell, char **command)
{
	int		i;
	char	*expanded;

	if (command == NULL)
		return ;
	i = 0;
	while (command[i])
	{
		expanded = expand_string(shell, command[i]);
		free(command[i]);
		command[i] = expanded;
		i ++;
	}
}

void	expand_variable(t_shell *shell)
{
	t_node	*current;

	if (shell == NULL || shell->head == NULL)
		return ;
	current = shell->head;
	while (current != NULL)
	{
		expand_command(shell, current->command);
		expand_redirects(shell, current->redirects);
		current = current->next;
	}
}
