# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edubois- <edubois-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/21 11:39:27 by edubois-          #+#    #+#              #
#    Updated: 2025/04/01 13:42:57 by edubois-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS =	srcs/main.c\
		srcs/utils/utils.c\
		srcs/handle_philo.c\
		srcs/utils/init.c\
		srcs/make_actions.c\

OBJS 			:= $(SRCS:.c=.o)

CC 				:= @cc

FLAGS 			:= -Wall -Wextra -Werror -g

.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compilation de $(NAME)"
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)
	sleep 0.7
	clear

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "Suppresion des objets..." 
	rm -f $(OBJS)

fclean: clean
	@echo "Suppresion des executables..." 
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
