# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hirwatan <hirwatan@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/13 16:59:23 by hirwatan          #+#    #+#              #
#    Updated: 2025/03/21 19:43:57 by hirwatan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
SRCS = src/path_util.c src/path_util2.c src/pipex_utils.c src/pipex_utils2.c src/pipex_split.c\
		 src/free.c src/dev.c src/cmd_error.c src/execute.c src/unsetpath_permission_error.c src/main.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFRAG = -Wall -Wextra -Werror -I .

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)
	chmod 777 $(NAME)

all: $(NAME)

.c.o:
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	
v: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

re: fclean all