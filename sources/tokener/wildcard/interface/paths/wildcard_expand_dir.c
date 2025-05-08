/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand_dir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:28:55 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 00:04:17 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/wildcard.h"

/**
 * Process directory entries for wildcard matches
 *
 * @param context: Expansion context
 * @return: 1 on success, 0 on failure
 */
static int	process_directory_entries(t_expand_context *context)
{
	struct dirent	*entry;

	entry = readdir(context->dir);
	while (entry != NULL)
	{
		if (wildcard_match(context->pattern, entry->d_name))
			add_wildcard_match(context, entry->d_name);
		entry = readdir(context->dir);
	}
	return (1);
}

/**
 * Process wildcard matches and get final results
 *
 * @param context: Expansion context
 * @param dir_path: Directory path
 * @param file_pattern: File pattern
 * @return: Array of matching paths or NULL
 */
static char	**process_wildcard_matches(t_expand_context *context,
		char *dir_path)
{
	char	**matches;

	process_directory_entries(context);
	closedir(context->dir);
	matches = finalize_wildcard_matches(context);
	if (!matches)
	{
		free(dir_path);
		return (NULL);
	}
	return (create_full_paths(matches, dir_path));
}

/**
 * Initialize directory and path components for wildcard expansion
 *
 * @param pattern: The wildcard pattern to match against
 * @param dir_path: Pointer to store directory path
 * @param file_pattern: Pointer to store file pattern
 * @param dir: Pointer to store directory handle
 * @return: 1 on success, 0 on failure
 */
static int	init_wildcard_expansion(const char *pattern, char **dir_path,
		char **file_pattern, DIR **dir)
{
	if (!split_path_and_pattern(pattern, dir_path, file_pattern))
		return (0);
	*dir = opendir(*dir_path);
	if (!*dir)
	{
		free(*dir_path);
		free(*file_pattern);
		return (0);
	}
	return (1);
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
	matches = process_wildcard_matches(context, dir_path);
	free(file_pattern);
	if (matches == NULL)
		return (NULL);
	free(dir_path);
	if (!matches)
		return (NULL);
	return (matches);
}
