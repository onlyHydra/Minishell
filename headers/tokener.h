/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/25 00:27:18 by iatilla-         ###   ########.fr       */
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
# include "token_struct.h"
/* Enums and Structures */

/* ============================= */
/*         DECLARATIONS         */
/* ============================= */

/* --- Main Functions and Wrappers --- */
t_token			*wrapper_process_string(char *input, char **envp);
t_parsed_data	*tokenize_input(char **argv, char **envp);

// Move the function away with First Occasion
int				has_env_vars(char *str);

// Move into Parsing Header with First Occasion
int				handle_operator_segment(t_parse_params *params, int i);
void			process_segment(t_parse_params *params);
void			handle_segment(t_parse_params *params, int i);

/* --- Parse State Init move to Parser header with First Occasion --- */
void			init_parse_state(t_parse_state *state, t_token **tokens);
void			init_parse_params(t_parse_params *params, char *input,
					t_token **tokens, char **envp);

/* --- Token Processing --- */
void			process_token(char *input, t_parse_state *state, int end);
int				handle_without_quotes(char *input, t_token **tokens, int i);
char			*handle_escapes(char *input);
int				handle_whitespace(char *input, t_parse_state *state);
int				handle_backslash(char *input, t_parse_state *state);

/* --- Token Type Logic --- */

int				is_builtin_command(char *token);

/* --- Token Operations --- */
char			*extract_string(char *input, int start, int end);
int				handle_parsing_ops(char *input, t_parse_state *state);

// UTILS TOKEN
char			*extract_string(char *input, int start, int end);
int				calculate_total_length(char **argv);
char			*concatenate_arguments(char **argv, int total_len);

/* --- Command Logic --- */
void			apply_command_flags(t_token *tokens, int *cmd_flags);
int				is_command_in_path(char *cmd);
int				executable(char *token, char **envp);

/* --- UTILS --- */
void			free_array(char **dirs);

/* --- String utils --- */
int				is_quote_closed(char *str, int start, char quote_char);
int				handle_quotes_tokenize(char *input, int i, int *in_quote,
					char *quote_char);
int				handle_escape(char *input, int i);
int				is_operator(char *input, int i);

int				process_operator_token(char *input, t_token **tokens, int j);
int				handle_quoted_string(char *str, int i, t_token_type quote_type,
					int *error);

#endif
