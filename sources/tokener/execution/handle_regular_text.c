/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_regular_text.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 18:34:41 by schiper           #+#    #+#             */
/*   Updated: 2025/04/30 20:24:29 by iatilla-         ###   ########.fr       */
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
		|| input[state->i] == '"' || input[state->i] == '('
		|| input[state->i] == ')')
		return (0);
	if (!state->in_word)
	{
		state->in_word = 1;
		state->start = state->i;
	}
	j = state->i;
	while (input[j] && !is_operator(input, j) && input[j] != ' '
		&& input[j] != '\t' && input[j] != '\'' && input[j] != '"'
		&& input[j] != '(' && input[j] != ')')
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
