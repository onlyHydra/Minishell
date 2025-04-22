/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_tokenparams->c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@studentparams->42params->fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:29:28 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/16 16:30:04 by marvin           ###   ########params->fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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

/**
 * Initialize parsing state
 * @param input: string of cmdline input
 * @param tokens: Pointer to parameter struct
 */
t_parse_params	*init_params(char *input, t_token *tokens, char **envp)
{
	t_parse_params	*params;

	params = NULL;
	params->input = input;
	params->tokens = &tokens;
	params->start = 0;
	params->end = 0;
	params->is_first = 1;
	params->envp = envp;
	params->in_quote = 0;
	params->quote_char = 0;
	params->segment_start = 0;
	return (params);
}
