# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lantonio <lantonio@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/11 16:35:01 by lantonio          #+#    #+#              #
#    Updated: 2024/10/14 08:26:51 by lantonio         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC		= cc -fsanitize=thread
FLAGS	= -Wall -Wextra -Werror

SRCS	= philosophers.c\
			./srcs/run.c\
			./srcs/utils.c\
			./srcs/initialize.c\
			./srcs/take_forks.c\
			./srcs/get_and_set.c\

OBJS	= $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -Iincludes -o $(NAME)
	@echo "\033[1;32mSUCESS"

%.o:%.c
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean :
	@rm -rf $(OBJS)
	@echo "Cleaning objects"

fclean : clean
	@rm -rf $(NAME)
	@echo "cleaning executable"

re : fclean all

.PHONY : all clean fclean re