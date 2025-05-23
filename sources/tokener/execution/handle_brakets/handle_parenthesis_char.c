/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parenthesis_char.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:24:40 by schiper           #+#    #+#             */
/*   Updated: 2025/05/08 23:44:37 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"

/**
 * Handle character-by-character tokenization
 * with special attention to parentheses
 * This should be called at the start of parsing each character
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if character was handled, 0 if regular processing should continue
 */
int	handle_parenthesis_char(char *input, t_parse_state *state, char **envp)
{
	char	*paren_token;

	if (input[state->i] == '(' || input[state->i] == ')')
	{
		if (state->in_word)
		{
			process_token(input, state, envp);
			state->in_word = 0;
		}
		paren_token = extract_string(input, state->i, state->i + 1);
		if (!paren_token)
			return (0);
		if (input[state->i] == '(')
			add_token(state->tokens, paren_token, LPAREN, NULL);
		else
			add_token(state->tokens, paren_token, RPAREN, NULL);
		state->i++;
		state->start = state->i;
		return (1);
	}
	return (0);
}
