/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_executable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:41 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/25 16:46:32 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

////REDO THE ENTIRE FILE IN HERE PLS BOY
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
    path_dirs=NULL;
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
	return (NULL); // PATH not found
}

/**
 * Check if a file exists and is executable
 * @param filepath: Full path to the file
 * @return: 1 if executable, 0 otherwise
 */
static int	is_executable_file(char *filepath)
{
	return (access(filepath, F_OK | X_OK) == 0);
	return (access(filepath, F_OK | X_OK) == 0);
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
int	 is_string_command(char *string, char **envp)
{
	char	**dirs;
	char	*path;
	int		i;

	i = 0;
	if (is_direct_executable(string))
	if (is_direct_executable(string))
		return (1);
	dirs = find_path(envp);
	while (dirs != NULL && dirs[i])
	dirs = find_path(envp);
	while (dirs != NULL && dirs[i])
	{
		path = ft_strjoin3(dirs[i++], "/", string);
		path = ft_strjoin3(dirs[i++], "/", string);
		if (!path)
			break ;
			break ;
		if (is_executable_file(path))
		{
			free(path);
			free_array(dirs);
			return (1);
			return (1);
		}
		free(path);
	}
	free_array(dirs);
	return (0);
	return (0);
}
