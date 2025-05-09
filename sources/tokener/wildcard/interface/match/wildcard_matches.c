/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matches.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:37:02 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 14:53:59 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/wildcard.h"
#include <stdlib.h>

/**
 * Finalize the wildcard matches array and clean up the context
 *
 * @param context: The expansion context structure
 * @return: The array of matched filenames (NULL-terminated)
 */
char	**finalize_wildcard_matches(t_expand_context *context)
{
	char	**result;

	if (!context)
		return (NULL);
	if (context->match_count == 0)
	{
		free(context->matches);
		free(context);
		return (NULL);
	}
	result = context->matches;
	free(context);
	return (result);
}

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
 * Determines if a filename matches a wildcard pattern
 *
 * @param pattern: The wildcard pattern
 * @param filename: The filename to check
 * @return: 1 if matched, 0 otherwise
 */
int	wildcard_match(const char *pattern, const char *filename)
{
	return (match_pattern(pattern, filename));
}
