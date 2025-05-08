/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:24:43 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 23:44:37 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"

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

/* Helper function to expand environment variables in quoted content */
static char	*expand_env_if_needed(char *content, char quote_char,
		t_parse_state *state, t_token_type *type)
{
	char	*expanded;

	if (quote_char == '"' && is_environment_variable(content))
	{
		expanded = extract_env_value(content, state->envp);
		free(content);
		if (!expanded)
			return (NULL);
		*type = ENV_VAR;
		return (expanded);
	}
	return (content);
}

/* Modified handle_quoted_content with helper function */
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
	content = expand_env_if_needed(content, quote_char, state, type);
	if (!content)
		return (NULL);
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
		process_token(input, state, state->envp);
	state->quote_char = quote_char;
	token_content = handle_quoted_content(input, state, end, &token_type);
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
