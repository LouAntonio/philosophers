# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 16:35:01 by lantonio          #+#    #+#              #
#    Updated: 2024/09/23 13:46:39 by lantonio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philosophers
CC		=  cc
FLAGS	= -Wall -Wextra -Werror

SRCS	= philosophers.c\
			./srcs/utils.c\
			./srcs/initialize.c\
			./srcs/run.c\
			./srcs/getters.c\

OBJS	= $(SRCS:.c=.o)

%.c:%.0
	@$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -Iincludes -o $(NAME)

all: $(NAME)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re