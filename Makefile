# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmendes <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/29 05:23:06 by jmendes           #+#    #+#              #
#    Updated: 2021/07/31 20:36:58 by jmendes          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc 
FLAGS = -Wall -Wextra -Werror -fsanitize=address
RM = rm -f

NAME = pipex
INCLUDE = pipex.h 

SRC = pipex.c\
	  pipex1.c\
	  utils.c\
	  utils1.c\

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
