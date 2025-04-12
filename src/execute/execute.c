/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:31:19 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/13 03:00:08 by hirwatan         ###   ########.fr       */
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

// リダイレクトを適用する
void	setup_redirections(t_redirect *redirect, int *local_fd_in,
		int *local_fd_out)
{
	while (redirect)
	{
		if (apply_redirections(redirect, local_fd_in, local_fd_out) != 0)
			exit(EXIT_FAILURE);
		redirect = redirect->next;
	}
}

pid_t	execute_pipeline_node(t_node *node, t_env *env, int fd_in,
		int *next_pipe)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (node->next && pipe(pipe_fd) < 0)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid == 0)
	{
		if (node->next)
			execute_child_process(node, env, fd_in, pipe_fd);
		else
			execute_child_process(node, env, fd_in, next_pipe);
	}
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (node->next)
	{
		close(pipe_fd[1]);
		*next_pipe = pipe_fd[0];
	}
	return (pid);
}

int	execute_pipeline(t_shell *shell, int fd_in, int fd_out, pid_t pid)
{
	t_node	*current;
	int		next_fd;

	current = shell->head;
	next_fd = fd_in;
	while (current)
	{
		pid = execute_pipeline_node(current, shell->env, next_fd, &next_fd);
		current = current->next;
	}
	while (wait(NULL) > 0)
		;
	return (EXIT_SUCCESS);
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
	else
		shell->status = execute_single(shell, fd_in, fd_out);
	return (EXIT_SUCCESS);
}
