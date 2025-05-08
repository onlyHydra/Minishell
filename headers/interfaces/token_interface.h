/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:17:26 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 14:02:51 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_INTERFACE_H
# define TOKEN_INTERFACE_H

# include "minishell.h"
# include "models/token_struct.h"

/* --- Main Tokenization Functions --- */
t_token			*wrapper_process_string(char *input, char **envp);

/* --- Token Creation and Management --- */
void			add_token(t_token **head, char *value, t_token_type type,
					char *filepath);

/* --- Token Type Logic --- */
t_token_type	decide_token_type(char *token, char **envp,
					t_parse_state *state);
t_token_type	get_token_type(char c);
t_token_type	onechar_operator(char *token);
t_token_type	twochar_operator(char *token);

/* --- Operator Detection --- */
int				is_operator(char *input, int i);

/* --- Environment Variable Logic --- */
int				has_env_vars(char *str);

/* --- Command Processing --- */
int				is_builtin_command(char *token);
int				is_string_command(char *string, char **envp, char **filepath);

/* --- Memory Management --- */
void			free_single_token(t_token *token);
void			free_token_struct(t_token **tokens);
void			free_parsed_data(t_parsed_data *parsed_data);

/* --- Token Navigation Helpers --- */
t_token			*get_last_token(t_token *head);

/* --- Token Display for Debugging --- */
int				display_tokens(t_token *tokens);

/* --- Moved from token_struct.h for better organization --- */

/**
 * @brief Peeks at the next token without advancing the token pointer.
 *
 * This function allows the parser to inspect the next token in the list
 * without consuming it.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 * @return A pointer to the next token, or NULL if no tokens are available.
 */
t_parsed_data	*peek_token(t_parsed_data **tokens);

/**
 * @brief Peeks at the next token label without advancing the token pointer.
 *
 * This function allows the parser to inspect the next token label in the list
 * without consuming it.
 *
 * @param data A double pointer to the list of parsed tokens.
 * @return A pointer to the token label, or NULL if no labels are available.
 */
t_token_type	*peek_token_label(t_parsed_data **data);

/**
 * @brief Advances the token pointer to the next token.
 *
 * This function moves the token pointer to the next token in the list,
 * effectively consuming the current token.
 *
 * @param tokens A double pointer to the list of parsed tokens.
 */
void			advance_token(t_parsed_data **tokens);
int				is_operator_token(t_token_type type);
int				is_label_argv(t_token_type type);

#endif
