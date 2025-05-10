/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:59:15 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/09 15:02:10 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/envir.h"
#include "libft.h"
#include "models/envir_struct.h"

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
