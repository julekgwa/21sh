# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julekgwa <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/14 07:28:36 by julekgwa          #+#    #+#              #
#    Updated: 2016/05/14 07:28:53 by julekgwa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
SRC = ./src/main.c ./src/cmd/ft_commands.c ./src/signals/ft_ctrl_c_signal_handler.c \
	./src/cmd/ft_cd.c ./src/cmd/ft_echo.c ./src/env/ft_env.c ./src/utils/ft_utils.c \
	./src/utils/ft_get_data.c ./src/utils/ft_cmd_utils.c ./src/memory/ft_free.c
OBJECT = main.o ft_commands.o ft_ctrl_c_signal_handler.o ft_cd.o ft_echo.o \
	ft_env.o ft_utils.o ft_get_data.o ft_cmd_utils.o ft_free.o
FLAGS = -Wall -Wextra -Werror -g3
OPTIONS = -c -I libft/includes/ -I includes/

all: $(NAME)

$(NAME):
	@make -C libft/
	@gcc $(FLAGS) $(OPTIONS) $(SRC)
	@gcc -o $(NAME) $(OBJECT) -L libft/ -lft
	@chmod 777 $(NAME)
	@echo "\x1B[32mCompiled project.\x1B[0m"

clean:
	@make -C libft/ clean
	@/bin/rm -f $(OBJECT)
	@echo "\x1B[32mCleaned up object files.\x1B[0m"

fclean: clean
		@make -C libft/ fclean
		@/bin/rm -f $(NAME)
		@echo "\x1B[32mCleaned up compiled files.\x1B[0m"

re: fclean	all
