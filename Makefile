# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lminta <lminta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/02 20:58:32 by lminta            #+#    #+#              #
#    Updated: 2019/05/08 15:24:30 by lminta           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

INC = libft

FLAGS = -Wall -Werror -Wextra -c

OBJ = map.o \
move.o \
read.o \
control.o

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(INC)
	gcc $(OBJ) $(INC)/libft.a -o $(NAME)

$(OBJ): %.o: %.c
	gcc $(FLAGS) -I$(INC) $< -o $@

clean:
	make -C $(INC) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(INC) fclean
	rm -f $(NAME)

re: fclean all
