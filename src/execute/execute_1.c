/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:31:19 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/12 18:27:48 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 実行ファイルに実行権限がない際, command not found が表示された
// ., ..: Permission denied
// エラー文が標準出力に出力されていた
// 無効なコマンドを入力するとstill reachableが増える
// 終了ステータスが無効なコマンド時, シグナル時に0
// quote
// PATHをunsetするとエラーが表示されない
// echo '|': シングルクォートが外されない('|')
// redirect
// chmod -w a.txt    ->     echo hello > a.txt: Permissionエラーが表示されない
// pipeを利用した複数でも表示されない
// リダイレクトが先頭に来るとコマンドが実行されない
// cat << EOF: ctrl+Cでminishellが終了する
// pipe
// a | b | c: cのエラーのみだった
// signal
// cat    ->    ctrl+\: core-dumpが表示されない
// cat    ->    ctrl+c: 改行がない
// builtin
// export: 内容のない変数が表示されてしまっていた
// echo a b c d e: ab c d eが表示されてしまう
// echo -n -n: で-nが表示されてしまう

#include "../../inc/minishell.h"

//---util
int	wifexited(int status)
{
	return ((status & 0x7F) == 0);
}

int	wexitstatus(int status)
{
	return ((status >> 8) & 0xff);
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

//---path
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

///---buildin---
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
///---buildin---

//---redirect---
int	open_input_redirect(t_redirect *redirect)
{
	// filenameの存在チェック
	if (!redirect->filename)
	{
		fprintf(stderr, "syntax error near unexpected token `newline'\n");
		return (-1);
	}
	if (access(redirect->filename[0], F_OK) != SUCCESS)
	{
		printf("bash: %s: No such file or directory\n", redirect->filename);
		return (-1);
	}
	if (access(redirect->filename[0], R_OK) != SUCCESS)
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

void	process_heredoc_content(int pipe_fd[2], char *delimiter)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, signal_exit);
		line = readline("> ");
		if (!line)
		{
			write(2, "warning: here-document at line 1 delimited by EOF\n", 50);
			break ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	signal(SIGINT, signal_handler);
}

// メイン関数
int	open_heredoc_redirect(t_redirect *redirect)
{
	int	pipe_fd[2];

	if (access(redirect->filename[0], W_OK) != SUCCESS)
	{
		write(2, "bash: ", 6);
		write(2, redirect->filename[0], strlen(redirect->filename[0]));
		write(2, ": Permission denied\n", 20);
		exit(1);
	}
	if (!redirect->filename)
	{
		write(2, "syntax error near unexpected token `newline'\n", 45);
		return (-1);
	}
	if (pipe(pipe_fd) == -1)
		return (-1);
	process_heredoc_content(pipe_fd, redirect->filename);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

//---free---
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
//---free

int	input_heredoc_redirect(t_redirect *current, int *fd_in)
{
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
	return (0);
}

int	output_append_redirect(t_redirect *current, int *fd_out)
{
	if (current->kind == RD_OUTPUT)
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
	return (0);
}

int	apply_redirections(t_redirect *current, int *fd_in, int *fd_out)
{
	if (current == NULL)
		return (0);
	if (current->kind == RD_INPUT || current->kind == RD_HEREDOC)
		input_heredoc_redirect(current, fd_in);
	else if (current->kind == RD_OUTPUT || current->kind == RD_APPEND)
		output_append_redirect(current, fd_out);
	if (*fd_in == -1 || *fd_out == -1)
		return (EXIT_FAILURE);
	return (0);
}
//---redirect---

//---execute---

int	is_directry(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/' && str[i] != '.')
			return (0);
		i++;
	}
	return (1);
}

void	print_is_directory(char *str)
{
	write(2, "bash: ", 6);
	write(2, str, strlen(str));
	write(2, ": Is a directory\n", 17);
	exit(126); // not free
}

void	execute_direct_path(t_node *node, t_env *env)
{
	char	**envp;

	envp = convert_env_to_array(env);
	if (execve(node->command[0], node->command, envp) == -1)
	{
		if (is_directry(node->command[0]))
			print_is_directory(node->command[0]);
		else if (access(node->command[0], F_OK) != 0)
		{
			write(2, "bash:  ", 7);
			write(2, node->command[0], strlen(node->command[0]));
			write(2, ":  No such file or directory\n", 29);
		}
		else if (access(node->command[0], X_OK) != 0)
		{
			write(2, "bash:", 5);
			write(2, node->command[0], strlen(node->command[0]));
			write(2, "Permission denied\n", 18);
		}
		free_env_array(envp);
	}
	free_env_array(envp);
}

void	search_command_in_path(t_node *node, t_env *env, char **path)
{
	int		i;
	char	*cmd_path;
	char	**envp;

	i = 0;
	envp = convert_env_to_array(env);
	while (path && path[i])
	{
		cmd_path = join_three_strings(path[i], "/", node->command[0]);
		if (!cmd_path)
		{
			i++;
			continue ;
		}
		if (access(cmd_path, X_OK) == 0)
		{
			execve(cmd_path, node->command, envp);
			perror(cmd_path);
			free(cmd_path);
			break ;
		}
		free(cmd_path);
		i++;
	}
	if (path)
		free_path_array(path);
	if (envp)
		free_env_array(envp);
}

// メイン関数
int	execute_normal(t_node *node, t_env *env)
{
	char	**path;

	if (!node->command || !node->command[0])
	{
		write(2, "bash: command not found\n", 24);
		exit(EXIT_FAILURE);
	}
	if (node->command[0][0] == '/' || (node->command[0][0] == '.'
			&& node->command[0][1] == '/'))
	{
		execute_direct_path(node, env);
		exit(0);
	}
	path = create_path_array(env);
	search_command_in_path(node, env, path);
	write(2, node->command[0], strlen(node->command[0]));
	write(2, ": command not found", 19);
	write(2, "\n", 1);
	exit(127);
}
//---execute---

// 子プロセスでのパイプライン実行
void	execute_pipeline_child(t_node *node, t_env *env, int fd_in, int *pipefd,
		int fd_out)
{
	t_redirect	*redirect;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (node->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	redirect = node->redirects;
	while (redirect)
	{
		if (apply_redirections(redirect, &fd_in, &fd_out) != 0)
			exit(EXIT_FAILURE);
		redirect = redirect->next;
	}
	if (is_builtin(node->command[0]))
		exit(execute_builtin_command(node, env));
	else
		execute_normal(node, env);
}

// メイン関数
int	execute_pipeline(t_shell *shell, int fd_in, int fd_out, pid_t pid)
{
	int		pipefd[2];
	t_node	*node;

	node = shell->head;
	while (node)
	{
		if (node->next && pipe(pipefd) < 0)
			exit(EXIT_FAILURE);
		pid = fork();
		if (pid < 0)
			exit(EXIT_FAILURE);
		if (pid == 0)
			execute_pipeline_child(node, shell->env, fd_in, pipefd, fd_out);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
		if (node->next)
		{
			close(pipefd[1]);
			fd_in = pipefd[0];
		}
		node = node->next;
	}
	while (wait(NULL) > 0)
		;
	return (EXIT_SUCCESS);
}

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
		if (wifexited(status))
			status = wexitstatus(status);
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

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (shell->head->next != NULL)
	{
		execute_pipeline(shell, fd_in, fd_out, pid);
		return (0);
	}
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
		shell->status = execute_single(shell, fd_in, fd_out);
	return (EXIT_SUCCESS);
}
