/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_for_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/25 19:00:32 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Handle regular text (without quotes or special characters)
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
int	handle_regular_text(char *input, t_parse_state *state, char **envp)
{
	int	j;

	if (is_operator(input, state->i) || input[state->i] == '\''
		|| input[state->i] == '"' || input[state->i] == '\\')
		return (0);
	if (!state->in_word)
	{
		state->in_word = 1;
		state->start = state->i;
	}
	j = state->i;
	while (input[j] && !is_operator(input, j) && input[j] != ' '
		&& input[j] != '\t' && input[j] != '\'' && input[j] != '"'
		&& input[j] != '\\')
		j++;
	if (j > state->i)
	{
		process_token(input, state, j, envp);
		state->i = j;
		return (1);
	}
	return (0);
}

/**
 * Check if a quote is closed properly
 * @param str: The string to check
 * @param start: Starting index of the quote
 * @param quote_char: The quote character to match (' or ")
 * @return: 1 if closed properly, 0 if unclosed
 */
int	is_quote_closed(char *str, int start, char quote_char)
{
	int	i;

	i = start + 1;
	while (str[i] && str[i] != quote_char)
		i++;
	return (str[i] == quote_char);
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

/**
 * Handles escape sequences in the input
 * @param input: the input string being tokenized
 * @param i: the current index in the input string
 * @return (2 if an escape sequence is detected); 0 otherwise
 */
int	handle_escape(char *input, int i)
{
	if (input[i] == '\\' && input[i + 1])
		return (2);
	return (0);
}

/**
 *@param input: string
 *@param i: index
 @return: true if its a operator, false if not
 */
int	is_operator(char *input, int i)
{
	if (!input || i < 0 || i >= (int)ft_strlen(input))
		return (0);
	if (input[i] == '&' && input[i + 1] == '&')
		return (1);
	if (input[i] == '|' && input[i + 1] == '|')
		return (1);
	if (input[i] == '>' && input[i + 1] == '>')
		return (1);
	if (input[i] == '<' && input[i + 1] == '<')
		return (1);
	if (input[i] == '|' || input[i] == '>' || input[i] == '<' || input[i] == '&'
		|| input[i] == ';')
		return (1);
	return (0);
}
