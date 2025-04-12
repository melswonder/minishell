/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:31:19 by hirwatan          #+#    #+#             */
/*   Updated: 2025/04/12 21:27:58 by hirwatan         ###   ########.fr       */
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

// void	execute_pipeline_child(t_shell *shell, int fd_in, int *pipefd,
// 		int fd_out)
// {
// 	t_redirect	*redirect;

// 	signal(SIGINT, SIG_DFL);
// 	signal(SIGQUIT, SIG_DFL);
// 	if (fd_in != STDIN_FILENO)
// 	{
// 		dup2(fd_in, STDIN_FILENO);
// 		close(fd_in);
// 	}
// 	if (shell->head->next)
// 	{
// 		close(pipefd[0]);
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		close(pipefd[1]);
// 	}
// 	redirect = shell->head->redirects;
// 	while (redirect)
// 	{
// 		if (apply_redirections(redirect, &fd_in, &fd_out) != 0)
// 			exit(EXIT_FAILURE);
// 		redirect = redirect->next;
// 	}
// 	if (is_builtin(shell->head->command[0]))
// 		exit(execute_builtin_command(shell->head, shell->env));
// 	else
// 		execute_normal(shell->head, shell->env);
// }

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
	else
		shell->status = execute_single(shell, fd_in, fd_out);
	return (EXIT_SUCCESS);
}
