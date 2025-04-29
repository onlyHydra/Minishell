/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:17:26 by schiper           #+#    #+#             */
/*   Updated: 2025/04/29 13:37:32 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(TOKEN_INTERFACE_H)
# define TOKEN_INTERFACE_H

# include "token_struct.h"

#endif // TOKEN_INTERFACE_H
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener_interface.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 00:00:00 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/29 00:00:00 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENER_INTERFACE_H
# define TOKENER_INTERFACE_H

# include "token_struct.h"

/* --- Main Tokenization Functions --- */
t_token			*wrapper_process_string(char *input, char **envp);
t_token			*process_input(char *input, char **envp);
t_token			*process_tokenization_loop(char *input, t_parse_params *params);

/* --- Parse State Init --- */
void			init_parse_state(t_parse_state *state, t_token **tokens);
void			init_parse_params(t_parse_params *params, char *input,
					t_token **tokens, char **envp);

/* --- Token Processing --- */
void			process_token(char *input, t_parse_state *state, int end,
					char **envp);
int				handle_whitespace(char *input, t_parse_state *state,
					char **envp);
int				handle_parenthesis_char(char *input, t_parse_state *state,
					char **envp);
int				handle_quotes(char *input, t_parse_state *state);
int				handle_regular_text(char *input, t_parse_state *state,
					char **envp);
int				handle_parsing_ops(char *input, t_parse_state *state,
					char **envp);

/* --- Segment Processing --- */
int				handle_operator_segment(t_parse_params *params, int i);
void			process_segment(t_parse_params *params);
void			handle_segment(t_parse_params *params, int i);

/* --- Token Navigation --- */
t_parsed_data	*peek_token(t_parsed_data **tokens);
void			advance_token(t_parsed_data **tokens);
int				is_operator_token(t_parsed_data *token);

/* --- Token Creation and Management --- */
t_token			*add_token(t_token **head, char *value, t_token_type type);
t_parsed_data	*allocate_parsed_data(t_token *tokens, int count);
t_parsed_data	*tokens_to_parsed_data(t_token *tokens);

/* --- Token Type Logic --- */
t_token_type	decide_token_type(char *token, char **envp);
t_token_type	get_token_type(char c);
t_token_type	onechar_operator(char *token);
t_token_type	twochar_operator(char *token);

/* --- String Handling --- */
char			*extract_string(char *input, int start, int end);
int				is_quote_closed(char *str, int start, char quote_char);
int				handle_quotes_tokenize(char *input, int i, int *in_quote,
					char *quote_char);
int				handle_braces(char *input, t_parse_state *state);
int				is_operator(char *input, int i);
int				handle_quoted_string(char *str, int i, t_token_type quote_type,
					int *error);
int				has_env_vars(char *str);
int				calculate_total_length(char **argv);
char			*concatenate_arguments(char **argv, int total_len);

/* --- Command Processing --- */
void			post_process_command_tokens(t_token *tokens, char **envp);
int				is_builtin_command(char *token);
int				is_command_in_path(char *cmd);
int				executable(char *token, char **envp);
int				is_string_command(char *string, char **envp);
void			apply_command_flags(t_token *tokens, int *cmd_flags);

/* --- Memory Management --- */
void			free_single_token(t_token *token);
void			free_token_struct(t_token *tokens);
void			free_state_struct(t_parse_state *state);
void			free_params_struct(t_parse_params *params);
void			free_parsed_data(t_parsed_data *parsed_data);
void			free_parsed_data_up_to(t_parsed_data *parsed_data,
					int up_to_index);
void			free_parsed_data_on_error(t_parsed_data *parsed_data, int index,
					int free_token);
void			free_array(char **dirs);

#endif
