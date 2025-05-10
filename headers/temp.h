/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:52:49 by schiper           #+#    #+#             */
/*   Updated: 2025/05/10 16:04:31 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(TEMP_H)
# define TEMP_H
# include "models/input_data_struct.h"
# include "models/token_struct.h"
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

int		handle_whitespace(const char *input, t_parse_state *state, char **envp);
int		handle_parsing_ops(const char *input, t_parse_state *state,
			char **envp);
int		process_operator_token(t_parse_state *state, char *op,
			t_token_type type, int len);
void	process_token(const char *input, t_parse_state *state, char **envp);
void	add_token_to_list(t_token **tokens, t_token *new_token);
int		handle_regular_text(const char *input, t_parse_state *state,
			char **envp);
int		handle_quoted_text(const char *input, t_parse_state *state);
#endif // TEMP_H
