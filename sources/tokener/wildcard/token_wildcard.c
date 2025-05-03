/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:19:30 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 16:02:10 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Match filename against a pattern with wildcards
 *
 * @param pattern: Pattern containing wildcards
 * @param filename: Filename to match against the pattern
 * @return: 1 if the filename matches the pattern, 0 otherwise
 */
int	match_pattern(const char *pattern, const char *filename)
{
	if (*pattern == '\0' && *filename == '\0')
		return (1);
	if (*pattern == '*')
	{
		while (*(pattern + 1) == '*')
			pattern++;
		if (*(pattern + 1) == '\0')
			return (1);
		while (*filename != '\0')
		{
			if (match_pattern(pattern + 1, filename))
				return (1);
			filename++;
		}
		return (match_pattern(pattern + 1, filename));
	}
	if (*pattern == *filename || (*pattern == '?' && *filename != '\0'))
		return (match_pattern(pattern + 1, filename + 1));
	return (0);
}

/**
 * checks if string has a wildcard inside of it
 * if str has quotes at any point return false
 *
 * @param str_token: The token string to check for wildcards
 * @return: 1 if token contains wildcard, 0 otherwise
 */
int	has_wildcard(char *str_token)
{
	if (ft_strchr(str_token, '\'') || ft_strchr(str_token, '"'))
		return (0);
	if (ft_strchr(str_token, '*'))
		return (1);
	return (0);
}
