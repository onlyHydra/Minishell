/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_relative_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:29:24 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 12:50:10 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "utils.h"

/**
 * Get the current working directory
 * @param envp: Environment variables
 * @return: Path to current directory or NULL on failure
 */
char	*get_current_directory(char **envp)
{
	char	*path;
	int		i;

	path = getcwd(NULL, 0);
	if (path)
		return (path);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
			return (ft_strdup(envp[i] + 4));
		i++;
	}
	return (NULL);
}

/**
 * Join path components with proper handling of directory separators
 * @param base: Base path
 * @param component: Path component to add
 * @return: New combined path or NULL on failure
 */
char	*join_path(char *base, char *component)
{
	char	*result;
	size_t	base_len;

	base_len = ft_strlen(base);
	if (base[base_len - 1] == '/')
	{
		result = ft_strjoin(base, component);
		return (result);
	}
	else
	{
		result = ft_strjoin3(base, "/", component);
		return (result);
	}
}

/**
 * Resolves relative path from current directory
 * @param path: Relative path to resolve
 * @param envp: Environment variables for current directory
 * @return: Absolute path or NULL on failure
 */
char	*resolve_relative_path(char *path, char **envp)
{
	char	*current_dir;
	char	*absolute_path;
	char	*resolved_path;

	if (path[0] == '/')
		return (ft_strdup(path));
	current_dir = get_current_directory(envp);
	if (!current_dir)
		return (NULL);
	if (ft_strncmp(path, "./", 2) == 0)
		absolute_path = join_path(current_dir, path + 2);
	else
		absolute_path = join_path(current_dir, path);
	free(current_dir);
	resolved_path = resolve_path(absolute_path);
	free(absolute_path);
	return (resolved_path);
}
