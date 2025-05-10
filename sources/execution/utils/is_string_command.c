/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_string_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:50:55 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 19:20:49 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/builtins.h"
#include "interfaces/builtin_interface.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Join three strings into a newly allocated string
 */
char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*result;
	size_t	len1;
	size_t	len2;
	size_t	len3;

	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	len3 = ft_strlen(s3);
	result = (char *)malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	ft_strcpy(result, s1);
	ft_strcat(result, s2);
	ft_strcat(result, s3);
	return (result);
}

/**
 * Extract PATH entries from environment variables
 * @param envp: Environment variables array
 * @return: Array of PATH directories or NULL if not found
 */
static char	**find_path(char **envp)
{
	char	**path_dirs;
	int		i;
	char	*path_str;

	i = 0;
	path_dirs = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_str = envp[i] + 5;
			path_dirs = ft_split(path_str, ':');
			if (!path_dirs)
				return (NULL);
			return (path_dirs);
		}
		i++;
	}
	return (NULL);
}

/**
 * Checks if a token is an executable with direct path
 * cases: 1 if it's directory
 * @param token: Command to check
 * @return: 1 if it's a command with valid direct path, 0 if not
 * @return: 1 if it's a command with valid direct path, 0 if not
 */

static int	is_direct_executable(char *string, char **filepath, char **envp)
{
	char	*resolved_path;

	if (!string || !*string)
		return (0);
	if (access(string, F_OK) != 0)
	{
		if (ft_strchr(string, '/') != NULL)
		{
			resolved_path = resolve_relative_path(string, envp);
			if (!resolved_path)
				return (0);
			if (access(resolved_path, X_OK) == 0)
			{
				*filepath = resolved_path;
				return (1);
			}
			free(resolved_path);
		}
		return (0);
	}
	if (access(string, X_OK) == 0)
	{
		*filepath = ft_strdup(string);
		return (1);
	}
	return (0);
}

/**
 * Checks if a token is in PATH directories
 * @param token: Command to check, @param envp: Environment variables
 * @return: 1 if executable, 0 if not executable
 * @return: 1 if executable, 0 if not executable
 */
int	is_string_command(char *string, char **envp, char **filepath)
{
	char	**dirs;
	char	*path;
	int		i;

	i = 0;
	if (is_direct_executable(string, filepath, envp))
		return (1);
	dirs = find_path(envp);
	while (dirs != NULL && dirs[i])
	{
		path = ft_strjoin3(dirs[i++], "/", string);
		if (!path)
			break ;
		*filepath = path;
		if (is_builtin(string) == 1 || access(*filepath, X_OK) == 0)
		{
			free_array(dirs);
			return (1);
		}
		free(path);
	}
	free_array(dirs);
	*filepath = NULL;
	return (0);
}
