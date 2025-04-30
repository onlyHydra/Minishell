/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:24:43 by schiper           #+#    #+#             */
/*   Updated: 2025/04/30 19:02:17 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Check if the current character is a quote and set the quote_char
 */
static int	is_quote(char c, char *quote_char)
{
	if (c == '\'' || c == '"')
	{
		*quote_char = c;
		return (1);
	}
	return (0);
}

/**
 * Find the closing quote index starting from 
 the character after the opening quote
 */
static int	find_closing_quote(char *input, int start, char quote_char)
{
	int	j;

	j = start + 1;
	while (input[j] && input[j] != quote_char)
		j++;
	if (input[j] == quote_char)
		return (j);
	return (-1);
}

/**
 * Extract the quoted string and update the parsing state
 */
static int	process_quoted_token(char *input, t_parse_state *state, int end)
{
	char	*token_value;

	token_value = extract_string(input, state->i + 1, end);
	if (!token_value)
		return (0);
	add_token(state->tokens, token_value, STR_LITERAL);
	state->i = end + 1;
	state->in_word = 0;
	return (1);
}

/**
 * Handle quoted text in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_quoted_text(char *input, t_parse_state *state)
{
	char	quote_char;
	int		end;

	if (!input || !state || !input[state->i])
		return (0);
	if (!is_quote(input[state->i], &quote_char))
		return (0);
	end = find_closing_quote(input, state->i, quote_char);
	if (end != -1)
		return (process_quoted_token(input, state, end));
	else
		state->error = 1;
	return (1);
}

/**
 * Handles quote characters during tokenization
 * @param input: the input string being tokenized
 * @param i: the current index in the input string
 * @param in_quote: pointer to flag indicating if currently inside a quote
 * @param quote_char: pointer to the current quote character (' or ")
 * @return (1 if a quote state is entered, exited,
	or currently in quote); 0 otherwise
 */
int	handle_quotes_tokenize(char *input, int i, int *in_quote, char *quote_char)
{
	if ((input[i] == '\'' || input[i] == '"') && !(*in_quote))
	{
		*in_quote = 1;
		*quote_char = input[i];
		return (1);
	}
	else if (*in_quote && input[i] == *quote_char)
	{
		*in_quote = 0;
		return (1);
	}
	else if (*in_quote)
		return (1);
	return (0);
}
