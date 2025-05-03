/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:27:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 19:08:34 by schiper          ###   ########.fr       */
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
# include "get_next_line.h"
# include "libft.h"
# include "models/input_data_struct.h"
# include "token_interface.h"

/* ============================= */
/*         DECLARATIONS         */
/* ============================= */

/* --- Main Functions --- */
t_parsed_data	*tokenize_input(char *input, char **envp);
t_token			*process_tokenization_loop(char *input, t_parse_params *params);
t_token			*process_input(char *input, char **envp);
t_token			*wrapper_process_string(char *input, char **envp);

/* --- Parse State Init --- */
void			init_parse_state(t_parse_state *state, t_token **tokens,
					char **envp);
void			init_parse_params(t_parse_params *params, char *input,
					t_token **tokens, char **envp);

/* --- Utility Functions --- */
int				ft_is_whitespace(char c);
char			*extract_string(char *input, int start, int end);

/*          Handle Quotes           */
int				handle_quoted_text(char *input, t_parse_state *state);
int				update_quote_state(char *input, int i, int *in_quote,
					char *quote_char);
int				is_quote(char c, char *quote_char);

/*          Handle WhiteSpace           */
int				handle_whitespace(char *input, t_parse_state *state,
					char **envp);

/*          Handle Parenthesis          */
int				handle_parenthesis_char(char *input, t_parse_state *state,
					char **envp);

/*          Handle Regular              */
int				handle_regular_text(char *input, t_parse_state *state,
					char **envp);

/*          Handle Brakets              */
int				handle_brakets(char *input, t_parse_state *state);

/*         Token Allocs                 */
t_parsed_data	*tokens_to_parsed_data(t_token *tokens);

/* --- Token Processing --- */
void			process_token(char *input, t_parse_state *state, int end,
					char **envp);

/*          Parser Operations           */
int				handle_parsing_ops(char *input, t_parse_state *state,
					char **envp);

/*          Environment Variable Handling */
char			*extract_env_value(char *str, char **envp);
int				handle_filename(char *input, t_parse_state *state);

/* --- Post-Processing Functions --- */
void			post_process_filename_tokens(t_token *tokens);
void			post_process_command_tokens(t_token *tokens, char **envp);
void			print_export_error(char *arg);


#endif // TOKENER_H
