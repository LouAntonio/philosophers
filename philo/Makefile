# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 16:35:01 by lantonio          #+#    #+#              #
#    Updated: 2024/09/23 17:25:15 by lantonio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosophers
CC		= cc
FLAGS	= -Wall -Wextra -Werror

SRCS	= philosophers.c\
			./srcs/run.c\
			./srcs/utils.c\
			./srcs/getters.c\
			./srcs/initialize.c\

OBJS	= $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -Iincludes -o $(NAME)

all: $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re