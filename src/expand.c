/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 04:30:08 by kiwasa            #+#    #+#             */
/*   Updated: 2025/04/10 04:42:29 by kiwasa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	is_alpha_under(char c)
{
	return (isalpha(c) || c == '_');
}

bool	is_alpha_num_under(char c)
{
	return (is_alpha_under(c) || isdigit(c));
}

bool	is_identifier(const char *s)
{
	if (!is_alpha_under(*s))
		return (false);
	s++;
	while (*s)
	{
		if (!is_alpha_num_under(*s))
			return (false);
		s++;
	}
	return (true);
}

bool	is_variable(char *s)
{
	return (s[0] == '$' && is_alpha_under(s[1]));
}

bool	is_special_parameter(char *s)
{
	return (s[0] == '$' && s[1] == '?');
}

void	append_char(char **dst, char c)
{
	size_t	len;
	char	*new;

	len = strlen(*dst);
	new = calloc(len + 2, sizeof(char));
	if (new == NULL)
		printf("calloc");
	strcpy(new, *dst);
	new[len] = c;
	new[len + 1] = '\0';
	free(*dst);
	*dst = new;
}

void	append_num(char **dst, unsigned int num)
{
	if (num == 0)
	{
		append_char(dst, '0');
		return ;
	}
	if (num / 10 != 0)
		append_num(dst, num / 10);
	append_char(dst, '0' + (num % 10));
}

bool	is_metacharacter(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
			c == '|' || c == '<' || c == '>');
}

char	*get_env_values(t_shell *shell, const char *key)
{
	t_env	*env;

	env = shell->env;
	while (env)
	{
		if (strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	expand_variable_str(char **dst, char **rest, char *p, t_shell *shell)
{
	char	*name;
	char	*value;

	name = calloc(1, sizeof(char));
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

void	expand_special_parameter_str(char **dst, char **rest, \
		char *p, t_shell *shell)
{
	if (!is_special_parameter(p))
		printf("Expected special parameter");
	p += 2;
	append_num(dst, shell->status);
	*rest = p;
}

void	append_single_quote(char **dst, char **rest, char *p)
{
	if (*p == SINGLE_QUOTE_CHAR)
	{
		append_char(dst, *p++);
		while (*p != SINGLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				printf("Unclosed single quote");
			append_char(dst, *p++);
		}
		append_char(dst, *p++);
		*rest = p;
	}
	else
		printf("Expected single quote");
}

void	append_double_quote(char **dst, char **rest, char *p, t_shell *shell)
{
	if (*p == DOUBLE_QUOTE_CHAR)
	{
		p++;
		while (*p != DOUBLE_QUOTE_CHAR)
		{
			if (*p == '\0')
				printf("Unclosed double quote");
			else if (is_variable(p))
				expand_variable_str(dst, &p, p, shell);
			else if (is_special_parameter(p))
				expand_special_parameter_str(dst, &p, p, shell);
			else
				append_char(dst, *p++);
		}
		p++;
		*rest = p;
	}
	else
		printf("Expected double quote");
}

char	*expand_string(t_shell *shell, char *word)
{
	char	*new_word;
	char	*p;

	if (word == NULL)
		return (NULL);
	p = word;
	new_word = calloc(1, sizeof(char));
	if (new_word == NULL)
		printf("calloc");
	while (*p && !is_metacharacter(*p))
	{
		if (*p == SINGLE_QUOTE_CHAR)
			append_single_quote(&new_word, &p, p);
		else if (*p == DOUBLE_QUOTE_CHAR)
			append_double_quote(&new_word, &p, p, shell);
		else if (is_variable(p))
			expand_variable_str(&new_word, &p, p, shell);
		else if (is_special_parameter(p))
			expand_special_parameter_str(&new_word, &p, p, shell);
		else
			append_char(&new_word, *p++);
	}
	return (new_word);
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

void	expand_redirects(t_shell *shell, t_redirect *redirect)
{
	char	*expanded;

	while (redirect != NULL)
	{
		if (redirect->kind != RD_HEREDOC && redirect->filename != NULL)
		{
			expanded = expand_string(shell, redirect->filename);
			free(redirect->filename);
			redirect->filename = expanded;
		}
		redirect = redirect->next;
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
