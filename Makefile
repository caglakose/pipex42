# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cakose <cakose@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 16:14:20 by cakose            #+#    #+#              #
#    Updated: 2024/11/14 17:52:03 by cakose           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROG    = pipex

SRCS    = srcs/pipex.c srcs/utils.c srcs/execute.c
OBJS    = ${SRCS:.c=.o}
MAIN    = srcs/pipex.c

HEADER  = -Iincludes

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g

.c.o:
		${CC} ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all: ${PROG}

${PROG}: ${OBJS}
		make re -C ./libft
		$(CC) ${OBJS} -Llibft -lft -o ${PROG}

clean:
		make clean -C ./libft
		rm -f ${OBJS}

fclean: clean
		make fclean -C ./libft
		rm -f ${PROG}

re: fclean
	make all

.PHONY: all clean fclean re