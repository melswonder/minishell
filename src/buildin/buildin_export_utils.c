/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:27:30 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/11 13:37:43 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strjoin_safe(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len1 = strlen(s1);
	len2 = strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	strcpy(result, s1);
	strcat(result, s2);
	return (result);
}

int	is_valid_varname(char *name)
{
	int	i;

	if (!name || name[0] == '\0')
		return (0);
	if (!isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i] && name[i] != '=' && !(name[i] == '+' && name[i + 1] == '='))
	{
		if (!isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

// NAME+=value 形式かチェック
int	is_appending(char *arguments)
{
	int	i;

	if (!arguments)
		return (0);
	i = 0;
	while (arguments[i])
	{
		if (arguments[i] == '+' && arguments[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

// NAME=value 形式の環境変数を追加または更新
t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

int	no_assignment(char *arguments)
{
	int	i;

	i = 0;
	while (arguments[i])
	{
		if (arguments[i] == '=')
			return (0);
		i++;
	}
	return (1);
}
