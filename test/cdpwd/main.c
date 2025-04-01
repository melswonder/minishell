#include "../../inc/minishell.h"
#include <string.h>

int ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return(i);
}

char *get_directory(char *cmd)
{
	char *ptr = cmd;
	while(*ptr && !(*ptr == ' ' || *ptr == '\t'))
		ptr++;
	while(*ptr && (*ptr == ' ' || *ptr == '\t'))
		ptr++;
	if(*ptr == '\0')
		return(getenv("HOME"));
	return(ptr);
}

char *ft_cmd(char *str)
{
	char *ptr = str;
	while(*ptr && !(*ptr == ' ' || *ptr == '\t'))
		ptr++;
	while(*ptr && (*ptr == ' ' || *ptr == '\t'))
		ptr++;
	return(ptr);
}

void lexser_w(char *str)
{
	char *pwd;
	char *dir;

	if(strncmp(str,"pwd",3) == 0)
	{
		pwd = getcwd(NULL,0);
		printf("%s\n",pwd);
		free(pwd);
	}
	else if(strncmp(str,"cd",2) == 0)
	{
		dir = get_directory(str);
		if(chdir(dir) != 0)
			printf("bash: cd: %s: No such file or directory\n",ft_cmd(str)); //errmsgなどを作りたい
	}
	else
		printf("command not found: %s\n",str);
	return ;
}

int	main(void)
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
			lexser_w(line);
		}
		free(line);
	}
	exit(0);
}