#include <ctype.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0') //数字かチェック
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

//文字列をunsigned long long変換(over flowチェックもある)
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

int	has_extra_args(char *line, int i)
{
	while (line[i] == ' ')
		i++;
	return (line[i] != '\0');
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
	if (sign_present && *num_start == '\0') //-0とかのちぇっく
		return (0);
	return (1);
}

void	ft_exit(char *line, char *envp[])
{
	int					i;
	char				*arg;
	int					is_minus;
	unsigned long long	num;

	if (strncmp(line, "exit", 4) == 0)
	{
		printf("exit\n");
		i = 4;
		while (line[i] == ' ')
			i++;
		if (line[i] == '\0') // 引数がない場合は通常終了（ステータス0）
			exit(0);
		arg = extract_arg(line, &i);
		is_minus = 0;
		if (!is_valid_number(arg, &num))
		{
			printf("bash: exit: %s: numeric argument required\n", arg);
			free(arg);
			exit(2);
		}
		if (has_extra_args(line, i))
		{
			free(arg);
			printf("bash: exit: too many arguments\n");
			return ;
		}
		if (arg[0] == '-') //マイナスなら計算式を変える
			exit(256 - (num % 256) % 256);
		else
			exit(num % 256);
	}
	else
		printf("command not found: %s\n", line);
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
			ft_exit(line, environ);
		}
		free(line);
	}
	exit(0);
}