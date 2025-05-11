/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:50 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 00:27:26 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"

/**
 * Captures a token and advances the state
 * 
 * @param params: Parameters containing input and environment variables
 * @param state: Current parsing state
 * @param end: Where the current token ends
 */
static void	capture_token(t_parse_params *params, t_parse_state *state, int end)
{
	if (state->start < end && !state->error)
	{
		state->i = end;  // Set the current position to the end of token
		process_token(params->input, state, params->envp);
		state->start = end;  // Reset start position for next token
	}
}

/**
 * Determines token boundaries based on shell syntax rules
 * 
 * @param input: Input string
 * @param current: Current position in string
 * @return: Position where current token ends
 */
static int	find_token_boundary(char *input, int current)
{
	char	quote_char;

	// Handle quotes
	if (input[current] == '\'' || input[current] == '"')
	{
		quote_char = input[current];
		current++;  // Move past opening quote
		
		// Find matching closing quote
		while (input[current] && input[current] != quote_char)
			current++;
		
		if (input[current] == quote_char)
			current++;  // Include closing quote
	}
	// Handle operators
	else if (is_operator_char(input[current]))
	{
		// Handle two-character operators
		if ((input[current] == '>' && input[current + 1] == '>') ||
			(input[current] == '<' && input[current + 1] == '<') ||
			(input[current] == '&' && input[current + 1] == '&') ||
			(input[current] == '|' && input[current + 1] == '|'))
			current += 2;
		else
			current++;
	}
	// Handle whitespace as a separate token
	else if (ft_is_whitespace(input[current]))
	{
		while (input[current] && ft_is_whitespace(input[current]))
			current++;
	}
	// Handle parentheses
	else if (input[current] == '(' || input[current] == ')')
	{
		current++;
	}
	// Handle regular text
	else
	{
		while (input[current] && 
			   !ft_is_whitespace(input[current]) &&
			   !is_operator_char(input[current]) &&
			   input[current] != '\'' &&
			   input[current] != '"' &&
			   input[current] != '(' &&
			   input[current] != ')')
		{
			// Handle environment variables with special care
			if (input[current] == '$')
			{
				// Include the entire env variable
				current++;
				if (input[current] == '{')
				{
					current++;
					while (input[current] && input[current] != '}')
						current++;
					if (input[current] == '}')
						current++;
				}
				else if (input[current] == '?')  // Special case for $?
				{
					current++;
				}
				else
				{
					while (input[current] && (ft_isalnum(input[current]) || input[current] == '_'))
						current++;
				}
			}
			else
				current++;
		}
	}
	return (current);
}

/**
 * Helper function to check if a character is a shell operator
 * 
 * @param c: Character to check
 * @return: 1 if operator, 0 otherwise
 */
int	is_operator_char(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == '&' || c == ';');
}

/**
 * This function is the core of the parsing process,
 * processing a segment of input by preserving exact input
 * and tokenizing based on shell syntax.
 *
 * @param params: Contains input string, segment boundaries, and environment variables
 * @param segment_state: Tracks current parsing state including position, flags, and errors
 */
void	parse_segment(t_parse_params *params, t_parse_state *segment_state)
{
	int	next_pos;

	segment_state->start = segment_state->i;
	
	while (segment_state->i < params->segment_end && !segment_state->error)
	{
		// Find where the next token ends
		next_pos = find_token_boundary(params->input, segment_state->i);
		
		// Capture the token between current position and found boundary
		if (next_pos > segment_state->i)
		{
			segment_state->i = segment_state->start;  // Reset to start of token
			capture_token(params, segment_state, next_pos);
		}
		else
		{
			// Avoid infinite loop if no progress was made
			segment_state->i++;
		}
		
		// Update start position for next token
		segment_state->start = segment_state->i;
	}
	
	// Process any remaining characters
	if (segment_state->i > segment_state->start && !segment_state->error)
	{
		segment_state->i = segment_state->start;
		process_token(params->input, segment_state, params->envp);
	}
	
	params->filepath = segment_state->filepath;
}
