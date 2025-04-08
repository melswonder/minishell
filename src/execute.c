#include "../inc/minishell.h"

// TK_WORD
// TK_RESERVED
// TK_EOF

int	count_commad(t_node *node)
{
	int	i;

	i = 0;
	if (node->command[i] == NULL)
		return (0);
	while (node->command[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	is_builtin_command(char *str)
{
	if (strcmp(str, "echo") == 0)
		return (1);
	else if (strcmp(str, "exit") == 0)
		return (1);
	else if (strcmp(str, "cd") == 0)
		return (1);
	else if (strcmp(str, "pwd") == 0)
		return (1);
	else if (strcmp(str, "export") == 0)
		return (1);
	else if (strcmp(str, "unset") == 0)
		return (1);
	else if (strcmp(str, "env") == 0)
		return (1);
	return (0);
}

int	buildin_branch(t_node *node, t_env *env)
{
	int	i;

	i = 0;
	while (node->command[i] != NULL)
	{
		if (strstr(node->command[i], "echo"))
			buildin_echo();
		else if (strstr(node->command[i], "exit"))
			buildin_exit();
		else if (strstr(node->command[i], "cd"))
			buildin_cd();
		else if (strstr(node->command[i], "pwd"))
			buildin_pwd();
		else if (strstr(node->command[i], "export"))
			buildin_export();
		else if (strstr(node->command[i], "unset"))
			buildin_unset();
		else if (strstr(node->command[i], "env"))
			buildin_env();
		i++;
	}
	return (0);
}

//---redirect---
int	redirect_input(t_node *node)
{
	int	fd;

	if (access(node->redirects->filename, F_OK) != 0)
	{
		perror("file not found");
		return (-1);
	}
	if (access(node->redirects->filename, R_OK) != 0)
	{
		perror("file not found");
		return (-1);
	}
	fd = open(node->redirects->filename, O_RDONLY);
	return (fd);
}
int	redirect_output(t_node *node)
{
	int	fd;

	fd = open(node->redirects->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}
int	redirect_append(t_node *node)
{
	int	fd;

	fd = open(node->redirects->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}
int	redirect_heredoc(t_node *node)
{
	int	fd;

	// fd = create_heredoc(node->redirects->filename);
	fd = 1;
	return (fd);
}
//---addpath---

char	**ft_path_split(char *path)
{
	char	*path_dup;
	char	*token;
	char	**result;
	int		count;
	int		i;

	count = 0;
	path_dup = strdup(path);
	if (!path_dup)
		return (NULL);
	token = strtok(path_dup, ":");
	while (token)
	{
		count++;
		token = strtok(NULL, ":");
	}
	free(path_dup);
	// 結果配列を確保（NULL終端のため+1）
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	// 再度複製してトークン分割
	path_dup = strdup(path);
	if (!path_dup)
	{
		free(result);
		return (NULL);
	}
	i = 0;
	token = strtok(path_dup, ":");
	while (token)
	{
		result[i] = strdup(token);
		i++;
		token = strtok(NULL, ":");
	}
	result[i] = NULL;
	free(path_dup);
	return (result);
}

char	**path_new(t_env *env)
{
	char	**path;

	while (env)
	{
		if (strcmp(env->key, "PATH") == 0)
			path = ft_path_split(env->value);
		env = env->next;
	}
	if (!path)
		return (NULL);
	return (path);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
//---addpath---

char	**env_to_array(t_env *env)
{
	int		count;
	t_env	*tmp;
	char	**envp;
	int		i;
	char	*line;

	count = 0;
	tmp = env;
	i = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	tmp = env;
	while (tmp)
	{
		line = malloc(strlen(tmp->key) + strlen(tmp->value) + 2);
		if (!line)
			break ;
		sprintf(line, "%s=%s", tmp->key, tmp->value);
		envp[i++] = line;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (envp)
	{
		while (envp[i])
		{
			free(envp[i]);
			i++;
		}
		free(envp);
	}
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	int		i;
	int		s1_size;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s1_size = strlen(s1);
	dest = (char *)malloc(strlen(s1) + strlen(s2) + 1);
	if (!dest)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		dest[s1_size + i] = s2[i];
		i++;
	}
	dest[s1_size + i] = '\0';
	return (dest);
}

char	*ft_str_three_join(char const *s1, char const *s2, char const *s3)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	return (ret);
}

// unset PATH用の実行
void	exec_path_or_exefile(t_node *node, t_env *env)
{
	char	**envp;

	envp = env_to_array(env);
	if (execve(node->command[0], node->command, envp) == -1)
	{
		printf("Command not found: %s\n", node->command[0]); //エラーメッセージ
		free_envp(envp);
	}
	free_envp(envp);
}

// execute_nomal: 外部コマンドの実行（PATH 内からコマンドを探す）
int	execute_nomal(t_node *node, t_env *env)
{
	char	**path;
	int		i;
	char	*cmd_path;
	char	**envp;

	if (node->command[0][0] == '/' || (node->command[0][0] == '.'
			&& node->command[0][1] == '/'))
	{
		exec_path_or_exefile(node, env);
		return (0);
	}
	i = 0;
	path = path_new(env);
	envp = env_to_array(env);
	while (path[i])
	{
		cmd_path = ft_str_three_join(path[i], "/", node->command[0]);
		if (!cmd_path)
		{
			i++;
			continue ;
		}
		printf("Trying: %s\n", cmd_path);
		if(access(cmd_path,X_OK) == 0)
		{
			if(execve(cmd_path,node->command,envp) == -1)
				perror(cmd_path);
			free(cmd_path);
			break;
		}
		free(cmd_path);
		i++;
	}
	printf("Command not found: %s\n", node->command[0]); // errorcheck
	free_path(path);
	free_envp(path);
	return (0);
}

int	execute(t_node *node, t_env *env)
{
	pid_t	pid;
	int		status;

	int input_fd, fd_in, fd_out;
	int stdin_backup, stdout_backup;
	input_fd = STDIN_FILENO;
	while (node)
	{
		fd_in = input_fd; // 以前のコマンドの出力を次の入力に
		fd_out = STDOUT_FILENO;
		// リダイレクトが設定されている場合
		if (node->redirects != NULL)
		{
			if (node->redirects->kind == RD_INPUT)
				fd_in = redirect_input(node);
			else if (node->redirects->kind == RD_HEREDOC)
				fd_in = redirect_heredoc(node);
			else if (node->redirects->kind == RD_OUTPUT)
				fd_out = redirect_output(node);
			else if (node->redirects->kind == RD_APPEND)
				fd_out = redirect_append(node);
			if (fd_in == -1 || fd_out == -1)
				return (EXIT_FAILURE);
		}
		// built-in の場合
		if (is_builtin_command(node->command[0]))
		{
			// 標準入出力のバックアップに正しいfdを使用する
			stdin_backup = dup(STDIN_FILENO);
			stdout_backup = dup(STDOUT_FILENO);
			if (fd_in != STDIN_FILENO)
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (fd_out != STDOUT_FILENO)
			{
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			buildin_branch(node, env);
			dup2(stdin_backup, STDIN_FILENO);
			dup2(stdout_backup, STDOUT_FILENO);
			close(stdin_backup);
			close(stdout_backup);
		}
		else // 外部コマンドの場合
		{
			pid = fork();
			if (pid == 0)
			{
				if (fd_in != STDIN_FILENO)
					dup2(fd_in, STDIN_FILENO);
				if (fd_out != STDOUT_FILENO)
					dup2(fd_out, STDOUT_FILENO);
				execute_nomal(node, env);
				exit(EXIT_FAILURE);
			}
			else if (pid < 0)
			{
				perror("fork error");
				return (EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, &status, 0);
			}
			if (fd_in != STDIN_FILENO)
				close(fd_in);
			if (fd_out != STDOUT_FILENO)
				close(fd_out);
		}
		// 出力リダイレクトがあれば、次のコマンドの入力として引き継ぐ
		if (node->redirects != NULL && (node->redirects->kind == RD_OUTPUT
				|| node->redirects->kind == RD_APPEND))
			input_fd = fd_out;
		else
			input_fd = STDIN_FILENO;
		node = node->next;
	}
	return (EXIT_SUCCESS);
}
