#include "../../inc/minishell.h"

void	env(char *line, char *envp[])
{
	int	i;

	i = 0;
	if(strncmp(line,"env",3) == 0)
	{
		while (envp[i] != NULL)
		{
			printf("%s\n",envp[i]);
			i++; //最期のenvの値が違うが　多分実行場所？
		}
	}
	else
		printf("command not found: %s\n",line);
}

int	main(int argc, char *argv[], char *envp[])
{
	char *line;
	while (1)
	{
		line = readline("$");
		if (line == NULL)
			break ;
		if (*line)
		{
			add_history(line);
			env(line, envp);
		}
		free(line);
	}
	exit(0);
}