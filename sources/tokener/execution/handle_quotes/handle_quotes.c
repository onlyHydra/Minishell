/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:24:43 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 14:49:59 by iatilla-         ###   ########.fr       */
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

	*type = STR_LITERAL;
	content = extract_string(input, start, end);
	if (!content)
		return (NULL);
	
	// If double quoted and contains environment variables, expand them
	if (quote_char == '"' && is_environment_variable(content))
	{
		char *expanded = extract_env_value(content, state->envp);
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
 * Handle quoted text embedded within a word
 * This function is called when quotes are found within a continuous token

 * 
 * @param input: The input string
 * @param state: Current parsing state
 * @param quote_char: The type of quote (' or ")
 * @return: Index of the position after the closing quote, or -1 if error
 */
static int	handle_embedded_quote(char *input, t_parse_state *state, char quote_char)
{
	int end;
	
	// Find the closing quote
	end = find_closing_quote(input, state->i + 1, quote_char);
	if (end == -1)
	{
		state->error = 1; // Unclosed quote
		return (-1);
	}
	
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
	token_content = extract_quoted_content(input, state->i + 1, end, 
											quote_char, state, &token_type);
	if (!token_content)
		return (0);
	
	add_token(state->tokens, token_content, token_type, NULL);
	state->i = end + 1;
	state->start = state->i;
	state->in_word = 0;
	return (1);
}

/**
 * Handle quoted text in the input string
 * Now checks if the quote is part of a larger word or stands alone
 *
 * @param input: The input string being parsed
 * @param state: Current parsing state
 * @return: 1 if a quote was handled, 0 otherwise
 */
int	handle_quoted_text(char *input, t_parse_state *state)
{
	char	quote_char;
	int		end;
	int		is_embedded_quote;

	if (!input || !state || !input[state->i])
		return (0);

	if (!is_quote(input[state->i], &quote_char) || state->in_quote)
		return (0);

	// Determine if this quote is embedded in a word or stands alone
	is_embedded_quote = (state->in_word ||
		(state->i > 0 && !ft_is_whitespace(input[state->i - 1])));

	if (is_embedded_quote)
	{
		int new_pos = handle_embedded_quote(input, state, quote_char);
		if (new_pos == -1)
			return (1); // Error already set
		state->i = new_pos;

		// DO NOT process the token yet — let parsing continue
		return (1);
	}
	else
	{
		end = find_closing_quote(input, state->i + 1, quote_char);
		if (end == -1)
		{
			state->error = 1;
			return (1);
		}
		return process_standalone_quoted_token(input, state, end, quote_char);
	}
}
