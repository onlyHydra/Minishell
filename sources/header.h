/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:27:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/16 18:08:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

/* Standard Libraries */
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

/* Project-specific Includes */
# include "../includes/Libft/get_next_line/get_next_line.h"
# include "../includes/Libft/libft.h"

/* Enums and Structures */
typedef enum e_token_type
{
	CMD,
	REDIRECT_APPEND,
	HERE_DOC,
	HEREDOC,
	ENV_VAR,
	EXIT_STATUS,
	AND,
	OR,
	LPAREN,
	RPAREN,
	ARG,
	FLAG = '-',
	PIPE = '|',
	REDIRECT_IN = '<',
	REDIRECT_OUT = '>',
	SEMICOLON = ';',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
}					t_token_type;

typedef struct s_token
{
	char			*value;
	char			**split_values;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_parsed_data
{
	t_token_type	*token;
	char			*data;
}					t_parsed_data;

// helper strcut for bundle parsing state [FOR Tokenizer]
typedef struct s_parse_state
{
	int i;            // Current position
	int start;        // Start position of current token
	int in_word;      // Flag for whether we're in a word
	int error;        // Error flag
	t_token **tokens; // Pointer to token list
}					t_parse_state;

// initialize_token
/* Remove the 'static' keyword from function declarations */
void				init_parse_state(t_parse_state *state, t_token **tokens);

// Tokenizer functions
t_token_type		get_token_type(char c);
char				*extract_token(char *input, int start, int end);
t_token				*add_token(t_token **head, char *value, t_token_type type);
t_parsed_data		*tokens_to_parsed_data(t_token *tokens);
t_parsed_data		*tokenize_data(char **argv);

// STRING TOKENIZER
t_token				*tokenize_string(char *input);
void apply_command_flags(t_token *tokens, int *cmd_flags);
int is_command_in_path(char *cmd);
int is_operator_string(char *str);

// TOKEN operatations
int					handle_operators(char *input, t_parse_state *state);

// UTILS TOKEN
t_token_type get_token_type(char c);
char *extract_token(char *input, int start, int end);
t_token *add_token(t_token **head, char *value, t_token_type type);
int calculate_total_length(char **argv);
char *concatenate_arguments(char **argv, int total_len);
t_parsed_data *allocate_parsed_data(t_token *tokens, int count);
t_parsed_data *tokens_to_parsed_data(t_token *tokens);

#endif
