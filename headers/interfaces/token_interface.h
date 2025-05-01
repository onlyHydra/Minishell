/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:17:26 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 01:21:02 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_INTERFACE_H
# define TOKEN_INTERFACE_H

# include "minishell.h"
# include "models/token_struct.h"

/* --- Main Tokenization Functions --- */
t_token			*wrapper_process_string(char *input, char **envp);
t_token			*process_input(char *input, char **envp);



/* --- Token Creation and Management --- */
t_token			*add_token(t_token **head, char *value, t_token_type type);

/* --- Token Type Logic --- */
t_token_type	decide_token_type(char *token, char **envp);
t_token_type	get_token_type(char c);
t_token_type	onechar_operator(char *token);
t_token_type	twochar_operator(char *token);

int				is_operator(char *input, int i);

int				has_env_vars(char *str,char **envp);

/* --- Command Processing --- */
int				is_builtin_command(char *token);
int				is_string_command(char *string, char **envp);
void			post_process_command_tokens(t_token *tokens, char **envp);

/* --- Memory Management --- */
void			free_single_token(t_token *token);
void			free_token_struct(t_token *tokens);




#endif
