# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schiper <schiper@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 14:40:00 by iatilla-          #+#    #+#              #
#    Updated: 2025/05/05 15:15:26 by schiper          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
# Source files
SRCS = $(shell find sources -type f -name "*.c")
OBJS = $(SRCS:.c=.o)
# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
# Include path for readline
INCLUDES = -I./includes/Libft -I./includes/Libft/get_next_line -I/usr/local/opt/readline/include \
		   -Iheaders/interfaces -Iheader/models -Iheaders
# Linker flags
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline
# Formatter command
FORMAT = find sources -type f -name "*.c" -exec c_formatter_42 {} \;
# Libft
LIBFT_DIR = includes/Libft
LIBFT = $(LIBFT_DIR)/libft.a
# Rules
all: $(NAME)
	

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)
fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
re: fclean all
# 🆕 Format rule
format:
	$(FORMAT)

# valgrind : 
# 	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --trace-children=yes --log-file=vg-logs/valgrind-%p.log --suppressions=readline.supp ./minishell

valgrind:
	@mkdir -p vg-logs
	@rm -rf vg-logs/*
	VALGRIND_OPTS="--suppressions=$(PWD)/readline.supp" valgrind \
	--tool=memcheck \
	--leak-check=full \
	--show-leak-kinds=all \
	--trace-children=yes \
	--child-silent-after-fork=no \
	--log-file=vg-logs/valgrind-%p.log \
	./$(NAME)


.PHONY: all clean fclean re format valgrind

# printf "one\ntwo\nthree\n" | ( grep '^two$' && echo filtered )
