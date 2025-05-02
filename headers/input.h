/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:49:06 by schiper           #+#    #+#             */
/*   Updated: 2025/05/02 14:52:40 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(INPUT_H)
# define INPUT_H
// Just to make Intelisense GO AWAY
# define _POSIX_C_SOURCE 200809L

# include "models/token_struct.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

/* Forward declaration of t_env_var to avoid circular inclusion */
typedef struct s_env_var	t_env_var;

/**
 * Function to refresh prompt after any Output. Please use it once you're
 * done printinh to STDOUT
 */
void						refresh_prompt(void);

/**
 * MAIN read pipeline. Use to keep reading from user
 * @param env : ENV variable passed from main
 * @return : Exit code of the last launched cmd
 */
int							read_loop(char **env);

/**
 * Displays token information for debugging purposes
 * @param tokens: Linked list of tokens to display
 * @return: Always returns 0
 */
int							display_tokens(t_token *tokens);
void						parse_segment(t_parse_params *params,
								t_parse_state *segment_state);

#endif // INPUT_H
