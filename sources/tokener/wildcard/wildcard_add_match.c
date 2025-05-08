/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_add_match.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:31:21 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 21:15:27 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/**
 * Add a new match to the matches array
 *
 * @param matches: Array of matches
 * @param filename: Filename to add
 * @param index: Index to add at
 * @return: 1 on success, 0 on failure
 */
static int	add_new_match(char **matches, const char *filename, int index)
{
	matches[index] = ft_strdup(filename);
	if (!matches[index])
		return (0);
	matches[index + 1] = NULL;
	return (1);
}

/**
 * Copy existing matches to new array
 *
 * @param new_matches: New array to copy into
 * @param old_matches: Old array to copy from
 * @param match_count: Number of matches to copy
 */
static void	copy_existing_matches(char **new_matches, char **old_matches,
		int match_count)
{
	int	i;

	i = 0;
	while (i < match_count)
	{
		new_matches[i] = old_matches[i];
		i++;
	}
}

/**
 * Update context with new matches array
 *
 * @param context: The expansion context to update
 * @param new_matches: The new matches array
 */
static void	update_context_matches(t_expand_context *context,
		char **new_matches)
{
	if (context->matches)
		free(context->matches);
	context->matches = new_matches;
	context->match_count++;
}

/**
 * Add a matching filename to the context's matches array
 *
 * @param context: The expansion context structure
 * @param filename: The filename that matched the pattern
 * @return: 1 on success, 0 on failure
 */
int	add_wildcard_match(t_expand_context *context, const char *filename)
{
	char	**new_matches;
	int		i;

	if (!should_include_filename(context, filename))
		return (1);
	new_matches = allocate_new_matches(context->match_count);
	if (!new_matches)
		return (0);
	copy_existing_matches(new_matches, context->matches, context->match_count);
	i = context->match_count;
	if (!add_new_match(new_matches, filename, i))
	{
		free(new_matches);
		return (0);
	}
	update_context_matches(context, new_matches);
	return (1);
}
