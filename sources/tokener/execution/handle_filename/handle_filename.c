/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_filename.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 16:14:44 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 00:10:22 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"
#include "components/wildcard.h"

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
 * checks if string has a wildcard inside of it
 * if str has quotes at any point return false
 *
 * @param str_token: The token string to check for wildcards
 * @return: 1 if token contains wildcard, 0 otherwise
 */
static int	has_wildcard(char *str_token)
{
	if (ft_strchr(str_token, '\'') || ft_strchr(str_token, '"'))
		return (0);
	if (ft_strchr(str_token, '*'))
		return (1);
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
	int		expecting_filename;

	current = tokens;
	expecting_filename = 0;
	while (current)
	{
		if (current->type == STR_LITERAL && has_wildcard(current->value))
			expand_wildcard_token(current);
		if (expecting_filename && (current->type == STR_LITERAL))
		{
			current->type = FILENAME;
			expecting_filename = 0;
		}
		if (current->type == REDIRECT_IN || current->type == REDIRECT_OUT
			|| current->type == REDIRECT_APPEND || current->type == HEREDOC)
			expecting_filename = 1;
		else if (current->type != STR_LITERAL && current->type != ENV_VAR)
			expecting_filename = 0;
		current = current->next;
	}
}
