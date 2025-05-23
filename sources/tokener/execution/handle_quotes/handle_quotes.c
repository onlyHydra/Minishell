/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:24:43 by schiper           #+#    #+#             */
/*   Updated: 2025/05/21 18:50:55 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Extract the content from a quoted string and handle environment variables
 * Uses existing environment functions directly
 */
char	*extract_quoted_content(char *input, int start, int end,
		char quote_char, t_parse_state *state, t_token_type *type)
{
	char	*content;
	char	*expanded;

	*type = STR_LITERAL;
	content = extract_string(input, start, end);
	if (!content)
		return (NULL);
	if (quote_char == '"' && is_environment_variable(content))
	{
		expanded = extract_env_value(content, state->envp);
		free(content);
		if (!expanded)
			return (NULL);
		*type = ENV_VAR;
		content = expanded;
	}
	if (state->expect_filename && *type != ENV_VAR)
	{
		*type = FILENAME;
		state->expect_filename = 0;
	}
	else if (state->expect_filename)
		state->expect_filename = 0;
	return (content);
}

/**
 * Process a standalone quoted token (one surrounded by whitespace)
 */
static int	process_standalone_quoted_token(char *input, t_parse_state *state,
		int end, char quote_char)
{
	char			*token_content;
	t_token_type	token_type;

	if (state->start < state->i && state->in_word)
		process_token(input, state, state->envp);
	state->quote_char = quote_char;
	token_content = extract_quoted_content(input, state->i + 1, end, quote_char,
			state, &token_type);
	if (!token_content)
		return (0);
	add_token(state->tokens, token_content, token_type, NULL);
	state->i = end + 1;
	state->start = state->i;
	state->in_word = 0;
	return (1);
}

/**
 * Process a complex word that may contain embedded quotes
 */
static int	process_complex_word(char *input, t_parse_state *state)
{
	char	*word_buffer;
	int		current_pos;
	char	quote_char;

	word_buffer = init_word_buffer(input, state);
	if (state->error)
		return (0);
	current_pos = state->i;
	if (is_quote(input[current_pos], &quote_char))
	{
		current_pos = handle_embedded_quote(input, state, quote_char,
				&word_buffer);
		if (current_pos == -1)
		{
			free(word_buffer);
			return (0);
		}
	}
	if (!process_word_content(input, state, &word_buffer, &current_pos))
		return (0);
	finalize_complex_word(&word_buffer, state, input, current_pos);
	return (1);
}

/**
 * Handle quoted text in the input string
 */
int	handle_quoted_text(char *input, t_parse_state *state)
{
	char	quote_char;
	int		end;

	if (!input || !state || !input[state->i])
		return (0);
	if (!is_quote(input[state->i], &quote_char))
		return (0);
	if (is_part_of_word(input, state->i))
		return (process_complex_word(input, state));
	else
	{
		end = find_closing_quote(input, state->i + 1, quote_char);
		if (end == -1)
		{
			state->error = 1;
			return (1);
		}
		return (process_standalone_quoted_token(input, state, end, quote_char));
	}
}
