/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_string_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:50:55 by schiper           #+#    #+#             */
/*   Updated: 2025/05/06 15:14:57 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include <libft.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Join three strings into a newly allocated string
 */
static char	*ft_strjoin3(char *s1, char *s2, char *s3)
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
 * Check if a file exists and is executable
 * @param filepath: Full path to the file
 * @return: 1 if executable, 0 otherwise
 */
static int	is_executable_file(char *filepath)
{
	return (access(filepath, X_OK) == 0);
}

/**
 * Checks if a token is an executable with direct path
 * @param token: Command to check
 * @return: 1 if it's a command with valid direct path, 0 if not
 * @return: 1 if it's a command with valid direct path, 0 if not
 */
static int	is_direct_executable(char *string)
{
	if (!string || !*string)
		return (0);
	if (string[0] == '/' || string[0] == '.' || string[0] == '~')
		if (is_executable_file(string))
			return (1);
	return (0);
	if (!string || !*string)
		return (0);
	if (string[0] == '/' || string[0] == '.' || string[0] == '~')
		if (is_executable_file(string))
			return (1);
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
	if (is_direct_executable(string))
		return (1);
	dirs = find_path(envp);
	while (dirs != NULL && dirs[i])
	{
		path = ft_strjoin3(dirs[i++], "/", string);
		if (!path)
			break ;
		*filepath = path;
		if (is_builtin(string) == 1)
		{
			free_array(dirs);
			return (1);
		}
		if (is_executable_file(path))
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
