/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_wildcard_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:35:08 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/02 16:02:42 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
// #include "wildcard.h"

// /**
//  * Add a match to the matches array
//  *
//  * @param context: The expansion context with matches array
//  * @param filename: The filename to add
//  * @return: 1 if successful, 0 on failure
//  */
// int	add_wildcard_match(t_expand_context *context, const char *filename)
// {
// 	char	**new_matches;

// 	new_matches = (char **)realloc(context->matches, sizeof(char *)
// 			* (context->match_count + 1));
// 	if (!new_matches)
// 		return (0);
// 	context->matches = new_matches;
// 	context->matches[context->match_count] = ft_strdup(filename);
// 	if (!context->matches[context->match_count])
// 		return (0);
// 	context->match_count++;
// 	return (1);
// }

// /**
//  * Finalize matches array by adding NULL terminator
//  *
//  * @param context: The expansion context
//  * @return: The completed matches array or NULL on error
//  */
// char	**finalize_wildcard_matches(t_expand_context *context)
// {
// 	char	**matches;
// 	char	**new_matches;

// 	if (context->match_count == 0)
// 	{
// 		free(context->matches);
// 		free(context);
// 		return (NULL);
// 	}
// 	new_matches = (char **)realloc(context->matches, sizeof(char *)
// 			* (context->match_count + 1));
// 	if (!new_matches)
// 	{
// 		free_args(context->matches);
// 		free(context);
// 		return (NULL);
// 	}
// 	matches = new_matches;
// 	matches[context->match_count] = NULL;
// 	free(context);
// 	return (matches);
// }

// /**
//  * Expand a wildcard pattern into matching filenames
//  *
//  * @param pattern: The wildcard pattern to expand
//  * @return: A null-terminated array of matching filenames, or NULL if error
//  */
// char	**expand_wildcard_in_dir(const char *pattern)
// {
// 	t_expand_context	*context;
// 	struct dirent		*entry;

// 	context = init_wildcard_expand(pattern);
// 	if (!context)
// 		return (NULL);
// 	while ((entry = readdir(context->dir)) != NULL)
// 	{
// 		if (entry->d_name[0] == '.' && pattern[0] != '.')
// 			continue ;
// 		if (wildcard_match(pattern, entry->d_name))
// 		{
// 			if (!add_wildcard_match(context, entry->d_name))
// 			{
// 				free_args(context->matches);
// 				closedir(context->dir);
// 				free(context);
// 				return (NULL);
// 			}
// 		}
// 	}
// 	closedir(context->dir);
// 	return (finalize_wildcard_matches(context));
// }

// /**
//  * Extract directory path and filename pattern from a path with wildcards
//  *
//  * @param path: Full path with wildcards
//  * @param dir_path: Pointer to store directory path
//  * @param pattern: Pointer to store filename pattern
//  * @return: 1 if successful, 0 on failure
//  */
// int	split_path_and_pattern(const char *path, char **dir_path, char **pattern)
// {
// 	char	*last_slash;

// 	if (!has_wildcard((char *)path))
// 		return (0);
// 	last_slash = ft_strrchr(path, '/');
// 	if (!last_slash)
// 		return (0);
// 	*dir_path = ft_substr(path, 0, last_slash - path + 1);
// 	if (!*dir_path)
// 		return (0);
// 	*pattern = ft_strdup(last_slash + 1);
// 	if (!*pattern)
// 	{
// 		free(*dir_path);
// 		return (0);
// 	}
// 	return (1);
// }

// /**
//  * Create full paths by joining directory with match filenames
//  *
//  * @param matches: Array of filenames
//  * @param dir_path: Directory path
//  * @return: New array with full paths or NULL on error
//  */
// char	**create_full_paths(char **matches, const char *dir_path)
// {
// 	char	**result;
// 	int		match_count;
// 	int		i;

// 	match_count = 0;
// 	// Count matches
// 	while (matches[match_count])
// 		match_count++;
// 	// Allocate result array
// 	result = (char **)malloc(sizeof(char *) * (match_count + 1));
// 	if (!result)
// 		return (NULL);
// 	// Create full paths
// 	for (i = 0; i < match_count; i++)
// 	{
// 		result[i] = ft_strjoin(dir_path, matches[i]);
// 		if (!result[i])
// 		{
// 			// Handle failure
// 			while (i > 0)
// 				free(result[--i]);
// 			free(result);
// 			return (NULL);
// 		}
// 		free(matches[i]); // Free the original match
// 	}
// 	result[i] = NULL;
// 	free(matches); // Free the original array
// 	return (result);
// }

// /**
//  * Expand a wildcard pattern in the given path context
//  *
//  * @param path: The path containing a wildcard pattern
//  * @return: A null-terminated array of matching paths, or NULL if error
//  */
// char	**expand_path_with_wildcard(char *path)
// {
// 	char	*dir_path;
// 	char	*pattern;
// 	char	**matches;
// 	char	**result;
// 	char	*original_dir;

// 	// Handle simple case with no directory
// 	if (!ft_strchr(path, '/'))
// 		return (expand_wildcard_in_dir(path));
// 	// Split path into directory and pattern
// 	if (!split_path_and_pattern(path, &dir_path, &pattern))
// 		return (NULL);
// 	// Save current directory
// 	original_dir = getcwd(NULL, 0);
// 	if (!original_dir)
// 	{
// 		free(dir_path);
// 		free(pattern);
// 		return (NULL);
// 	}
// 	// Change to target directory
// 	if (chdir(dir_path) != 0)
// 	{
// 		free(dir_path);
// 		free(pattern);
// 		free(original_dir);
// 		return (NULL);
// 	}
// 	// Get matches in the target directory
// 	matches = expand_wildcard_in_dir(pattern);
// 	chdir(original_dir);
// 	free(original_dir);
// 	free(pattern);
// 	if (!matches)
// 	{
// 		free(dir_path);
// 		return (NULL);
// 	}
// 	// Create full paths
// 	result = create_full_paths(matches, dir_path);
// 	free(dir_path);
// 	return (result);
// }
