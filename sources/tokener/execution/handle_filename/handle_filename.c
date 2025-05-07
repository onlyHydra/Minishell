/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:14:44 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/07 13:33:54 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"
#include "wildcard.h"

/**
 * Handles the filename tokenization if there is one
 * Checks if the current position follows a redirection operator
 * and processes the subsequent token as a filename
 *
 * after < ✅ Filename
 * after > ✅ Filename
 * after >> ✅ Filename
 * after << ✅ FILENAME (heredoc delimiter)
 *
 * @param input: The input string being parsed
 * @param state: Current parsing state
 * @return: 1 if a filename was handled, 0 otherwise
 */
int	handle_filename(char *input, t_parse_state *state)
{
	t_token	*last_token;

	last_token = get_last_token(*(state->tokens));
	if (!last_token)
		return (0);
	while (input[state->i] && ft_is_whitespace(input[state->i]))
		state->i++;
	if (last_token->type == REDIRECT_IN || last_token->type == REDIRECT_OUT
		|| last_token->type == REDIRECT_APPEND || last_token->type == HEREDOC)
	{
		state->expect_filename = 1;
		return (1);
	}
	return (0);
}

/**
 * Updates an existing token to be marked as a filename if it follows
 * a redirection operator during post-processing and processes wildcards
 *
 * @param tokens: The linked list of tokens to post-process
 * @return: None
 */
void	post_process_filename_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*prev;
	int		expecting_filename;

	current = tokens;
	prev = NULL;
	expecting_filename = 0;
	while (current)
	{
		if (current->type == STR_LITERAL && has_wildcard(current->value))
			current->type = WILDCARD;
		if (expecting_filename && (current->type == STR_LITERAL))
		{
			current->type = FILENAME;
			expecting_filename = 0;
			if (prev && has_wildcard(current->value))
			{
				// expand_wildcard_token(current, prev);
			}
		}
		if (current->type == REDIRECT_IN || current->type == REDIRECT_OUT
			|| current->type == REDIRECT_APPEND || current->type == HEREDOC)
			expecting_filename = 1;
		else if (current->type != STR_LITERAL && current->type != ENV_VAR)
			expecting_filename = 0;
		prev = current;
		current = current->next;
	}
}
