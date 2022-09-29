# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmendes <jmendes@student.42lisboa.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/29 05:23:06 by jmendes           #+#    #+#              #
#    Updated: 2022/09/29 02:59:17 by jmendes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
FLAGS = -Wall -Wextra -Werror -fsanitize=address
RM = rm -f

NAME = pipex
INCLUDE = pipex.h 

SRC = $(wildcard ./src/*.c)

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) 
	gcc	 $(OBJS) $(FLAGS) -o $(NAME)

.c.o: $(CC) $(FLAGS) -I$(INCLUDE) -c $< -o $(<:.c=.o)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
