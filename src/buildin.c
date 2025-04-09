#include "../inc/minishell.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ヘッダでは get_env_value のシグネチャは
// char *get_env_value(t_env *env, char *key);
// に合わせる
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*get_env_value(t_env *env, char *key)
{
	int	var_len;

	var_len = ft_strlen(key);
	while (env)
	{
		if ((ft_strlen(env->key) == var_len) && (strncmp(env->key, key,
					var_len) == 0))
			return (env->value);
		env = env->next;
	}
	return ("");
}

int	option_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' && str[i + 1] == 'n')
			return (1);
		i++;
	}
	return (0);
}

int	buildin_echo(t_node *node, t_env *env)
{
	int		i;
	int		var_pos;
	int		in_squote;
	int		in_dquote;
	char	var_name[256];
	int		new_line;

	new_line = 1;
	if (option_check(node->command[0]))
		new_line = 0;
	i = 4; // "echo" の後ろから開始
	while (node->command[0][i] == ' ')
		i++;
	in_dquote = 0;
	in_squote = 0;
	while (node->command[0][i])
	{
		if (node->command[0][i] == '"' && !in_squote)
		{
			in_dquote = !in_dquote;
			i++;
			continue ;
		}
		else if (node->command[0][i] == '\'' && !in_dquote)
		{
			in_squote = !in_squote;
			i++;
			continue ;
		}
		else if (node->command[0][i] == '$' && !in_squote)
		{
			i++;
			var_pos = 0;
			while (node->command[0][i] && (isalnum(node->command[0][i])
					|| node->command[0][i] == '_'))
				var_name[var_pos++] = node->command[0][i++];
			var_name[var_pos] = '\0';
			if (var_pos > 0)
				printf("%s", get_env_value(env, var_name));
			continue ;
		}
		printf("%c", node->command[0][i++]);
	}
	if (new_line)
		printf("\n");
	return (0);
}

//---exit---
int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoull(const char *str, unsigned long long *result)
{
	unsigned long long	res;
	int					i;
	unsigned long long	prev;

	res = 0;
	i = 0;
	while (isspace(str[i]))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		prev = res;
		res = res * 10 + (str[i] - '0');
		if (res < prev)
		{
			*result = 0;
			return (0);
		}
		i++;
	}
	if (str[i] != '\0')
		return (0);
	*result = res;
	return (1);
}

static char	*extract_arg(char *line, int *index)
{
	char	buffer[1024];
	int		i;
	int		j;

	i = *index;
	j = 0;
	while (line[i] != '\0' && line[i] != ' ')
		buffer[j++] = line[i++];
	buffer[j] = '\0';
	*index = i;
	return (strdup(buffer));
}

int	has_extra_args(char **line, int i)
{
	while (line[i] != NULL)
		i++;
	if (i > 2)
		return (1);
	return (0);
}

int	is_valid_number(char *arg, unsigned long long *num)
{
	char	*num_start;
	int		sign_present;

	num_start = arg;
	sign_present = 0;
	if (*num_start == '-' || *num_start == '+')
	{
		sign_present = 1;
		num_start++;
	}
	if (!is_numeric(arg))
		return (0);
	if (!ft_atoull(num_start, num))
		return (0);
	if (sign_present && *num_start == '\0')
		return (0);
	return (1);
}

int	buildin_exit(t_node *node)
{
	char				*arg;
	unsigned long long	num;
	int					i;

	i = 0;
	printf("exit\n");
	if (node->command[1] == NULL) // 引数なしなら exit(0)
		exit(0);
	arg = extract_arg(node->command[1], &i);
	if (!is_valid_number(arg, &num))
	{
		printf("bash: exit: %s: numeric argument required\n", arg);
		free(arg);
		exit(2);
	}
	if (node->command[2] != NULL)
	{
		free(arg);
		printf("bash: exit: too many arguments\n");
		return (1);
	}
	if (arg[0] == '-')
		exit(256 - (num % 256) % 256);
	else
		exit(num % 256);
	return (0);
}

//---cd---
char	*ft_getenv(char *str, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (strcmp(str, env->key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_directory(char *cmd, t_env *env)
{
	char	*ptr;

	ptr = cmd;
	while (*ptr && !isspace(*ptr))
		ptr++;
	while (*ptr && isspace(*ptr))
		ptr++;
	return (ptr);
}

int	elements_check(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	if (i > 2)
		return (1);
	return (0);
}

char	*str_substitution(char const *ret, char  const *rep)
{
	free(ret);
	ret = malloc(sizeof(char *) * ft_strlen(rep) + 1);
	ret = ft_strjoin(ret, rep);
	return (ret);
}

int	set_to_env_value(t_env *env, char *key, char *set_value)
{
	t_env	*tmp;

	while (tmp)
	{
		if (strcmp(env->key, key) == 0)
		{
			str_substitution(env->value, set_value);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	buildin_cd(t_node *node, t_env *env)
{
	char	*home;
	char	*dir;

	if (node->command[1] == NULL)
	{
		home = ft_getenv("HOME", env);
		if (home == NULL)
		{
			printf("bash: cd: HOME not set\n");
			return (1);
		}
		dir = home;
	}
	else
		dir = node->command[1];
	if (chdir(dir) != 0)
	{
		if (elements_check(node->command) == 1)
			printf("bash: cd: too many arguments\n");
		else
			printf("bash: cd: %s: No such file or directory\n",
				node->command[1]);
	}
	set_to_env_value(env, "OLDPWD", node->command[1]);
	return (0);
}

int	buildin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd error");
	return (0);
}

int	buildin_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s=\"%s\"\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}

int	buildin_unset(t_node *node, t_env **env)
{
	char	*unset_key;
	t_env	*prev;
	t_env	*curr;

	if (node->command[1] == NULL)
		unset_key = strdup("");
	else
		unset_key = strdup(node->command[1]);
	prev = NULL;
	curr = *env;
	while (curr)
	{
		if (strcmp(curr->key, unset_key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	free(unset_key);
	return (0);
}

int	buildin_env(t_env *env)
{
	if (!env)
		return (1);
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
	return (0);
}