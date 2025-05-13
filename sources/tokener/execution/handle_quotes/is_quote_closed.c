/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quote_closed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:27:35 by schiper           #+#    #+#             */
/*   Updated: 2025/05/13 16:14:10 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"

/**
 * Find the closing quote index starting from
 * the character after the opening quote
 */
int	find_closing_quote(char *input, int start, char quote_char)
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
 * Check if the current character is a quote and set the quote_char
 */
int	is_quote(char c, char *quote_char)
{
	if (c == '\'' || c == '"')
	{
		*quote_char = c;
		return (1);
	}
	return (0);
}
