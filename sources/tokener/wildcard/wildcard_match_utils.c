/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:23:36 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 20:24:35 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/**
 * Check if a filename should be included in wildcard matches
 *
 * @param context: The expansion context structure
 * @param filename: The filename to check
 * @return: 1 if file should be included, 0 if it should be skipped
 */
int	should_include_filename(t_expand_context *context, const char *filename)
{
	if (!context || !filename)
		return (0);
	if (filename[0] == '.' && context->pattern[0] != '.')
		return (0);
	return (1);
}

/**
 * Allocate memory for new matches array
 *
 * @param match_count: Current number of matches
 * @return: Newly allocated array or NULL on failure
 */
char	**allocate_new_matches(int match_count)
{
	char	**new_matches;

	new_matches = malloc(sizeof(char *) * (match_count + 2));
	if (!new_matches)
		return (NULL);
	return (new_matches);
}
