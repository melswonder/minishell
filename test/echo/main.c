#include "../../inc/minishell.h"
#include <ctype.h>
#include <string.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*get_env_value(char *var_name, char *env[])
{
	int		i;
	char	*eq_pos;
	int		var_len;

	var_len = ft_strlen(var_name);
	i = 0;
	while (env[i] != NULL)
	{
		eq_pos = strchr(env[i], '=');
		if (eq_pos && (eq_pos - env[i]) == var_len && 
		strncmp(var_name, env[i],var_len) == 0) //ながさと文字が一緒かどうか
			return (eq_pos + 1);
		else
			i++;
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
		else
			i++;
	}
	return (0);
}

int	ft_echo(char *line, char *env[])
{
	int		i;
	int		var_pos;
	int		in_squote;
	int		in_dquote;
	char	var_name[256];
	int		new_line;

	new_line = 1;
	if (strncmp("echo", line, 4) == 0)
	{
		if (option_check(line))
			new_line = 0;
		i = 4;
		while (line[i] == ' ') //空白をスキップ
			i++;
		in_dquote = 0;
		in_squote = 0;
		while (line[i])
		{
			if (line[i] == '"' && !in_squote)
			{
				in_dquote = !in_dquote;
				i++;
				continue ;
			}
			else if (line[i] == '\'' && !in_dquote)
			{
				in_squote = !in_squote;
				i++;
				continue ;
			}
			else if (line[i] == '$' && !in_squote) //シングルクオートでは展開しない
			{
				i++;
				var_pos = 0;
				while (line[i] && (isalnum(line[i]) || line[i] == '_'))
					var_name[var_pos++] = line[i++];
				var_name[var_pos] = '\0';
				// printf("\nDEBUG: 変数名=[%s]\n", var_name);
				if (var_pos > 0)
				{
					// char *value = get_env_value(var_name, env);
					// printf("DEBUG: 値=[%s]\n", value);
					printf("%s", get_env_value(var_name, env));
				}
				continue ;
			}
			printf("%c", line[i++]);
		}
		if (new_line)
			printf("\n");
	}
	else
		printf("command not found: %s\n", line);
	return (0);
}

int	main(void)
{
	char *line;
	extern char **environ;
	while (1)
	{
		line = readline("$");
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			ft_echo(line, environ);
		}
		free(line);
	}
	exit(0);
}