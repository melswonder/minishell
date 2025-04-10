/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 00:00:00 by user              #+#    #+#             */
/*   Updated: 2025/04/11 01:29:58 by kiwasa           ###   ########.fr       */
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

//---tokenize---
t_token		*tokenize(char *line, t_shell *shell);
int			is_reserved(char c);
t_token		*tokenize_reserved(char **line);
t_token		*tokenize_word(char **line, t_shell *shell);
char		*extract_word(char **line, t_shell *shell);
t_token		*new_token(t_token_kind kind, char *word);
void		add_token(t_token **tokens, t_token *new);
int			is_space(char c);

//---parse---
t_node		*parse(t_token *tokens, t_shell *shell);
t_node		*parse_command_node(t_token **token_ptr, t_shell *shell);
int			count_command_words(t_token *token);
char		**create_command_array(t_token *token, int count);
t_token		*handle_command(t_node	*node, t_token *token);
t_token		*handle_redirect(t_node *node, t_token *token, t_shell *shell);
t_node		*new_node(void);
t_redirect	*new_redirect(t_redirect_kind kind, char *filename);
void		add_redirect_to_node(t_node *node, t_redirect *redirect);


//---init---
t_env		*init_env(char **envp);
t_shell		*init_shell(t_env *env);

//---free---
void		free_all_nodes(t_node *head);
void		free_node(t_node *node);
void		free_tokens(t_token *tokens);
void		free_env(t_env *env);

//---signal---
void		signal_handler(int sig);
void		setup_signal(void);

//---debug---
void	print_node(t_node *node);

//---minishell---
void		minishell_loop(t_env *env, t_shell *shell);

//---expand---
void expand_variable(t_shell *shell);

char		*get_env_value(t_env *env, char *key);
void		set_env_value(t_env *env, char *key, char *value);

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

//---buildin---

char	*ft_strjoin(char const*s1, char const *s2);
int	buildin_branch(t_node *node, t_env *env);
int	buildin_unset(t_node *node, t_env **env);
int	buildin_echo(t_node *node);
int	buildin_cd(t_node *node, t_env *env);
int	buildin_exit(t_node *node);
int	buildin_export(t_node *node,t_env *env);
int	buildin_env(t_env *env);
int	buildin_pwd(void);
//---buildin---

//---execute---
int	execute(t_shell *shell);

#endif