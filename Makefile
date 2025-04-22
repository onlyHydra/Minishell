# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schiper <schiper@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 14:40:00 by iatilla-          #+#    #+#              #
#    Updated: 2025/04/21 14:41:58 by schiper          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Source files
SRCS = sources/token_quote_handler.c sources/token_white_space.c sources/token_executable.c sources/initialize_token.c  sources/minishell.c  sources/token_path_cmd.c   sources/string_tokenize.c  sources/token_parser.c  sources/tokenizer.c    sources/parser_utils.c  sources/token_ops.c  sources/token_utils.c
OBJS = $(SRCS:.c=.o)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

# Includes
INCLUDES = -I./includes/Libft -I./includes/Libft/get_next_line

# Libft
LIBFT_DIR = includes/Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Rules
all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

// norminette -R CheckDefine headers