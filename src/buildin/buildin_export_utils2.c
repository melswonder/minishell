/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:33:57 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/11 13:36:16 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	print_env(t_env *env)
{
	if (!env)
		return (1);
	while (env)
	{
		if (env->value == NULL)
			printf("declare -x %s\n", env->key);
		else
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

void	export_join_env(t_env *existing, char *value, char *new_value,
		char *key)
{
	new_value = ft_strjoin_safe(existing->value, value);
	free(existing->value);
	existing->value = new_value;
	free(key);
	free(value);
}

void	export_valid_error(char *key, char *value, char *arguments)
{
	printf("export: '%s': not a valid identifier\n", arguments);
	free(key);
	free(value);
}

t_env	*find_env(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	add_env(t_env *env, t_env *new_node)
{
	t_env	*last;

	if (!env)
		return (1);
	last = env;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (0);
}
