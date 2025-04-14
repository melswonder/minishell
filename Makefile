# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 20:58:32 by hirwatan          #+#    #+#              #
#    Updated: 2025/04/14 21:32:20 by hirwatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = 	src/tokenizer/tokenizer.c \
		src/tokenizer/token_reserved.c \
		src/tokenizer/token_utils.c \
		src/tokenizer/token_word.c \
		src/parser/parser.c \
		src/parser/parse_node.c \
		src/parser/node_utils.c \
		src/parser/command_handler.c \
		src/parser/redirect_handler.c \
		src/debug/debug.c \
		src/signal/signal.c \
		src/buildin/buildin.c \
		src/buildin/buildin_echo.c \
		src/buildin/buildin_exit.c \
		src/buildin/buildin_cd.c \
		src/buildin/buildin_cd_utils.c \
		src/buildin/buildin_pwd.c \
		src/buildin/buildin_env.c \
		src/buildin/buildin_unset.c \
		src/buildin/buildin_export.c \
		src/buildin/buildin_export_utils.c \
		src/buildin/buildin_export_utils2.c \
		src/minishell/minishell.c \
		src/execute/execute.c \
		src/execute/execute_child.c \
		src/execute/execute_utils.c \
		src/execute/execute_utils2.c \
		src/redirect/redirect_input.c \
		src/redirect/redirect_output.c \
		src/redirect/redirect.c \
		src/expand/expand_quote.c \
		src/expand/expand_redirect.c \
		src/expand/expand_special.c \
		src/expand/expand_utils.c \
		src/expand/expand_variable.c \
		src/env/env.c \
		src/path/path.c \
		src/free/free.c \
		src/free/free_exec.c \
		src/init/init.c \
		src/main.c

LIBFT	= libft/libft.a
OBJS 	= $(SRCS:.c=.o)
CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -I./libft -I./inc

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline 

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all
    
v: $(NAME) clean
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME)

.PHONY: all clean fclean re