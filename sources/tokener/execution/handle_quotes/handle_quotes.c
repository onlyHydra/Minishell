/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:24:43 by schiper           #+#    #+#             */
/*   Updated: 2025/05/01 19:23:48 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Updates quote state while parsing input
 * 
 * This function checks whether the current character
 *  opens or closes a quote block.
 * It updates the `in_quote` flag and `quote_char` accordingly.
 *
 * @param input: the input string
 * @param i: the current index in the input
 * @param in_quote: pointer to a flag indicating if we're currently inside quotes
 * @param quote_char: pointer to the active quote character (' or ")
 * @return: 1 if we're entering, exiting, or inside a quote; 0 otherwise
 */
int	update_quote_state(char *input, int i, int *in_quote, char *quote_char)
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
