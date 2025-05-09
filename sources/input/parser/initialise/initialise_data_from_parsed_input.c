/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data_from_parsed_input.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:20:33 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 00:29:02 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "models/input_data_struct.h"
#include "models/token_struct.h"
#include "libft.h"

/**
 * Initialize parse state with default values
 * @param state: The parse state to initialize
 * @param tokens: Pointer to the tokens list
 */
void	init_parse_state(t_parse_state *state, t_token **tokens, char **envp)
{
	state->i = 0;
	state->start = 0;
	state->in_word = 0;
	state->is_first_token = 1;
	state->in_quote = 0;
	state->quote_char = 0;
	state->error = 0;
	state->expect_filename = 0;
	state->tokens = tokens;
	state->envp = envp;
	state->exit_status = 0;
}

/**
 * Initialize parse parameters struct with provided values
 * @param params: The parse parameters to initialize
 * @param input: Input string to parse
 * @param tokens: Pointer to the tokens list
 * @param envp: Environment variables
 */
void	init_parse_params(t_parse_params *params, char *input, t_token **tokens,
		char **envp)
{
	params->input = input;
	params->segment_start = 0;
	params->segment_end = ft_strlen(input);
	params->is_first_segment = 1;
	params->tokens = tokens;
	params->envp = envp;
	params->exit_status = 0;
}
