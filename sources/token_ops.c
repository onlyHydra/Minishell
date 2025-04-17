/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_ops.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:48:06 by marvin            #+#    #+#             */
/*   Updated: 2025/04/16 17:48:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/**
 * Handle logical operators (&& and ||) in the input
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_logical_operators(char *input, t_parse_state *state)
{
	if (input[state->i] == '&' && input[state->i + 1] == '&')
	{
		add_token(state->tokens, extract_token(input, state->i, state->i + 2),
			AND);
		state->i += 2;
		state->start = state->i;
		return (1);
	}
	if (input[state->i] == '|' && input[state->i + 1] == '|')
	{
		add_token(state->tokens, extract_token(input, state->i, state->i + 2),
			OR);
		state->i += 2;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle double redirection operators (>> and <<)
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_double_redirection(char *input, t_parse_state *state)
{
	if (input[state->i] == '>' && input[state->i + 1] == '>')
	{
		add_token(state->tokens, extract_token(input, state->i, state->i + 2),
			REDIRECT_APPEND);
		state->i += 2;
		state->start = state->i;
		return (1);
	}
	if (input[state->i] == '<' && input[state->i + 1] == '<')
	{
		add_token(state->tokens, extract_token(input, state->i, state->i + 2),
			HEREDOC);
		state->i += 2;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle single character operators (|, >, <)
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_single_char_operators(char *input, t_parse_state *state)
{
	if (input[state->i] == '|')
	{
		add_token(state->tokens, extract_token(input, state->i, state->i + 1),
			PIPE);
		state->i += 1;
		state->start = state->i;
		return (1);
	}
	if (input[state->i] == '>')
	{
		add_token(state->tokens, extract_token(input, state->i, state->i + 1),
			REDIRECT_OUT);
		state->i += 1;
		state->start = state->i;
		return (1);
	}
	if (input[state->i] == '<')
	{
		add_token(state->tokens, extract_token(input, state->i, state->i + 1),
			REDIRECT_IN);
		state->i += 1;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle parentheses ( and )
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_parentheses(char *input, t_parse_state *state)
{
	if (input[state->i] == '(')
	{
		add_token(state->tokens, extract_token(input, state->i, state->i + 1),
			LPAREN);
		state->i += 1;
		state->start = state->i;
		return (1);
	}
	if (input[state->i] == ')')
	{
		add_token(state->tokens, extract_token(input, state->i, state->i + 1),
			RPAREN);
		state->i += 1;
		state->start = state->i;
		return (1);
	}
	return (0);
}

/**
 * Handle all operators (logical, double redirection, single char operators,
	and parentheses)
 * @param input: The input string
 * @param state: Parsing state
 * @return: 1 if handled, 0 otherwise
 */
int	handle_operators(char *input, t_parse_state *state)
{
	if (handle_logical_operators(input, state))
		return (1);
	if (handle_double_redirection(input, state))
		return (1);
	if (handle_single_char_operators(input, state))
		return (1);
	if (handle_parentheses(input, state))
		return (1);
	return (0);
}
