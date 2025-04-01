#include <ctype.h>
#include <limits.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define LINEBUF_MAX 2048

long long int	ft_atoll(char *nptr)
{
	long long int	ret;
	int				m_flag;

	m_flag = 1;
	ret = 0;
	while ((*nptr >= 'a' && *nptr <= 'z') || (*nptr >= 'A' && *nptr <= 'Z'))
		nptr++;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == ' ')
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			m_flag = -1;
	while (*nptr)
	{
		if (*nptr >= '0' && *nptr <= '9')
		{
			if (m_flag == 1 && ret > (LLONG_MAX - (*nptr - '0')) / 10)
				return (LLONG_MAX);
			if (m_flag == -1 && ret > ((unsigned long long)(-(LLONG_MIN + (*nptr
								- '0')))) / 10)
				return (LLONG_MIN);
			ret = ret * 10 + (*nptr - '0');
			nptr++;
		}
		else
			break ;
	}
	return (ret * m_flag);
}

int	ft_first_exit_check(char *str)
{
	int			i;
	int			sign;
	long long	result;
	int			digit;

	i = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (strncmp(str + i, "exit", 4) != 0)
		return (1);
	i += 4;
	if (str[i] && !(str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		return (1);
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (!str[i])
		return (0);
	sign = 1;
	result = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!isdigit(str[i]))
		return (1);
	while (isdigit(str[i]))
	{
		digit = str[i] - '0';
		if (sign == 1)
		{
			if (result > (LLONG_MAX - digit) / 10)
				return (1);
		}
		else
		{
			/* LLONG_MINは負なので、正のresultに変換してチェックする */
			if (result > ((unsigned long long)(-(LLONG_MIN + digit))) / 10)
				return (1);
		}
		result = result * 10 + digit;
		i++;
	}
	// 数値の後に余計な文字がないかチェック
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i])
		return (1);
	return (0);
}

int	overflow_or_character_check(char *buf)
{
}

void	prompt(void)
{
	char			buf[LINEBUF_MAX];
	long long int	exit_status;
	ssize_t			n;
	char			*cmd;
	long long int	exit_status;

	while (1)
	{
		write(1, "$ ", 2);
		n = read(0, buf, LINEBUF_MAX - 1);
		if (n <= 0)
			exit(0);
		buf[n] = '\0';
		if (buf[n - 1] == '\n')
			buf[n - 1] = '\0';
		cmd = split_buf();
		if (overflow_or_character_check(cmd))
		{
			printf("exit\n");
			printf("bash: exit: %s: numeric argument required", cmd[1]);
			exit(2);
		}
		if (ft_first_exit_check(buf) == 0)
		{
			exit_status = ft_atoll(buf);
			if (exit_status >= 0)
				exit(exit_status % 256);
			else
				exit(256 - (-exit_status % 256));
		}
	}
}

int	main(void)
{
	prompt();
	return (0);
}