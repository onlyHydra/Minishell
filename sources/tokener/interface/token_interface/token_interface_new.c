/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_interface_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 12:00:00 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/11 12:30:00 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/tokener.h"

/**
 * Determine token type with specific handling for spaces and special characters
 * 
 * @param token: The token string
 * @param envp: Environment variables
 * @param state: Parsing state for filepath storage
 * @return: The determined token type
 */
t_token_type	determine_token_type(char *token, char **envp, t_parse_state *state)
{
	// Handle whitespace tokens specially
	if (token && *token && ft_is_whitespace(*token))
	{
		int i = 0;
		while (token[i] && ft_is_whitespace(token[i]))
			i++;
		if (token[i] == '\0')  // Token is only whitespace
			return (STR_LITERAL);
	}

	// Handle quote-only tokens
	if (token && *token && (*token == '\'' || *token == '"'))
	{
		int len = ft_strlen(token);
		if (len >= 2 && token[len - 1] == *token)
			return (STR_LITERAL);
	}

	// Use standard token type determination
	return decide_token_type(token, envp, state);
}

/**
 * Identify if a token contains only whitespace
 * 
 * @param token: Token string to check
 * @return: 1 if only whitespace, 0 otherwise
 */
int	is_whitespace_token(const char *token)
{
	int i;

	if (!token || !*token)
		return (0);
	
	i = 0;
	while (token[i])
	{
		if (!ft_is_whitespace(token[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * Process token value to preserve quotes while correctly handling their content
 * 
 * @param token: Original token string
 * @return: Processed token string or NULL on error
 */
char	*process_token_value(char *token)
{
	// Return exact token for whitespace or normal tokens
	if (!token || is_whitespace_token(token) || 
		(token[0] != '\'' && token[0] != '"'))
		return (ft_strdup(token));

	// For quoted tokens, preserve them as-is
	return (ft_strdup(token));
}
