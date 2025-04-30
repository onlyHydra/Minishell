# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schiper <schiper@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 14:40:00 by iatilla-          #+#    #+#              #
#    Updated: 2025/04/29 14:12:16 by schiper          ###   ########.fr        #
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
.PHONY: all clean fclean re format
