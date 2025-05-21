/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_complex_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:12:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/21 21:37:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Determine token type and add the final word to tokens
 */
void	finalize_complex_word(char **word_buffer, t_parse_state *state,
		char *input, int current_pos)
{
	t_token_type	type;

	if (*word_buffer)
	{
		type = STR_LITERAL;
		if (state->expect_filename)
		{
			type = FILENAME;
			state->expect_filename = 0;
		}
		else if (input[state->start] == '-')
		{
			type = FLAG;
		}
		add_token(state->tokens, *word_buffer, type, NULL);
		state->in_word = 0;
	}
	state->i = current_pos;
	state->start = current_pos;
}

/**
 * Process an environment variable as part of a complex word
 * Uses existing environment functions directly
 */
int	process_env_in_complex_word(t_parse_state *state, char **word_buffer)
{
	if (*word_buffer)
	{
		add_token(state->tokens, *word_buffer, STR_LITERAL, NULL);
		*word_buffer = NULL;
	}
	state->start = state->i;
	state->in_word = 0;
	return (prepare_for_env_var(NULL, state, state->envp));
}

/**
 * Handle quoted segment within a complex word
 */
int	handle_quoted_segment(char *input, t_parse_state *state, int *current_pos,
		char **word_buffer)
{
	char	quote_char;

	if (is_quote(input[*current_pos], &quote_char))
	{
		state->i = *current_pos;
		state->quote_char = quote_char;
		*current_pos = handle_embedded_quote(input, state, word_buffer);
		if (*current_pos == -1)
		{
			free(*word_buffer);
			return (0);
		}
	}
	return (1);
}
