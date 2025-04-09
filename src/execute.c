#include "../inc/minishell.h"

// TK_WORD
// TK_RESERVED
// TK_EOF
int	ft_pipecount(t_node *node)
{
	t_node	*tmp;
	int		count;

	count = 0;
	tmp = node;
	while (tmp)
	{
		if (strcmp(tmp->command[0], "|") == 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

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
	if (!str)
		return (0);
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
	char	*cmd;

	cmd = node->command[0];
	if (strcmp(cmd, "echo") == 0)
		return (buildin_echo(node, env));
	else if (strcmp(cmd, "exit") == 0)
		return (buildin_exit(node));
	else if (strcmp(cmd, "cd") == 0)
		return (buildin_cd(node, env));
	else if (strcmp(cmd, "pwd") == 0)
		return (buildin_pwd());
	else if (strcmp(cmd, "export") == 0)
		return (buildin_export(env));
	else if (strcmp(cmd, "unset") == 0)
		return (buildin_unset(node, &env));
	else if (strcmp(cmd, "env") == 0)
		return (buildin_env(env));
	return (1);
}

//---redirect---
int	redirect_input(t_redirect *redirect)
{
	int	fd;

	// filenameの存在チェック
	if (!redirect->filename)
	{
		fprintf(stderr, "syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if (access(redirect->filename, F_OK) != 0)
	{
		printf("bash: %s: No such file or directory\n", redirect->filename);
		return (-1);
	}
	if (access(redirect->filename, R_OK) != 0)
	{
		printf("bash: %s: Permission denied\n", redirect->filename);
		return (-1);
	}
	fd = open(redirect->filename, O_RDONLY);
	return (fd);
}

// 同様に他のリダイレクト関数も修正
int	redirect_output(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	redirect_append(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}
int	redirect_heredoc(t_redirect *redirect)
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
		printf("command not found: %s\n", node->command[0]); //エラーメッセージ
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

	if (!node->command || !node->command[0])
	{
		printf("bash: command not found\n");
		return (EXIT_FAILURE);
	}
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
		if (access(cmd_path, X_OK) == 0)
		{
			if (execve(cmd_path, node->command, envp) == -1)
				perror(cmd_path);
			free(cmd_path);
			break ;
		}
		free(cmd_path);
		i++;
	}
	printf("command not found: %s\n", node->command[0]); // errorcheck
	free_path(path);
	free_envp(envp);
	return (0);
}

int	exec_command_get_fd(t_node *node, t_env *env, int input_fd)
{
	int		curr_pipe[2];
	pid_t	pid;

	if (pipe(curr_pipe) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (dup2(input_fd, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		if (dup2(curr_pipe[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(curr_pipe[0]);
		close(curr_pipe[1]);
		execute_nomal(node, env);
		exit(EXIT_FAILURE);
	}
	close(input_fd);
	close(curr_pipe[1]);
	return (curr_pipe[0]);
}

int	execute_pipeline(t_node *node, t_env *env)
{
	int			pipefd[2];
	pid_t		pid;
	int			status;
	int			input_fd;
	int			fd_in;
	int			fd_out;
	t_redirect	*current;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	input_fd = STDIN_FILENO;
	while (node)
	{
		if (node->next)
		{
			if (pipe(pipefd) < 0)
				exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
		{
			if (input_fd != STDIN_FILENO)
			{
				dup2(input_fd, STDIN_FILENO);
				close(input_fd);
			}
			if (node->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			current = node->redirects;
			while (current != NULL)
			{
				if (current->kind == RD_INPUT)
				{
					if (fd_in != STDIN_FILENO)
						close(fd_in);
					fd_in = redirect_input(current); // currentを引数に
					if (fd_in != -1)
					{
						dup2(fd_in, STDIN_FILENO);
						close(fd_in);
						fd_in = STDIN_FILENO; // 既にdup2したので標準入力になった
					}
				}
				else if (current->kind == RD_HEREDOC)
				{
					if (fd_in != STDIN_FILENO)
						close(fd_in);
					fd_in = redirect_heredoc(current);
					if (fd_in != -1)
					{
						dup2(fd_in, STDIN_FILENO);
						close(fd_in);
						fd_in = STDIN_FILENO;
					}
				}
				else if (current->kind == RD_OUTPUT)
				{
					if (fd_out != STDOUT_FILENO)
						close(fd_out);
					fd_out = redirect_output(current);
					if (fd_out != -1)
					{
						dup2(fd_out, STDOUT_FILENO);
						close(fd_out);
						fd_out = STDOUT_FILENO;
					}
				}
				else if (current->kind == RD_APPEND)
				{
					if (fd_out != STDOUT_FILENO)
						close(fd_out);
					fd_out = redirect_append(current);
					if (fd_out != -1)
					{
						dup2(fd_out, STDOUT_FILENO);
						close(fd_out);
						fd_out = STDOUT_FILENO;
					}
				}
				if (fd_in == -1 || fd_out == -1)
					return (EXIT_FAILURE);
				current = current->next;
			}
			if (is_builtin_command(node->command[0]))
				buildin_branch(node, env);
			else
				execute_nomal(node, env);
			exit(EXIT_SUCCESS);
		}
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (node->next)
		{
			close(pipefd[1]);
			input_fd = pipefd[0];
		}
		node = node->next;
	}
	while (wait(NULL) > 0)
		;
	return (EXIT_SUCCESS);
}

int	execute(t_node *node, t_env *env)
{
	int			input_fd;
	int			output_fd;
	t_redirect	*current;
	int			stdin_backup;
	int			stdout_backup;
	pid_t		pid;
	int			status;

	if (!node->command || !node->command[0])
		return (EXIT_FAILURE);
	if (node->next != NULL)
		execute_pipeline(node, env);
	else
	{
		input_fd = STDIN_FILENO;
		output_fd = STDOUT_FILENO;
		current = node->redirects;
		while (current != NULL)
		{
			if (current->kind == RD_INPUT)
			{
				if (input_fd != STDIN_FILENO)
					close(input_fd);
				input_fd = redirect_input(current);
			}
			else if (current->kind == RD_HEREDOC)
			{
				if (input_fd != STDIN_FILENO)
					close(input_fd);
				input_fd = redirect_heredoc(current);
			}
			else if (current->kind == RD_OUTPUT)
			{
				if (output_fd != STDOUT_FILENO)
					close(output_fd);
				output_fd = redirect_output(current);
			}
			else if (current->kind == RD_APPEND)
			{
				if (output_fd != STDOUT_FILENO)
					close(output_fd);
				output_fd = redirect_append(current);
			}
			if (input_fd == -1 || output_fd == -1)
				return (EXIT_FAILURE);
			if(input_fd != STDIN_FILENO)
				dup2(input_fd,STDIN_FILENO);
			current = current->next;
		}
		if (is_builtin_command(node->command[0]))
		{
			// 標準入出力のバックアップ
			stdin_backup = dup(STDIN_FILENO);
			stdout_backup = dup(STDOUT_FILENO);
			// リダイレクト適用
			if (input_fd != STDIN_FILENO)
				dup2(input_fd, STDIN_FILENO);
			if (output_fd != STDOUT_FILENO)
				dup2(output_fd, STDOUT_FILENO);
			// ビルトイン実行
			buildin_branch(node, env);
			// 標準入出力を元に戻す
			dup2(stdin_backup, STDIN_FILENO);
			dup2(stdout_backup, STDOUT_FILENO);
			close(stdin_backup);
			close(stdout_backup);
		}
		else // 外部コマンド
		{
			pid = fork();
			if (pid == 0)
			{
				// リダイレクト適用
				if (input_fd != STDIN_FILENO)
					dup2(input_fd, STDIN_FILENO);
				if (output_fd != STDOUT_FILENO)
					dup2(output_fd, STDOUT_FILENO);
				// コマンド実行
				execute_nomal(node, env);
				exit(EXIT_FAILURE);
			}
			else
			{
				waitpid(pid, &status, 0);
			}
		}
		// FDのクリーンアップ
		if (input_fd != STDIN_FILENO)
			close(input_fd);
		if (output_fd != STDOUT_FILENO)
			close(output_fd);
	}
	return (EXIT_SUCCESS);
}
