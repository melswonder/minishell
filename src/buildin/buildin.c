#include "../../inc/minishell.h"
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

int	option_check(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (str[i] != '-')
		return (0);
	i = 1;
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	if (i == 1)
		return (0);
	return (1);
}

int	buildin_echo(t_node *node)
{
	int	i;
	int	var_pos;
	int	new_line;

	i = 1;
	new_line = 1;
	if (option_check(node->command[1]))
	{
		new_line = 0;
		i++;
	}
	while (node->command[i] != NULL)
	{
		printf("%s", node->command[i]);
		if (node->command[i + 1] != NULL)
			printf(" ");
		i++;
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
//---exit---

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

char	*str_substitution(char const *ret, char const *rep)
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
//---cd---

//---pwd---
int	buildin_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd error");
	return (0);
}
//---pwd---

//---export---
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

// 変数名が有効化(alpha number '_')
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

// NAME=value 形式の環境変数を追加または更新
void	env_addition(char *arguments, t_env *env)
{
	char	*key;
	char	*value;
	t_env	*existing;
	t_env	*new_node;
	char	*equal_pos;

	equal_pos = strchr(arguments, '=');
	if (!equal_pos)
		return ;
	key = strndup(arguments, equal_pos - arguments);
	value = strdup(equal_pos + 1);
	if (!is_valid_varname(key))
	{
		printf("export: '%s': not a valid identifier\n", arguments);
		free(key);
		free(value);
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

// NAME+=value 形式の環境変数を追記
void	env_appending(char *arguments, t_env *env)
{
	char	*key;
	char	*value;
	t_env	*existing;
	t_env	*new_node;
	char	*plus_pos;
	char	*new_value;

	plus_pos = strstr(arguments, "+=");
	if (!plus_pos)
		return ;
	key = strndup(arguments, plus_pos - arguments);
	value = strdup(plus_pos + 2);
	if (!is_valid_varname(key))
	{
		printf("export: '%s': not a valid identifier\n", arguments);
		free(key);
		free(value);
		return ;
	}
	existing = find_env(env, key);
	if (existing)
	{
		new_value = ft_strjoin_safe(existing->value, value);
		free(existing->value);
		existing->value = new_value;
		free(key);
		free(value);
		return ;
	}
	new_node = create_env_node(key, value);
	if (new_node)
		add_env(env, new_node);
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

void	env_no_assignment(char *arguments, t_env *env)
{
	char	*key;
	char	*value;
	t_env	*existing;
	t_env	*new_node;
	char	*equal_pos;

	key = strdup(arguments);
	value = NULL;
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

// buildin_export関数を修正
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
//---export---

void	unset_env(t_env **env, char *unset_key)
{
	t_env	*prev;
	t_env	*curr;

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
}

int	buildin_unset(t_node *node, t_env **env)
{
	int	i;

	i = 1;
	if (node->command[i] == NULL)
		return (0);
	while (node->command[i] != NULL)
	{
		unset_env(env, node->command[i]);
		i++;
	}
	return (0);
}

//---env---
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
//---env---