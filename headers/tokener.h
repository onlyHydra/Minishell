/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokener.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:27:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 13:30:14 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(TOKENER_H)
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
# include "get_next_line.h"
# include "libft.h"
# include "models/input_data_struct.h"
# include "token_interface.h"
/* ============================= */
/*         DECLARATIONS         */
/* ============================= */

/* --- Main Functions --- */
t_parsed_data	*tokenize_input(char **argv, char **envp);
t_token			*process_tokenization_loop(char *input, t_parse_params *params);

/* --- Parse State Init --- */
void			init_parse_state(t_parse_state *state, t_token **tokens);
void			init_parse_params(t_parse_params *params, char *input,
					t_token **tokens, char **envp);

/* --- Utility Functions --- */
int				ft_is_whitespace(char c);

/*          Handle Quotes           */
int				handle_quoted_text(char *input, t_parse_state *state);
int				handle_quotes_tokenize(char *input, int i, int *in_quote,
					char *quote_char);

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
t_parsed_data	*allocate_parsed_data(t_token *tokens, int count);
t_parsed_data	*tokens_to_parsed_data(t_token *tokens);

/* --- Token Processing --- */
void			process_token(char *input, t_parse_state *state, int end,
					char **envp);

t_token			*process_tokenization_loop(char *input, t_parse_params *params);

/*          Unknown Usage               */
int				handle_parsing_ops(char *input, t_parse_state *state,
					char **envp);

t_token			*process_tokenization_loop(char *input, t_parse_params *params);
char *extract_env_value(char *str,char **envp);
#endif // TOKENER_H
