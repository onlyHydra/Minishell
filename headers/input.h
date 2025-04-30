/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:49:06 by schiper           #+#    #+#             */
/*   Updated: 2025/04/29 14:17:22 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(INPUT_H)
# define INPUT_H
//Just to make Intelisense GO AWAY 
# define _POSIX_C_SOURCE 200809L

# include "models/token_struct.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>

/**
 * Function to refresh prompt after any Output. Please use it once you're
 * done printinh to STDOUT
 */
void	refresh_prompt(void);
/**
 * MAIN read pipeline. Use to keep reading from user
 * @param env : ENV variable passed from main
 * @return : Exit code of the last launched cmd
 *
 */

int		read_loop(char **env);
int		display_tokens(t_token *tokens);
#endif // INPUT_H
