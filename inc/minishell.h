/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/04/10 11:22:35 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
#include <ctype.h>


#define SINGLE_QUOTE_CHAR '\''
#define DOUBLE_QUOTE_CHAR '"'

extern volatile sig_atomic_t	g_signal;

typedef enum e_token_kind
{
	TK_WORD,
	TK_RESERVED,
	TK_EOF,
}	t_token_kind;

typedef struct s_token
{
	t_token_kind		kind;
	char				*word;
	struct s_token		*next;
}	t_token;

// [fix] parser struct
typedef enum e_redirect_kind
{
    RD_INPUT,
    RD_OUTPUT,
    RD_APPEND,
    RD_HEREDOC,
}    t_redirect_kind;

typedef struct s_redirect
{
    t_redirect_kind  kind;
    char             *filename;
    struct s_redirect    *next;
}    t_redirect;

typedef struct s_node
{
    char           **command;
    t_redirect     *redirects;
    struct s_node  *next;
}    t_node;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_shell
{
    t_env   *env;
    t_node  *head;
    bool    syntax_error;
    int     status;
}   t_shell;

t_token		*tokenize(char *line, t_shell *shell);
void		free_tokens(t_token *tokens);

t_node		*parse(t_token *tokens, t_shell *shell);
void		free_node(t_node *node);


t_env		*init_env(char **envp);
char		*get_env_value(t_env *env, char *key);
void		set_env_value(t_env *env, char *key, char *value);
void		free_env(t_env *env);

int			is_builtin(char *cmd);
int			exec_builtin(char **cmd, t_env *env);
int			builtin_echo(char **args);
int			builtin_cd(char **args, t_env *env);
int			builtin_pwd(void);
int			builtin_export(char **args, t_env *env);
int			builtin_unset(char **args, t_env *env);
int			builtin_env(t_env *env);
int			builtin_exit(char **args);

char		**env_to_array(t_env *env);
void		free_array(char **array);

void		signal_handler(int sig);
void		setup_signal(void);
void		minishell_loop(t_env *env);
void		unset_env(t_env **env, char *key);

void	add_redirect(t_redirect **list, t_redirect *new);
t_redirect	*new_redirect(t_redirect_kind kind, char *filename);
t_redirect_kind	get_redirect_kind(t_token *token);
int	match(t_token *token, char *str);
t_env	*new_env_entry(char *key, char *value);
int	apply_input_redirect(t_redirect *redirect);
int	apply_output_redirect(t_redirect *redirect);
int	apply_append_redirect(t_redirect *redirect);
int	apply_heredoc(t_redirect *redirect);
void	execute_child(t_node *node, t_env *env);
char	*find_command_path(char *cmd, t_env *env);
void	execute_child(t_node *node, t_env *env);
int	apply_redirects(t_redirect *redirects);
int	execute_simple_command(t_node *node, t_env *env);

//--debugchar	*ft_strjoin(char *s1, char *s2)

//---buildin---

char	*ft_strjoin(char const*s1, char const *s2);
int	buildin_branch(t_node *node, t_env *env);
int	buildin_unset(t_node *node, t_env **env);
int	buildin_echo(t_node *node, t_env *env);
int	buildin_cd(t_node *node, t_env *env);
int	buildin_exit(t_node *node);
int	buildin_export(t_env *env);
int	buildin_env(t_env *env);
int	buildin_pwd(void);
//---buildin---

//---execute---
int	execute(t_shell *shell);
//---execute---


//---expand---
void expand_variable(t_shell *shell);
//---expand---

//---print_node---
void	print_node(t_node *node);
//---print_node---
#endif