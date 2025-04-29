/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:17:26 by schiper           #+#    #+#             */
/*   Updated: 2025/04/29 23:27:56 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENER_INTERFACE_H
# define TOKENER_INTERFACE_H

# include "models/token_struct.h"

/* --- Main Tokenization Functions --- */
t_token			*wrapper_process_string(char *input, char **envp);
t_token			*process_input(char *input, char **envp);

/* --- Parse State Init --- */
void			init_parse_state(t_parse_state *state, t_token **tokens);
void			init_parse_params(t_parse_params *params, char *input,
					t_token **tokens, char **envp);


/* --- Segment Processing --- */
int				process_char_before_op(t_parse_params *params, int i);
void			parse_segment_wrapper(t_parse_params *params);

/* --- Token Navigation --- */
t_parsed_data	*peek_token(t_parsed_data **tokens);
void			advance_token(t_parsed_data **tokens);
int				is_operator_token(t_parsed_data *token);

/* --- Token Creation and Management --- */
t_token			*add_token(t_token **head, char *value, t_token_type type);

/* --- Token Type Logic --- */
t_token_type	decide_token_type(char *token, char **envp);
t_token_type	get_token_type(char c);
t_token_type	onechar_operator(char *token);
t_token_type	twochar_operator(char *token);

int				is_operator(char *input, int i);

int				has_env_vars(char *str);

/* --- Command Processing --- */
int				is_builtin_command(char *token);
int				is_string_command(char *string, char **envp);
void			post_process_command_tokens(t_token *tokens, char **envp);

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

#endif
