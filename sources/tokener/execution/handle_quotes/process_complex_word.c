/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_complex_word.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:12:58 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/21 18:50:43 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Process an environment variable as part of a complex word
 * Uses existing environment functions directly
 */
int	process_env_in_complex_word(t_parse_state *state,
		char **word_buffer)
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
 * Extract regular text segment between special characters
 */
static char	*extract_regular_text(char *input, int *current_pos)
{
	int		text_start;
	char	quote_char;
	char	*regular_text;

	text_start = *current_pos;
	while (input[*current_pos] && !ft_is_whitespace(input[*current_pos])
		&& !is_operator(input, *current_pos) && !is_quote(input[*current_pos],
			&quote_char) && input[*current_pos] != '$')
		(*current_pos)++;
	regular_text = extract_string(input, text_start, *current_pos);
	return (regular_text);
}

/**
 * Append regular text to word buffer
 */
static int	append_regular_text(char **word_buffer, char *regular_text,
		t_parse_state *state)
{
	char	*new_buffer;

	if (*word_buffer)
	{
		new_buffer = ft_strjoin(*word_buffer, regular_text);
		free(*word_buffer);
		free(regular_text);
		if (!new_buffer)
		{
			state->error = 1;
			return (0);
		}
		*word_buffer = new_buffer;
	}
	else
		*word_buffer = regular_text;
	return (1);
}

/**
 * Process regular text within a complex word
 */
static int	process_regular_text_in_word(char *input, int *current_pos,
		char **word_buffer, t_parse_state *state)
{
	char	*regular_text;

	regular_text = extract_regular_text(input, current_pos);
	if (!regular_text)
	{
		free(*word_buffer);
		state->error = 1;
		return (0);
	}
	if (!append_regular_text(word_buffer, regular_text, state))
	{
		return (0);
	}
	return (1);
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
		*current_pos = handle_embedded_quote(input, state, quote_char,
				word_buffer);
		if (*current_pos == -1)
		{
			free(*word_buffer);
			return (0);
		}
	}
	return (1);
}

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
 * Process the content of a complex word after initialization
 */
int	process_word_content(char *input, t_parse_state *state, char **word_buffer,
		int *current_pos)
{
	char	quote_char;

	while (input[*current_pos] && !ft_is_whitespace(input[*current_pos])
		&& !is_operator(input, *current_pos))
	{
		if (is_quote(input[*current_pos], &quote_char))
		{
			if (!handle_quoted_segment(input, state, current_pos, word_buffer))
				return (0);
		}
		else if (input[*current_pos] == '$')
		{
			state->i = *current_pos;
			return (process_env_in_complex_word(state, word_buffer));
		}
		else if (!process_regular_text_in_word(input, current_pos, word_buffer,
				state))
			return (0);
	}
	return (1);
}
