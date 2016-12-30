# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julekgwa <julekgwa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/08/06 14:38:52 by ktshikot          #+#    #+#              #
#    Updated: 2016/12/30 06:49:14 by julekgwa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
SRC = ./src/main.c ./src/commands/ft_commands.c ./src/utils/ft_ctrl_c_signal_handler.c \
	./src/commands/ft_cd.c ./src/commands/ft_echo.c ./src/env/ft_env.c \
	./src/utils/ft_utils.c ./src/exec/ft_get_data.c ./src/history/ft_history.c \
	./src/utils/ft_more_utils.c ./src/keyboard/ft_ctrl_keyboard.c ./src/signals/ft_signals.c\
	./src/keyboard/ft_ctrl_terminal.c ./src/keyboard/ft_term_utils.c ./src/pipe/ft_manage_pipes.c \
	./src/buffer/ft_manage_buff.c ./src/history/ft_hist_utils.c ./src/memory/ft_free.c \
	./src/utils/ft_cmd_utils.c ./src/env/ft_env_utils.c ./src/redirection/ft_redirection.c \
	./src/redirection/ft_redirection_utils.c ./src/redirection/ft_here_doc.c \
	./src/parenthesis/ft_parenthesis.c ./src/parenthesis/ft_parenthesis_utils.c \
	./src/redirection/ft_here_doc_utils.c ./src/env/ft_export.c ./src/logical/ft_logical_op.c \
	./src/history/ft_bck_i_search.c ./src/history/ft_manage_hist.c ./src/copy/ft_cut.c \
	./src/auto/ft_auto_search.c ./src/auto/ft_auto_utils.c ./src/auto/ft_auto_misc.c \
	./src/hash_table/ft_hash_table.c ./src/hash_table/ft_hash_table_utils.c \
	./src/exec/ft_execute.c ./src/substitution/ft_sub.c
OBJECT = main.o ft_commands.o ft_ctrl_c_signal_handler.o ft_cd.o ft_echo.o \
	ft_env.o ft_utils.o ft_get_data.o ft_more_utils.o ft_ctrl_terminal.o \
	ft_term_utils.o ft_ctrl_keyboard.o ft_manage_pipes.o ft_manage_buff.o \
	ft_history.o ft_signals.o ft_hist_utils.o ft_free.o ft_cmd_utils.o ft_env_utils.o \
	ft_redirection.o ft_redirection_utils.o ft_here_doc.o ft_parenthesis.o \
	ft_parenthesis_utils.o ft_here_doc_utils.o ft_export.o ft_logical_op.o \
	ft_bck_i_search.o ft_manage_hist.o ft_cut.o ft_auto_search.o ft_auto_utils.o \
	ft_auto_misc.o ft_hash_table.o ft_hash_table_utils.o ft_execute.o ft_sub.o
FLAGS = -Wall -Wextra -Werror -g3
OPTIONS = -c -I libft/includes/ -I includes/

all: $(NAME)

$(NAME):
	@make -C libft/
	@gcc $(FLAGS) $(OPTIONS) $(SRC)
	@gcc -o $(NAME) $(OBJECT) -L libft/ -lft -ltermcap
	@chmod 777 $(NAME)
	@echo "\x1B[32mCompiled project.\x1B[0m"
	@whoami > author

clean:
	@make -C libft/ clean
	@/bin/rm -f $(OBJECT)
	@echo "\x1B[32mCleaned up object files.\x1B[0m"

fclean: clean
		@make -C libft/ fclean
		@/bin/rm -f $(NAME)
		@echo "\x1B[32mCleaned up compiled files.\x1B[0m"

re: fclean	all
