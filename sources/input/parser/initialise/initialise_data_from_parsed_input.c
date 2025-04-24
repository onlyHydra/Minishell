/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data_from_parsed_input.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:20:33 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/24 18:59:47 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_struct.h"

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
 * Initialize the parsing parameters
 * @param params: pointer to params struct to initialize
 * @param input: the input string to tokenize
 * @param tokens: pointer to tokens list
 * @param envp: environment variables array
 */
void	init_parse_params(t_parse_params *params, char *input, t_token **tokens,
		char **envp)
{
	params->input = input;
	params->tokens = tokens;
	params->segment_start = 0;
	params->is_first_segment = 1;
	params->envp = envp;
}
