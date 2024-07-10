# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfabi <sfabi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/16 15:36:03 by sfabi             #+#    #+#              #
#    Updated: 2024/04/10 13:35:24 by sfabi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS = ft_printf.c logic.c stamp.c utils.c utils2.c utils3.c
OBJS = ${SRCS:.c=.o}
HEADER = ft_printf.h
AR = ar rsc

.c.o:
	cc -Wall -Wextra -Werror -c $?

all: ${NAME}

${NAME}: ${OBJS}
	$(AR) $@ $?

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}
	
bonus: re

re: fclean all
