# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 20:58:32 by hirwatan          #+#    #+#              #
#    Updated: 2025/04/12 19:52:21 by hirwatan         ###   ########.fr        #
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
		src/buildin/buildin_echo.c \
		src/buildin/buildin_exit.c \
		src/buildin/buildin_cd.c \
		src/buildin/buildin_pwd.c \
		src/buildin/buildin_env.c \
		src/buildin/buildin_unset.c \
		src/buildin/buildin_export.c \
		src/buildin/buildin_export_utils.c \
		src/buildin/buildin_export_utils2.c \
		src/minishell/minishell.c \
		src/execute/execute.c \
		src/expand/expand_quote.c \
		src/expand/expand_redirect.c \
		src/expand/expand_special.c \
		src/expand/expand_utils.c \
		src/expand/expand_variable.c \
		src/free/free.c \
		src/init/init.c \
		src/main.c

OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS =
#CFLAGS = -Wall -Wextra -Werror -I .

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lreadline
	chmod 777 $(NAME)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
    
v: $(NAME) clean
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=all ./$(NAME)

re: fclean all

.PHONY: all clean fclean re