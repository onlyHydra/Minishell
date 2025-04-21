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

/* ============================= */
/*          LIBRARIES           */
/* ============================= */

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

/* ============================= */
/*        ENUMS & STRUCTS       */
/* ============================= */

typedef enum e_token_type
{
	CMD,
	STR_LITERAL,
	REDIRECT_APPEND,
	APPEND_OUT,
	HEREDOC,
	ENV_VAR,
	EXIT_STATUS,
	AND,
	OR,
	LPAREN,
	RPAREN,
	ARG,
	OPERATOR,
	FILE_NAME,
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

/* Helper struct for tokenizer parse state */
typedef struct s_parse_state
{
	int i;       // Current position
	int start;   // Start position of current token
	int in_word; // Flag for whether we're in a word
	int error;   // Error flag
	int				is_first_token;
	t_token **tokens; // Pointer to token list
}					t_parse_state;

/* ============================= */
/*         DECLARATIONS         */
/* ============================= */

/* --- Tokenizer Core --- */
t_token				*tokenize_string(char *input, char **envp);
t_parsed_data		*tokenize_data(char **argv, char **envp);

/* --- Parse State Init --- */
void				init_parse_state(t_parse_state *state, t_token **tokens);

/* --- Token Processing --- */
void				process_token(char *input, t_parse_state *state, int end,
						char **envp);
void				process_segment(char *input, t_token **tokens, int start,
						int end, int is_first, char **envp);
int					handle_without_quotes(char *input, t_token **tokens, int i,
						char **envp);
char				*handle_escapes(char *input);
int					handle_whitespace(char *input, t_parse_state *state,
						char **envp);
int					handle_backslash(char *input, t_parse_state *state);

/* --- Token operation handlers --- */
int					handle_without_quotes(char *input, t_token **tokens, int i,
						char **envp);
int					is_quote_closed(char *str, int start, char quote_char);
int					handle_quoted_string(char *str, int i,
						t_token_type quote_type, int *error);
int					handle_quotes(char *input, t_parse_state *state,
						char **envp);

/* --- Token Operations --- */
t_token_type		get_token_type(char c);
char				*extract_token(char *input, int start, int end);
t_token				*add_token(t_token **head, char *value, t_token_type type);
int					handle_operators(char *input, t_parse_state *state);

/* --- Utility Functions --- */
int					calculate_total_length(char **argv);
char				*concatenate_arguments(char **argv, int total_len);
t_parsed_data		*allocate_parsed_data(t_token *tokens, int count);
t_parsed_data		*tokens_to_parsed_data(t_token *tokens);

/* --- Quotation Handling --- */
int					is_quote_closed(char *str, int start, char quote_char);
int					handle_quoted_string(char *str, int i,
						t_token_type quote_type, int *error);

/* --- Token Type Logic --- */
t_token_type		decide_token_type(char *token, char **envp);
int					is_operator_char(char c);

/* --- Command Logic --- */
void				apply_command_flags(t_token *tokens, int *cmd_flags);
int					is_command_in_path(char *cmd);
int					executable(char *token, char **envp);

/* --- Escape Handling --- */
char				*handle_escapes(char *input);

#endif
