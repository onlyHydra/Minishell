/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:28:55 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 20:29:09 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/**
 * Process wildcard matches and get final results
 *
 * @param context: Expansion context
 * @param dir_path: Directory path
 * @param file_pattern: File pattern
 * @return: Array of matching paths or NULL
 */
static char	**process_wildcard_matches(t_expand_context *context,
		char *dir_path, char *file_pattern)
{
	char	**matches;
	
	process_directory_entries(context);
	closedir(context->dir);
	free(file_pattern);
	
	matches = finalize_wildcard_matches(context);
	if (!matches)
	{
		free(dir_path);
		return (NULL);
	}
	return (create_full_paths(matches, dir_path));
}

/**
 * Free directory path and return null on match failure
 *
 * @param dir_path: Directory path to free
 * @return: NULL
 */
static char	**free_dir_path_and_return_null(char *dir_path)
{
	free(dir_path);
	return (NULL);
}

/**
 * Expand wildcard pattern in specified directory
 *
 * @param pattern: The wildcard pattern to match against
 * @return: Array of matching filenames or NULL if no matches
 */
char	**expand_wildcard_in_dir(const char *pattern)
{
	DIR					*dir;
	char				*dir_path;
	char				*file_pattern;
	t_expand_context	*context;
	char				**matches;

	if (!init_wildcard_expansion(pattern, &dir_path, &file_pattern, &dir))
		return (NULL);
	
	context = init_expansion_context(file_pattern, dir);
	if (!context)
		return (cleanup_and_return_null(dir, dir_path, file_pattern));
	
	matches = process_wildcard_matches(context, dir_path, file_pattern);
	if (!matches)
		return (free_dir_path_and_return_null(dir_path));
	
	return (matches);
}

