# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kiwasa <kiwasa@student.42.jp>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 20:58:32 by hirwatan          #+#    #+#              #
#    Updated: 2025/04/11 02:08:12 by kiwasa           ###   ########.fr        #
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

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
    
v: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re: fclean all