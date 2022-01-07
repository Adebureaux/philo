# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adeburea <adeburea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/06 15:43:50 by adeburea          #+#    #+#              #
#    Updated: 2022/01/07 18:29:20 by adeburea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
NAME	=	philo
FLAGS	=	-Wall -Wextra -Werror
INC		=	philo.h
OBJ		=	objs
OBJS	=	$(addprefix $(OBJ)/, $(SRCS:.c=.o))
SRCS 	=	main.c \
			philo.c \
			init.c \
			routine.c \
			ft_digit.c \
			ft_string.c

$(NAME): $(LIBFT) $(OBJ) $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

$(OBJ):
	@mkdir -p $(OBJ)

$(OBJ)/%.o: ./%.c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
