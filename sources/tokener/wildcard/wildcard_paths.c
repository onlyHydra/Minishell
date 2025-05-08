/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:30:44 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 21:05:52 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

/**
 * Check if paths were allocated successfully
 *
 * @param dir_path: Directory path
 * @param file_pattern: File pattern
 * @return: 1 on success, 0 on failure
 */
int	check_paths_allocation(char *dir_path, char *file_pattern)
{
	if (!dir_path || !file_pattern)
	{
		if (dir_path)
			free(dir_path);
		if (file_pattern)
			free(file_pattern);
		return (0);
	}
	return (1);
}

/**
 * Split a path with wildcards into directory path and file pattern
 *
 * @param pattern: The full path pattern
 * @param dir_path: Pointer to store the directory path
 * @param file_pattern: Pointer to store the file pattern
 * @return: 1 on success, 0 on failure
 */
int	split_path_and_pattern(const char *pattern, char **dir_path,
		char **file_pattern)
{
	char	*last_slash;

	if (!pattern || !dir_path || !file_pattern)
		return (0);
	last_slash = ft_strchr(pattern, '/');
	while (last_slash)
		last_slash = ft_strchr(last_slash, '/') + 1;
	if (!last_slash)
	{
		*dir_path = ft_strdup(".");
		*file_pattern = ft_strdup(pattern);
	}
	else
	{
		*dir_path = ft_substr(pattern, 0, last_slash - pattern);
		*file_pattern = ft_strdup(last_slash);
		if ((*dir_path)[0] == '\0')
		{
			free(*dir_path);
			*dir_path = ft_strdup("/");
		}
	}
	return (check_paths_allocation(*dir_path, *file_pattern));
}

/**
 * Create a single full path based on directory and filename
 *
 * @param dir_path: The directory path
 * @param filename: The filename
 * @return: Full path string
 */
char	*create_single_path(const char *dir_path, const char *filename)
{
	if (ft_strcmp(dir_path, "/") == 0)
		return (ft_strjoin("/", filename));
	else if (ft_strcmp(dir_path, ".") == 0)
		return (ft_strdup(filename));
	else
		return (ft_strjoin(dir_path, filename));
}

/**
 * Create full paths by combining directory path with matches
 *
 * @param matches: Array of matched filenames
 * @param dir_path: Directory path to prepend to each match
 * @return: Array of full paths (NULL-terminated)
 */
char	**create_full_paths(char **matches, const char *dir_path)
{
	char	**full_paths;
	int		i;
	int		count;

	if (!matches || !dir_path)
		return (NULL);
	count = 0;
	while (matches[count])
		count++;
	full_paths = malloc(sizeof(char *) * (count + 1));
	if (!full_paths)
		return (NULL);
	i = 0;
	while (i < count)
	{
		full_paths[i] = create_single_path(dir_path, matches[i]);
		free(matches[i]);
		i++;
	}
	full_paths[count] = NULL;
	free(matches);
	return (full_paths);
}

/**
 * Initialize expansion context
 *
 * @param dir_path: Directory path
 * @param file_pattern: File pattern
 * @return: Initialized context or NULL on failure
 */
t_expand_context	*init_expansion_context(const char *file_pattern, DIR *dir)
{
	t_expand_context	*context;

	context = malloc(sizeof(t_expand_context));
	if (!context)
		return (NULL);
	context->matches = NULL;
	context->match_count = 0;
	context->pattern = file_pattern;
	context->dir = dir;
	return (context);
}

/**
 * Process directory entries for wildcard matches
 *
 * @param context: Expansion context
 * @return: 1 on success, 0 on failure
 */
int	process_directory_entries(t_expand_context *context)
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
 * Initialize directory and path components for wildcard expansion
 *
 * @param pattern: The wildcard pattern to match against
 * @param dir_path: Pointer to store directory path
 * @param file_pattern: Pointer to store file pattern
 * @param dir: Pointer to store directory handle
 * @return: 1 on success, 0 on failure
 */
int	init_wildcard_expansion(const char *pattern, char **dir_path,
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
 * Expand a path that may contain wildcards at any level
 * For complex paths with wildcards in directories (e.g., srcfile.c)
 *
 * @param path: The path to expand
 * @return: Array of matching paths (NULL-terminated)
 */
char	**expand_path_with_wildcard(char *path)
{
	return (expand_wildcard_in_dir(path));
}
