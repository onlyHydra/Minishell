/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quoted_text.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 19:13:27 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 02:22:51 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
	* Find the closing quote index starting from
	the character after the opening quote
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

/**
 * Check if the string starts with an environment variable
 * @param str: The string to check
 * @return: 1 if starts with $, 0 otherwise
 */
static int	is_env_var(char *str)
{
	return (str && str[0] == '$' && str[1] && str[1] != ' ' && str[1] != '\t');
}

/* Modified handle_quoted_content with 4 parameters */
static char	*handle_quoted_content(char *input, t_parse_state *state, int end,
		t_token_type *type)
{
	char	*content;
	char	quote_char;

	quote_char = state->quote_char;
	*type = STR_LITERAL;
	content = extract_string(input, state->i + 1, end);
	if (!content)
		return (NULL);
	if (quote_char == '"' && is_env_var(content))
	{
		free(content);
		content = extract_string(input, state->i + 1, end);
		if (!content)
			return (NULL);
		*type = ENV_VAR;
		content = extract_env_value(content, state->envp);
	}
	if (state->expect_filename)
	{
		*type = FILENAME;
		state->expect_filename = 0;
	}
	return (content);
}

/**
 * Process quoted string content based on quote type
 * For double quotes, check for environment variables
 * For single quotes, always treat as literal string
 */
static int	process_quoted_token(char *input, t_parse_state *state, int end,
		char quote_char)
{
	char			*token_content;
	t_token_type	token_type;

	if (state->start < state->i && state->in_word)
		process_token(input, state, state->i, state->envp);
	state->quote_char = quote_char;
	token_content = handle_quoted_content(input, state, end, &token_type);
	if (!token_content)
		return (0);
	add_token(state->tokens, token_content, token_type);
	state->i = end + 1;
	state->start = state->i;
	state->in_word = 0;
	return (1);
}

/**
 * Handle quoted text in the input string
 * Manages quote tokens and their contents differently based on quote type
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
	if (is_quote(input[state->i], &quote_char) && !state->in_quote)
	{
		end = find_closing_quote(input, state->i + 1, quote_char);
		if (end != -1)
			return (process_quoted_token(input, state, end, quote_char));
		else
			state->error = 1;
		return (1);
	}
	return (0);
}
