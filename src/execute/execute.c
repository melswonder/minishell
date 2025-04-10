#include "../../inc/minishell.h"

// TK_WORD
// TK_RESERVED
// TK_EOF

int	is_builtin(char *str)
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

int	execute_builtin_command(t_node *node, t_env *env)
{
	char	*cmd;

	cmd = node->command[0];
	if (strcmp(cmd, "echo") == 0)
		return (buildin_echo(node));
	else if (strcmp(cmd, "exit") == 0)
		return (buildin_exit(node));
	else if (strcmp(cmd, "cd") == 0)
		return (buildin_cd(node, env));
	else if (strcmp(cmd, "pwd") == 0)
		return (buildin_pwd());
	else if (strcmp(cmd, "export") == 0)
		return (buildin_export(node, env));
	else if (strcmp(cmd, "unset") == 0)
		return (buildin_unset(node, &env));
	else if (strcmp(cmd, "env") == 0)
		return (buildin_env(env));
	return (1);
}

//---redirect---
int	open_input_redirect(t_redirect *redirect)
{
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
	return (open(redirect->filename, O_RDONLY));
}

// 同様に他のリダイレクト関数も修正
int	open_output_redirect(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (fd);
}

int	open_append_redirect(t_redirect *redirect)
{
	int	fd;

	fd = open(redirect->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (fd);
}

int	open_heredoc_redirect(t_redirect *redirect)
{
	int		pipe_fd[2];
	char	*line;
	char	*delimiter;

	// signal(SIGINT, signal_exit);
	if (!redirect->filename)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (-1);
	}
	delimiter = redirect->filename;
	if (pipe(pipe_fd) == -1)
		return (-1);
	while (1)
	{
		signal(SIGINT,signal_exit);
		line = readline("> "); // プロンプトに空白を追加
		if (!line)             // Ctrl+Dが入力された場合
		{
			printf("warning: here-document at line 1 delimited by EOF\n");
			break ;
		}
		if (strcmp(line, delimiter) == 0) // デリミタと一致した場合に終了
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	signal(SIGINT, signal_handler);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	apply_redirections(t_redirect *current, int *fd_in, int *fd_out)
{
	if (current == NULL)
		return (0);
	if (current->kind == RD_INPUT)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = open_input_redirect(current);
	}
	else if (current->kind == RD_HEREDOC)
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = open_heredoc_redirect(current);
	}
	else if (current->kind == RD_OUTPUT)
	{
		if (*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out = open_output_redirect(current);
	}
	else if (current->kind == RD_APPEND)
	{
		if (*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out = open_append_redirect(current);
	}
	if (*fd_in == -1 || *fd_out == -1)
		return (EXIT_FAILURE);
	return (0);
}

//---addpath---

char	**split_path_env(char *path)
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
	result = malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
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

char	**create_path_array(t_env *env)
{
	char	**path;

	path = NULL;
	while (env)
	{
		if (strcmp(env->key, "PATH") == 0)
			path = split_path_env(env->value);
		env = env->next;
	}
	if (!path)
		return (NULL);
	return (path);
}

void	free_path_array(char **path)
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

char	**convert_env_to_array(t_env *env)
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

void	free_env_array(char **envp)
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

char	*join_three_strings(char const *s1, char const *s2, char const *s3)
{
	char	*ret;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	ret = ft_strjoin(tmp, s3);
	free(tmp);
	return (ret);
}

// unset PATH用の実行
void	execute_direct_path(t_node *node, t_env *env)
{
	char	**envp;

	envp = convert_env_to_array(env);
	if (execve(node->command[0], node->command, envp) == -1)
	{
		printf("command not found: %s\n", node->command[0]); //エラーメッセージ
		free_env_array(envp);
	}
	free_env_array(envp);
}

// execute_normal: 外部コマンドの実行（PATH 内からコマンドを探す）
int	execute_normal(t_node *node, t_env *env)
{
	char	**path;
	int		i;
	char	*cmd_path;
	char	**envp;

	if (!node->command || !node->command[0])
	{
		printf("bash: command not found\n");
		exit(EXIT_FAILURE);
	}
	if (node->command[0][0] == '/' || (node->command[0][0] == '.'
			&& node->command[0][1] == '/'))
	{
		execute_direct_path(node, env);
		exit(0);
	}
	i = 0;
	path = create_path_array(env);
	envp = convert_env_to_array(env);
	while (path[i])
	{
		cmd_path = join_three_strings(path[i], "/", node->command[0]);
		if (!cmd_path)
		{
			i++;
			continue ;
		}
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
	if(path)
		free_path_array(path);
	if(envp)
		free_env_array(envp);
	printf("command not found: %s\n", node->command[0]);
	exit(127);
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
				if (apply_redirections(current, &fd_in, &fd_out) != 0)
					exit(EXIT_FAILURE);
				current = current->next;
			}
			if (fd_in != STDIN_FILENO)
				dup2(fd_in, STDIN_FILENO);
			if (fd_out != STDOUT_FILENO)
				dup2(fd_out, STDOUT_FILENO);
			if (is_builtin(node->command[0]))
				execute_builtin_command(node, env);
			else
				execute_normal(node, env);
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
//---refuct---

int	execute_builtin_with_redirect(t_shell *shell, int *fd_in, int *fd_out)
{
	int	stdin_backup;
	int	stdout_backup;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	if (*fd_in != STDIN_FILENO)
		dup2(*fd_in, STDIN_FILENO);
	if (*fd_out != STDOUT_FILENO)
		dup2(*fd_out, STDOUT_FILENO);
	execute_builtin_command(shell->head, shell->env);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	if (*fd_in != STDIN_FILENO)
	{
		close(*fd_in);
		*fd_in = STDIN_FILENO;
	}
	if (*fd_out != STDOUT_FILENO)
	{
		close(*fd_out);
		*fd_out = STDOUT_FILENO;
	}
	return (0);
}

int	execute_single(t_shell *shell, int fd_in, int fd_out)
{
	pid_t	pid;
	int		status;

	status = 0;
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (fd_in != STDIN_FILENO)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out != STDOUT_FILENO)
			dup2(fd_out, STDOUT_FILENO);
		execute_normal(shell->head, shell->env);
	}
	else
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	return (status);
}

int	execute(t_shell *shell)
{
	int			fd_in;
	int			fd_out;
	pid_t		pid;
	t_redirect	*current;
	int			status;

	if (!shell->head->command || !shell->head->command[0])
		return (EXIT_FAILURE);
	if (shell->head->next != NULL)
		return (execute_pipeline(shell->head, shell->env), 0);
	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	current = shell->head->redirects;
	while (current != NULL)
	{
		if (apply_redirections(current, &fd_in, &fd_out) != 0)
			return (EXIT_FAILURE);
		current = current->next;
	}
	if (is_builtin(shell->head->command[0]))
		execute_builtin_with_redirect(shell, &fd_in, &fd_out);
	else //単一コマンド
		status = execute_single(shell, fd_in, fd_out);
	return (EXIT_SUCCESS);
}
