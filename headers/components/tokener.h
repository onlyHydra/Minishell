/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:27:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/11 13:00:00 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(TOKENER_H)
# define TOKENER_H

/* Standard Libraries - Consider removing duplicates already in minishell.h */
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
# include "libft.h"
# include "models/input_data_struct.h"
# include "token_interface.h"

/* ============================= */
/*         DECLARATIONS         */
/* ============================= */

/* --- Main Functions --- */
t_parsed_data	*tokenize_input(char *input, char **envp);
t_token			*process_tokenization_loop(char *input, t_parse_params *params);
t_token			*process_input(char *input, char **envp, int exit_status);
t_token			*wrapper_process_string(char *input, char **envp);


void	process_token(char *input, t_parse_state *state, char **envp);
/* --- Parse State Init --- */
void			init_parse_state(t_parse_state *state, t_token **tokens,
					char **envp);
void			init_parse_params(t_parse_params *params, char *input,
					t_token **tokens, char **envp);

/* --- Utility Functions --- */
int				ft_is_whitespace(char c);
char			*extract_string(char *input, int start, int end);

/* --- New Token Interface Utilities --- */
int				is_whitespace_token(const char *token);
int				is_operator_char(char c);
t_token_type	determine_token_type(char *token, char **envp, t_parse_state *state);
char			*process_token_value(char *token);

/*          Environment Variable Handling */
char			*extract_env_value(char *str, char **envp);

/* --- Post-Processing Functions --- */
void			post_process_filename_tokens(t_token *tokens);
void			post_process_command_tokens(t_token *tokens, char **envp);

/* Function prototypes for exit status handling */
int				is_exit_status_var(const char *input, int index);
int				handle_exit_status(char *input, t_parse_state *state,
					int exit_status);

#endif // TOKENER_H
