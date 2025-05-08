/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_wildcard_expansion1.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:39:27 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 23:46:52 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/wildcard.h"
#include "minishell.h"
#include "token_interface.h"

/**
 * Insert matches into token list
 *
 * @param token: The token to replace with matches
 * @param matches: Array of matching strings
 * @return: 1 if expansion successful, 0 otherwise
 */
static int	insert_wildcard_matches(t_token *token, char **matches)
{
	int	i;

	if (!token || !matches)
		return (0);
	if (matches[0] == NULL)
		return (0);
	free(token->value);
	token->value = ft_strdup(matches[0]);
	token->type = STR_LITERAL;
	if (!token->value)
		return (0);
	i = 1;
	while (matches[i] != NULL)
	{
		add_token(&token, ft_strdup(matches[i]), STR_LITERAL, NULL);
		i++;
	}
	return (1);
}

/**
 * Get array of matches for a wildcard token
 *
 * @param token: The token containing a wildcard pattern
 * @return: Array of matching strings or NULL if error/no matches
 */
static char	**get_wildcard_matches(t_token *token)
{
	char	**matches;

	if (!token || !token->value)
		return (NULL);
	matches = expand_wildcard_in_dir(token->value);
	if (!matches)
		return (NULL);
	return (matches);
}

/**
 * Apply wildcard expansion to a token in the token list
 * Creates new tokens for each matched file and inserts them
 *
 * @param token: The token containing a wildcard pattern
 * @return: 1 if expansion successful, 0 otherwise
 */
int	expand_wildcard_token(t_token *token)
{
	char	**matches;
	int		result;
	int		i;

	matches = get_wildcard_matches(token);
	if (!matches)
		return (0);
	result = insert_wildcard_matches(token, matches);
	i = 0;
	while (matches[i])
	{
		free(matches[i]);
		i++;
	}
	free(matches);
	return (result);
}
