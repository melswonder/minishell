#include "../../inc/minishell.h"
#include <string.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s)
{
	char	*dest;
	char	*start;

	dest = (char *)malloc(ft_strlen(s) + 1);
	if (!dest)
		return (NULL);
	start = dest;
	while (*s)
	{
		*dest = *s;
		dest++;
		s++;
	}
	*dest = '\0';
	return (start);
}

char	**ft_join(char **env)
{
	int		i;
	int		len;
	char	**my_env;

	len = 0;
	while (env[len] != NULL)
		len++;
	my_env = (char **)malloc(sizeof(char *) * len + 1);
	my_env[len] = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		my_env[i] = strdup(env[i]);
		i++;
	}
	return (my_env);
}

void	delete_line_env(char *my_env[], int del_idx)
{
	int	i;

	free(my_env[del_idx]);
	i = del_idx;
	while (my_env[i + 1] != NULL)
	{
		my_env[i] = my_env[i + 1];
		i++;
	}
	my_env[i] = NULL;
}

void print_env(char *my_env[])
{
	int i = 0;
	while(my_env[i] != NULL)
	{
		printf("%s\n",my_env[i]);
		i++;
	}
}

void	unset(char *line, char **my_env)
{
	char	*name;
	char	*eq_pos;
	int		name_len;
	int		i;

	if (strncmp(line, "unset", 5) == 0)
	{
		i = 5;
		while (line[i] == ' ')
			i++;
		name = ft_strdup(line + i);
		if(!name)
			return;
		name_len = ft_strlen(name);
		while (my_env[i] != NULL)
		{
			eq_pos = strchr(my_env[i],'=');
			if (eq_pos && (eq_pos - my_env[i])== name_len &&
			 strncmp(name, my_env[i], name_len) == 0)
				delete_line_env(my_env, i);
			else
				i++;
		}
		free(name);
	}
	else if(strncmp(line,"env",3) == 0)
		print_env(my_env);
	else
		printf("command not found %s\n",line);
}

int	main(void)
{
	char *line;
	extern char **environ;
	char **my_env;

	my_env = ft_join(environ);
	while (1)
	{
		line = readline("\033[1;32mMinishell$ \033[0m");
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			unset(line, my_env);
		}
		free(line);
	}
	exit(0);
}