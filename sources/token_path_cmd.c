
#include "header.h"

/**
 * Check if a command exists in PATH
 * @param cmd: The command to check
 * @return: 1 if found, 0 if not
 */
int	is_command_in_path(char *cmd)
{
	char	*path;
	int		found;

	path = getenv("PATH");
	char *path_copy, *dir, *full_path;
	found = 0;
	if (!path)
		return (0);
	path_copy = strdup(path);
	if (!path_copy)
		return (0);
	dir = strtok(path_copy, ":");
	while (dir && !found)
	{
		full_path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
		if (full_path)
		{
			sprintf(full_path, "%s/%s", dir, cmd);
			if (access(full_path, X_OK) == 0)
				found = 1;
			free(full_path);
		}
		dir = strtok(NULL, ":");
	}
	free(path_copy);
	return (found);
}

/**
 * Check if a string is an operator
 * @param str: The string to check
 * @return: 1 if it's an operator, 0 if not
 */
int	is_operator_string(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, "|", 1) == 0 || ft_strncmp(str, ";", 1) == 0)
		return (1);
	if (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0
		|| ft_strncmp(str, "<<", 1) == 0 || ft_strncmp(str, ">>", 1) == 0)
		return (1);
	return (0);
}
