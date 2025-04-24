/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:48:06 by marvin            #+#    #+#             */
/*   Updated: 2025/04/24 23:46:05 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
	* Process an operator token at the current position and add it to the token list
 *
 * @param input: input string being parsed
 * @param tokens: pointer to token list to add the extracted token
 * @param position: current position in the input string
 * @return: the index of the last character of the processed operator
 */
int	process_operator_token(char *input, t_token **tokens, int position)
{
	char	*token;

	if ((input[position] == '>' && input[position + 1] == '>')
		|| (input[position] == '<' && input[position + 1] == '<')
		|| (input[position] == '&' && input[position + 1] == '&')
		|| (input[position] == '|' && input[position + 1] == '|'))
	{
		token = extract_string(input, position, position + 2);
		add_token(tokens, token, decide_token_type(token));
		return (position + 1);
	}
	token = extract_string(input, position, position + 1);
	add_token(tokens, token, decide_token_type(token));
	return (position);
}
