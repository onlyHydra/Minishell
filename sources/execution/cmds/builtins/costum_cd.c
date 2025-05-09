/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costum_cd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:00:00 by schiper           #+#    #+#             */
/*   Updated: 2025/05/09 14:02:21 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/builtins.h"

/**
 * Changes the working directory to the user's HOME directory
 * as specified in the environment.
 *
 * @param env_vars Pointer to the environment variable list.
 * @return EXIT_SUCCESS on success, or EXIT_FAILURE if HOME
 *  is not set or chdir fails.
 */
int	change_to_home_directory(t_env_var **env_vars)
{
	char	*home_value;

	home_value = get_env_value(*env_vars, "HOME");
	if (!home_value || !*home_value)
	{
		ft_putstr_fd("cd: HOME not set\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (chdir(home_value) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(home_value);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Updates the PWD and OLDPWD environment variables to reflect
 *  the current and previous working directories.
 *
 * @param env_vars Pointer to the environment variable list.
 */
void	update_dirs(t_env_var **env_vars)
{
	char	*current_path;
	char	*old_pwd;

	current_path = getcwd(NULL, 0);
	if (!current_path)
	{
		perror("getcwd");
		return ;
	}
	old_pwd = get_env_value(*env_vars, "PWD");
	if (old_pwd)
		update_env_var(env_vars, "OLDPWD", old_pwd, 1);
	update_env_var(env_vars, "PWD", current_path, 1);
	free(current_path);
}

/**
 * Validates that the number of arguments passed to the `cd`
 * command does not exceed the allowed count.
 *
 * @param data Pointer to the parsed command data structure.
 * @return EXIT_SUCCESS if argument count is valid, otherwise EXIT_FAILURE.
 */
static int	validate_cd_arguments(char **argv)
{
	int		count;
	char	**current;

	count = 0;
	current = argv;
	while (*current)
	{
		count++;
		current++;
	}
	if (count > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * Normalizes a path by resolving special directory references:
 * - '.' refers to the current directory
 * - '..' refers to the parent directory
 *
 * @param path The path to normalize
 * @return A newly allocated normalized path string, or NULL on failure
 */
char	*normalize_path(const char *path)
{
	char	*cwd;
	char	*result;

	if (!path)
		return (NULL);
	if (!*path)
		return (ft_strdup(""));
	if (ft_strncmp(path, "./", 2) == 0)
	{
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (NULL);
		if (ft_strlen(path) == 2)
			return (cwd);
		result = ft_strjoin(cwd, path + 1);
		free(cwd);
		return (result);
	}
	return (ft_strdup(path));
}

/**
 * Changes the working directory to the specified path, handling
 * special paths like "." and "./".
 *
 * @param target The target directory path
 * @return EXIT_SUCCESS on success, or EXIT_FAILURE if chdir fails
 */
int	change_to_directory(const char *target)
{
	char	*normalized_path;
	int		result;

	if (ft_strcmp(target, ".") == 0)
		return (EXIT_SUCCESS);
	normalized_path = normalize_path(target);
	if (!normalized_path)
	{
		ft_putstr_fd("cd: memory allocation error\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	result = EXIT_SUCCESS;
	if (chdir(normalized_path) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(normalized_path);
		result = EXIT_FAILURE;
	}
	free(normalized_path);
	return (result);
}

/**
 * Implements the behavior of the `cd` (change directory) shell built-in.
 * Handles argument validation, directory change, and environment updates.
 *
 * @param argv Array of command arguments
 * @param env_vars Pointer to the environment variable list
 * @return EXIT_SUCCESS if directory change succeeds, otherwise EXIT_FAILURE
 */
int	builtin_cd(char **argv, t_env_var **env_vars)
{
	char	*target;

	if (validate_cd_arguments(argv) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	target = *(argv + 1);
	if (!target)
	{
		if (change_to_home_directory(env_vars) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		else if (change_to_directory(target) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
	}
	update_dirs(env_vars);
	return (EXIT_SUCCESS);
}
