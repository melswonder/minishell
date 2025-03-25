/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 16:36:25 by hirwatan          #+#    #+#             */
/*   Updated: 2025/03/25 13:20:05 by hirwatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIP_H
# define PIP_H
# define BUFFER_SIZE 4096

# define DUP_ERROR 1
# define OPEN_ERROR 2
# define PIPE_ERROR 3
# define FORK_ERROR 4
# define EXECUTE_ERROR 5

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd_element
{
	char		***cmd;
	char		**cmd_path;
	int			command_count;
}				t_cmd_element;

// libft ok
int				ft_strlen(const char *str);
char			*ft_strjoin(char const *s1, char const *s2);
int				ft_strstr(const char *s1, const char *s2);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
static size_t	split_countwords(const char *s, char c);
static void		*mem_free(char **split, size_t word_i);
char			**ft_split(char const *s, char c);
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_memcpy(void *dest, const void *src, size_t n);
int				list_length(char **list);

// free ok
void			free_token_array(char **arr);
void			free_ce(t_cmd_element *ce);

// setting
int				sarch_path_index(char *envp[], t_cmd_element *ce);
int				countwords(char *str);
char			*first_path(char *str);
char			*after_path(char *str);
char			*add_path(char *str, int number);
char			**envp_split(char **envp, int path_index);
void			add_cmd_path(t_cmd_element *ce, char **envp, int path_index);
void			path_new(t_cmd_element *ce, char **envp);
t_cmd_element	*argv_to_exec_args(int argc, char *argv[], char *envp[]);

// execute
void			main_command_execution(t_cmd_element *ce, char **envp);
int				execute_first_command(t_cmd_element *ce, char **envp,
					int pipefd[2], int cmd_index);
int				execute_middle_command(t_cmd_element *ce, char **envp,
					int cmd_index, int input_fd);
int				normal_execution(t_cmd_element *ce, int cmd_number,
					char **envp);
void			execute_last_command(t_cmd_element *ce, char **envp,
					int input_fd, int cmd_index);
void			command_execution(t_cmd_element *ce, char **envp,
					int cmd_number);
// error
void			cmd_error(t_cmd_element *ce, int cmd_number);
void			execute_path_or_executable_file(t_cmd_element *ce,
					int cmd_number);
void			check_file_permissions_exist(t_cmd_element *ce);
void			ft_error(int error_number);
void			data_validation_check(t_cmd_element *ce);
void			unset_path_error(t_cmd_element *ce, int cmd_number);
int				exit_check_unset_path(t_cmd_element *ce);
void			execute_file_error(t_cmd_element *ce, int cmd_number);
void			ft_infile_error(int pipefd[2]);

// dev
void			print_command(t_cmd_element *ce);
#endif