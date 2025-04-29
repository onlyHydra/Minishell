/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:24:43 by schiper           #+#    #+#             */
/*   Updated: 2025/04/29 23:40:28 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Handle quoted text in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
int	handle_quoted_text(char *input, t_parse_state *state)
{
	char	quote_char;
	int		j;
	char	*token_value;

	if (!input || !state || !input[state->i])
		return (0);
	if (input[state->i] == '\'' || input[state->i] == '"')
	{
		quote_char = input[state->i];
		j = state->i + 1;
		while (input[j] && input[j] != quote_char)
			j++;
		if (input[j] == quote_char)
		{
			token_value = extract_string(input, state->i + 1, j);
			if (!token_value)
				return (0);
			add_token(state->tokens, token_value, STR_LITERAL);
			state->i = j + 1;
			state->in_word = 0;
		}
		else
			state->error = 1;
		return (1);
	}
	return (0);
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
