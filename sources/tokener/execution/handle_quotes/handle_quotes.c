/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:24:43 by schiper           #+#    #+#             */
/*   Updated: 2025/05/13 15:49:35 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "interfaces/envir_interface.h"

/**
 * Find the closing quote index starting from
 * the character after the opening quote
 */
static int	find_closing_quote(char *input, int start, char quote_char)
{
	int	j;

	j = start;
	while (input[j] && input[j] != quote_char)
		j++;
	if (input[j] == quote_char)
		return (j);
	return (-1);
}

/*
 * Extract the content from a quoted string, handling environment variables
 * if needed (for double quotes)
 */
static char	*extract_quoted_content(char *input, int start, int end,
		char quote_char, t_parse_state *state, t_token_type *type)
{
	char	*content;
	char	*expanded;

	*type = STR_LITERAL;
	content = extract_string(input, start, end);
	if (!content)
		return (NULL);
	// If double quoted and contains environment variables, expand them
	if (quote_char == '"' && is_environment_variable(content))
	{
		expanded = extract_env_value(content, state->envp);
		free(content);
		if (!expanded)
			return (NULL);
		*type = ENV_VAR;
		return (expanded);
	}
	// Handle filename expectations
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

	* Handle embedded quoted text within a word and append to the current word buffer
 *
 * @param input: The input string
 * @param state: Current parsing state
 * @param quote_char: The type of quote (' or ")
 * @param word_buffer: Buffer to store the combined word
 * @return: Index of the position after the closing quote, or -1 if error
 */
static int	handle_embedded_quote(char *input, t_parse_state *state,
		char quote_char, char **word_buffer)
{
	int				end;
	char			*quoted_content;
	t_token_type	token_type;
	char			*new_buffer;

	// Find the closing quote
	end = find_closing_quote(input, state->i + 1, quote_char);
	if (end == -1)
	{
		state->error = 1; // Unclosed quote
		return (-1);
	}
	// Extract the quoted content
	quoted_content = extract_quoted_content(input, state->i + 1, end,
			quote_char, state, &token_type);
	if (!quoted_content)
	{
		state->error = 1;
		return (-1);
	}
	// Append the quoted content to the word buffer
	if (*word_buffer)
	{
		new_buffer = ft_strjoin(*word_buffer, quoted_content);
		free(*word_buffer);
		free(quoted_content);
		if (!new_buffer)
		{
			state->error = 1;
			return (-1);
		}
		*word_buffer = new_buffer;
	}
	else
		*word_buffer = quoted_content;
	// Update the current position to after the closing quote
	return (end + 1);
}

/**
 * Process a standalone quoted token (one surrounded by whitespace)
 */
static int	process_standalone_quoted_token(char *input, t_parse_state *state,
		int end, char quote_char)
{
	char			*token_content;
	t_token_type	token_type;

	// If we're already in a word, process it first
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
 * Check if this is part of a continuous word (no whitespace before or after)
 */
static int	is_part_of_word(char *input, int i)
{
	int	is_start;
	int	is_end;

	is_start = (i == 0 || ft_is_whitespace(input[i - 1]) || is_operator(input, i
				- 1));
	is_end = (!input[i + 1] || ft_is_whitespace(input[i + 1])
			|| is_operator(input, i + 1));
	return (!(is_start && is_end));
}

/**
 * Process a complex word that may contain embedded quotes
 */
static int	process_complex_word(char *input, t_parse_state *state)
{
	char			*word_buffer;
	int				current_pos;
	char			quote_char;
	int				text_start;
	char			*regular_text;
	char			*new_buffer;
	t_token_type	type;

	word_buffer = NULL;
	current_pos = state->i;
	// Process any regular text before the first quote if we're in a word
	if (state->in_word && state->start < state->i)
	{
		word_buffer = extract_string(input, state->start, state->i);
		if (!word_buffer)
		{
			state->error = 1;
			return (0);
		}
	}
	// Process the first quote that triggered this function
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
	// Continue processing the rest of the word,
	while (input[current_pos] && !ft_is_whitespace(input[current_pos])
		&& !is_operator(input, current_pos))
	{
		if (is_quote(input[current_pos], &quote_char))
		{
			// Set state position for the embedded quote handling
			state->i = current_pos;
			current_pos = handle_embedded_quote(input, state, quote_char,
					&word_buffer);
			if (current_pos == -1)
			{
				free(word_buffer);
				return (0);
			}
		}
		else if (input[current_pos] == '$')
		{
			// Handle environment variables (save word buffer and process separately)
			if (word_buffer)
			{
				add_token(state->tokens, word_buffer, STR_LITERAL, NULL);
				word_buffer = NULL;
			}
			// Process environment variable
			state->i = current_pos;
			state->start = current_pos;
			state->in_word = 0; // Reset word status to process env var
			// Now the regular env var handler will take over in the next loop
			return (1);
		}
		else
		{
			// Regular text, collect until next quote or whitespace
			text_start = current_pos;
			while (input[current_pos] && !ft_is_whitespace(input[current_pos])
				&& !is_operator(input, current_pos)
				&& !is_quote(input[current_pos], &quote_char)
				&& input[current_pos] != '$')
				current_pos++;
			// Extract this segment of regular text
			regular_text = extract_string(input, text_start, current_pos);
			if (!regular_text)
			{
				free(word_buffer);
				state->error = 1;
				return (0);
			}
			// Append to word buffer
			if (word_buffer)
			{
				new_buffer = ft_strjoin(word_buffer, regular_text);
				free(word_buffer);
				free(regular_text);
				if (!new_buffer)
				{
					state->error = 1;
					return (0);
				}
				word_buffer = new_buffer;
			}
			else
			{
				word_buffer = regular_text;
			}
		}
	}
	// Add the complete word to tokens
	if (word_buffer)
	{
		// Determine token type based on content
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
		add_token(state->tokens, word_buffer, type, NULL);
		state->in_word = 0;
	}
	state->i = current_pos;
	state->start = current_pos;
	return (1);
}

/**
 * Handle quoted text in the input string
 * Now handles quotes that are part of a larger word
 *
 * @param input: The input string being parsed
 * @param state: Current parsing state
 * @return: 1 if a quote was handled, 0 otherwise
 */
int	handle_quoted_text(char *input, t_parse_state *state)
{
	char	quote_char;
	int		end;

	if (!input || !state || !input[state->i])
		return (0);
	if (!is_quote(input[state->i], &quote_char))
		return (0);
	// Check if this quote is part of a complex word
	if (is_part_of_word(input, state->i))
	{
		return (process_complex_word(input, state));
	}
	else
	{
		// Handle standalone quoted token
		end = find_closing_quote(input, state->i + 1, quote_char);
		if (end == -1)
		{
			state->error = 1;
			return (1);
		}
		return (process_standalone_quoted_token(input, state, end, quote_char));
	}
}
