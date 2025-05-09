/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 19:30:44 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 00:05:02 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/wildcard.h"

/**
 * Check if paths were allocated successfully
 *
 * @param dir_path: Directory path
 * @param file_pattern: File pattern
 * @return: 1 on success, 0 on failure
 */
static int	check_paths_allocation(char *dir_path, char *file_pattern)
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
	while (last_slash && ft_strchr(last_slash, '/'))
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
