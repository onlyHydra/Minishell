/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_matches.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:37:02 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 20:31:17 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

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
