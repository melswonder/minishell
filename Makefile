# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 20:58:32 by hirwatan          #+#    #+#              #
#    Updated: 2025/04/06 21:05:24 by hirwatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRCS = src/tokenizer.c src/parser.c src/debug.c src/buildin.c src/minishell.c src/execute.c
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