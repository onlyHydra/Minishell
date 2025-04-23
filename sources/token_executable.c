/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_executable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 20:19:41 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/23 20:21:41 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
char	**get_path_dirs(char **envp)
{
	char	**path_dirs;
	int		i;
	char	*path_str;

	i = 0;
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
int	is_executable_file(char *filepath)
{
	struct stat	file_stat;

	if (access(filepath, F_OK) != 0)
		return (0);
	if (access(filepath, X_OK) != 0)
		return (0);
	if (stat(filepath, &file_stat) == 0)
		return (S_ISREG(file_stat.st_mode));
	return (0);
}

/**
 * Checks if a token is an executable with direct path
 * @param token: Command to check
 * @return: 0 if it's a command with valid direct path, 1 if not
 */
int	is_direct_executable(char *token)
{
	if (!token || !*token)
		return (1);
	if (token[0] == '/' || token[0] == '.' || token[0] == '~')
		if (is_executable_file(token))
			return (0);
	return (1);
}

/**
 * Checks if a token is in PATH directories
 * @param token: Command to check, @param envp: Environment variables
 * @return: 0 if found, 1 if not
 */
int	executable(char *token, char **envp)
{
	char	**dirs;
	char	*path;
	int		i;

	i = 0;
	if (is_direct_executable(token) == 0)
		return (0);
	dirs = get_path_dirs(envp);
	if (!dirs)
		return (1);
	while (dirs[i])
	{
		path = ft_strjoin3(dirs[i++], "/", token);
		if (!path)
		{
			free_array(dirs);
			return (1);
		}
		if (is_executable_file(path))
		{
			free(path);
			free_array(dirs);
			return (0);
		}
		free(path);
	}
	free_array(dirs);
	return (1);
}
