/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_for_quotes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:20 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/24 23:04:02 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

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
	if (!input || i < 0 || i >= ft_strlen(input))
		return (0);
	if (input[i] == '&' && input[i + 1] == '&')
		return (1);
	if (input[i] == '|' && input[i + 1] == '|')
		return (1);
	if (input[i] == '>' && input[i + 1] == '>')
		return (1);
	if (input[i] == '<' && input[i + 1] == '<')
		return (1);
	if (input[i] == '|' || input[i] == '>' || input[i] == '<'
		|| input[i] == '&' || input[i] == ';')
		return (1);

	return (0);
}
