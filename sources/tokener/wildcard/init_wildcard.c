/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wildcard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:46:22 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 19:38:08 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/**
 * Initialize wildcard matches array
 *
 * @param pattern: The wildcard pattern to match against
 * @return: Directory pointer and initialized matches array in a struct
 */
t_expand_context	*init_wildcard_expand(const char *pattern)
{
	t_expand_context	*context;

	context = malloc(sizeof(t_expand_context));
	if (!context)
		return (NULL);
	context->matches = NULL;
	context->match_count = 0;
	context->dir = opendir(".");
	if (!context->dir)
	{
		free(context);
		return (NULL);
	}
	context->pattern = pattern;
	return (context);
}

/**
 * Simple wrapper for wildcard_in_dir to maintain backward compatibility
 * with existing code that might still call this function directly.
 *
 * @param pattern: The pattern to match against
 * @return: Array of matching filenames (NULL-terminated)
 */
char	**expand_wildcard_in_current_dir(const char *pattern)
{
	t_expand_context	*context;
	struct dirent		*entry;
	char				**result;

	context = init_wildcard_expand(pattern);
	if (!context)
		return (NULL);
	entry = readdir(context->dir);
	while (entry != NULL)
	{
		if (wildcard_match(context->pattern, entry->d_name))
			add_wildcard_match(context, entry->d_name);
		entry = readdir(context->dir);
	}
	result = finalize_wildcard_matches(context);
	return (result);
}
