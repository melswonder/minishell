/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:26:15 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/14 02:26:33 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// NAME=value
int	is_addition(char *arguments)
{
	int	i;

	if (!arguments)
		return (0);
	i = 0;
	while (arguments[i])
	{
		if (arguments[i] == '=' && (i == 0 || arguments[i - 1] != '+'))
			return (1);
		i++;
	}
	return (0);
}

// NAME=value 形式の環境変数を追加または更新
void	env_addition(char *arguments, t_env *env)
{
	char	*key;
	char	*value;
	t_env	*existing;
	t_env	*new_node;
	char	*equal_pos;

	equal_pos = ft_strchr(arguments, '=');
	if (!equal_pos)
		return ;
	key = strndup(arguments, equal_pos - arguments);
	value = strdup(equal_pos + 1);
	if (!is_valid_varname(key))
		return (export_valid_error(key, value, arguments));
	existing = find_env(env, key);
	if (existing)
	{
		free(existing->value);
		existing->value = value;
		free(key);
		return ;
	}
	new_node = create_env_node(key, value);
	if (new_node)
		add_env(env, new_node);
}

// NAME+=value 形式の環境変数を追記
void	env_appending(char *arguments, t_env *env)
{
	char	*key;
	char	*value;
	t_env	*existing;
	char	*plus_pos;
	char	*new_value;

	new_value = NULL;
	plus_pos = strstr(arguments, "+=");
	if (!plus_pos)
		return ;
	key = strndup(arguments, plus_pos - arguments);
	value = strdup(plus_pos + 2);
	if (!is_valid_varname(key))
		return (export_valid_error(key, value, arguments));
	existing = find_env(env, key);
	if (existing)
		return (export_join_env(existing, value, new_value, key));
	if (create_env_node(key, value))
		add_env(env, create_env_node(key, value));
}

void	env_no_assignment(char *arguments, t_env *env)
{
	char	*key;
	char	*value;
	char	*equal_pos;
	t_env	*existing;
	t_env	*new_node;

	key = strdup(arguments);
	value = NULL;
	equal_pos = NULL;
	if (!is_valid_varname(key))
	{
		printf("export: '%s': not a valid identifier\n", arguments);
		free(key);
		return ;
	}
	existing = find_env(env, key);
	if (existing)
	{
		free(existing->value);
		existing->value = value;
		free(key);
		return ;
	}
	new_node = create_env_node(key, value);
	if (new_node)
		add_env(env, new_node);
}

int	buildin_export(t_node *node, t_env *env)
{
	int	i;

	i = 1;
	if (node->command[i] == NULL)
		print_env(env);
	else
	{
		while (node->command[i] != NULL)
		{
			if (no_assignment(node->command[i]))
				env_no_assignment(node->command[i], env);
			else if (is_appending(node->command[i]))
				env_appending(node->command[i], env);
			else if (is_addition(node->command[i]))
				env_addition(node->command[i], env);
			else
				printf("export: '%s': not a valid identifier\n",
					node->command[i]);
			i++;
		}
	}
	return (0);
}
