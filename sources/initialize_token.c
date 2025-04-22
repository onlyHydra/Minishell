/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:29:28 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/21 13:29:26 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Initialize parsing state
 * @param state: State struct to initialize
 * @param tokens: Pointer to token list
 */
void	init_parse_state(t_parse_state *state, t_token **tokens)
{
	state->i = 0;
	state->start = 0;
	state->in_word = 0;
	state->error = 0;
	state->tokens = tokens;
}
