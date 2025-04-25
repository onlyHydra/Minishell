/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_whitespace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:09 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/25 19:21:26 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Handle whitespace in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @param envp: Environment variables
 * @return: 1 if handled, 0 otherwise
 */
int	handle_whitespace(char *input, t_parse_state *state, char **envp)
{
	if (input[state->i] == ' ' || input[state->i] == '\t')
	{
		// If we were building a word, complete it
		if (state->in_word)
		{
			process_token(input, state, state->i, envp);
			state->in_word = 0;
		}
		
		// Skip all consecutive whitespace
		while (input[state->i] && (input[state->i] == ' ' || input[state->i] == '\t'))
			(state->i)++;
		
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle backslash escapes in the input string
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_backslash(char *input, t_parse_state *state)
{
	if (input[state->i] == '\\' && input[state->i + 1])
	{
		if (!state->in_word)
		{
			state->in_word = 1;
			state->start = state->i;
		}
		state->i += 2;
		return (1);
	}
	return (0);
}

/**
 * Handle backslash escapes in the input string
 * @param input: The input string
 * @return: The processed string with escapes handled
 */
char	*handle_escapes(char *input)
{
	int		i;
	int		j;
	char	*processed;

	i = 0;
	j = 0;
	processed = (char *)malloc(sizeof(char) * (ft_strlen(input) + 1));
	if (!processed)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '\\' && input[i + 1])
		{
			i++;
			processed[j++] = input[i++];
		}
		else
			processed[j++] = input[i++];
	}
	processed[j] = '\0';
	return (processed);
}

/*

For parsing my idee and theory is:
	use "correct parentheses algortihm to know if you inside "parenthese" 
	"parentheses" are defines as you wish AKA '',"",(),

	the algoritm is O(n) aka linear. it will go over the entire non-parsed input, will check
	if the parentheses are matching and closed, if not syntax error, if yes,
	you will have indexes that mark at which position the parentheses are so you know your either inside or not.





*/