

#include "header.h"

/**
 * Helper function to free an array of strings
 */
void	ft_free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * Join three strings into a newly allocated string
 */
char	*ft_strjoin3(char *s1, char *s2, char *s3)
{
	char	*result;

	size_t len1, len2, len3;
	if (!s1 || !s2 || !s3)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	len3 = strlen(s3);
	result = (char *)malloc(len1 + len2 + len3 + 1);
	if (!result)
		return (NULL);
	strcpy(result, s1);
	strcat(result, s2);
	strcat(result, s3);
	return (result);
}

/**
 * Extract PATH entries from environment variables
 * @param envp: Environment variables array
 * @return: Array of PATH directories or NULL if not found
 */
static char	**get_path_dirs(char **envp)
{
	char	**path_dirs;
	int		i;
	char	*path_str;

	i = 0;
	while (envp[i])
	{
		// Look for the PATH environment variable
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			// Extract the path string (skip "PATH=")
			path_str = envp[i] + 5;
			// Split the path string by ':' delimiter
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
	struct stat	file_stat;

	// Check if file exists
	if (access(filepath, F_OK) != 0)
		return (0);
	// Check if we have execution permission
	if (access(filepath, X_OK) != 0)
		return (0);
	// Check if it's a regular file
	if (stat(filepath, &file_stat) == 0)
		return (S_ISREG(file_stat.st_mode));
	return (0);
}

/**
 * Check if a command is a built-in shell command
 * @param cmd: Command to check
 * @return: 1 if built-in, 0 otherwise
 */
static int	is_builtin_command(char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
			"exit", NULL};
	int			i;

	i = 0;
	while (builtins[i])
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * This function checks if the given token is an executable command
 * @param token: Command to check
 * @param envp: Environment variables from main()
 * @return: 0 if it's a command, 1 if it's not
 */
int	executable(char *token, char **envp)
{
	char	**path_dirs;
	char	*filepath;
	int		i;

	// Handle NULL or empty token
	if (!token || !*token)
		return (1);
	// Check if it's a built-in command
	if (is_builtin_command(token))
		return (0);
	// If it's an absolute or relative path, check directly
	if (token[0] == '/' || token[0] == '.' || token[0] == '~')
		return (is_executable_file(token) ? 0 : 1);
	// Get PATH directories from environment
	path_dirs = get_path_dirs(envp);
	if (!path_dirs)
		return (1); // No PATH found
	// Check each directory in PATH
	i = 0;
	while (path_dirs[i])
	{
		// Construct full path
		filepath = ft_strjoin3(path_dirs[i], "/", token);
		if (!filepath)
		{
			ft_free_array(path_dirs);
			return (1);
		}
		// Check if this path contains an executable file
		if (is_executable_file(filepath))
		{
			free(filepath);
			ft_free_array(path_dirs);
			return (0); // Found executable
		}
		free(filepath);
		i++;
	}
	ft_free_array(path_dirs);
	return (1); // Not found in any PATH directory
}
