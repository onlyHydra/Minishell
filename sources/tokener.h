/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:27:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/24 00:00:48 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENER_H
# define TOKENER_H

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
	STR_LITERAL,
	REDIRECT_APPEND,
	APPEND_OUT,
	HEREDOC,
	ENV_VAR,
	EXIT_STATUS,
	AND,
	OR,
	ARG,
	OPERATOR,
	FILE_NAME,
	LPAREN = '(',
	RPAREN = ')',
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

/**
 * Structure to combine parameters for process_segment
 */
typedef struct s_parse_params
{
	char			*input;
	t_token			**tokens;
	int				start;
	int				end;
	int				is_first;
	char			**envp;
	int				in_quote;
	char			quote_char;
	int				segment_start;
	int				segment_end;
	int				is_first_segment;
	int				exit_status; 
}					t_parse_params;

typedef struct s_parsed_data
{
	t_token_type	*token;
	char			*data;
}					t_parsed_data;

/* Helper struct for tokenizer parse state */
typedef struct s_parse_state
{
	int				i;
	int				start;
	int				in_word;
	int				error;
	int				is_first_token;
	int				in_quote;
	char			quote_char;
	t_token			**tokens;
}					t_parse_state;

typedef struct s_enviro
{
	/* data */
} t_enviro;



/* ============================= */
/*         DECLARATIONS         */
/* ============================= */

/* --- Tokenizer Core --- */
t_token				*tokenize_string(char *input, char **envp);
t_parsed_data		*tokenize_data(char **argv, char **envp);

/* --- Environment Variable Handling --- */
char    *expand_env_vars(char *token, char **envp, int exit_status);
char    *process_env_vars(char *token, char **envp, int exit_status);
int     has_env_vars(char *str);

/* --- Token Segment --- */
int					handle_operator_segment(t_parse_params *params, int i);
void				process_segment(t_parse_params *params);
void				handle_segment(t_parse_params *params, int i);

/* --- String utils --- */
int					is_quote_closed(char *str, int start, char quote_char);
int					handle_quotes_tokenize(char *input, int i, int *in_quote,
						char *quote_char);
int					handle_escape(char *input, int i);
int					is_operator(char *input, int i);

/* --- Parse State Init --- */
void				init_parse_state(t_parse_state *state, t_token **tokens);
void				init_parse_params(t_parse_params *params, char *input,
						t_token **tokens, char **envp);

/* --- Token Processing --- */
void				process_token(char *input, t_parse_state *state, int end);
int					handle_without_quotes(char *input, t_token **tokens, int i);
char				*handle_escapes(char *input);
int					handle_whitespace(char *input, t_parse_state *state);
int					handle_backslash(char *input, t_parse_state *state);

/* --- Token operation handlers --- */
int					is_quote_closed(char *str, int start, char quote_char);
int					handle_quoted_string(char *str, int i,
						t_token_type quote_type, int *error);
int					handle_quotes(char *input, t_parse_state *state);

/* --- Token Type Logic --- */
t_token_type		decide_token_type(char *token);
t_token_type		token_one(char *token);
t_token_type		token_two(char *token);
t_token_type		get_token_type(char c);
int					is_operator_char(char c);
int					is_builtin_command(char *token);

/* --- Token Operations --- */
t_token				*add_token(t_token **head, char *value, t_token_type type);
char				*extract_token(char *input, int start, int end);
int					handle_operators(char *input, t_parse_state *state);

// UTILS TOKEN
t_token_type		get_token_type(char c);
char				*extract_token(char *input, int start, int end);
t_token				*add_token(t_token **head, char *value, t_token_type type);
int					calculate_total_length(char **argv);
char				*concatenate_arguments(char **argv, int total_len);
t_parsed_data		*allocate_parsed_data(t_token *tokens, int count);
t_parsed_data		*tokens_to_parsed_data(t_token *tokens);

/* --- Command Logic --- */
void				apply_command_flags(t_token *tokens, int *cmd_flags);
int					is_command_in_path(char *cmd);
int					executable(char *token, char **envp);

/* --- UTILS --- */
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strcat(char *dest, const char *src);
void				free_array(char **dirs);

#endif
