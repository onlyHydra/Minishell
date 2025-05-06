/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:42:16 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/06 17:04:43 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "error_message.h"
#include "minishell.h"

/**
 * Validates whether a given string is a valid environment variable name.
 * A valid name starts with a letter or underscore, followed by letters, digits,
	or underscores.
 *
 * @param name The name to validate.
 * @return 1 if the name is valid, 0 otherwise.
 */
static int	is_valid_env_name(const char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * Executes the built-in `export` command,
	which sets or marks environment variables for export.
 * Handles multiple arguments in the form `name` or `name=value`.
 *
 * @param data The parsed input containing the export command and its arguments.
 * @param env_vars Pointer to the list of environment variables.
 * @return 0 on success, non-zero on error.
 */
int	execute_export(t_parsed_data *data, t_env_var **env_vars)
{
	int		result;
	char	**args;

	if (!env_vars || !*env_vars || !data)
		return (1);
	args = get_args_from_data(data);
	result = cmd_export(env_vars, args);
	free_args(args);
	return (result);
}

/**
 * Processes an export argument in the form `name=value`.

	* Updates or creates the environment variable with
		the given value if the name is valid.
 *
 * @param env_vars Pointer to the list of environment variables.
 * @param arg The export argument string containing an '='.
 * @return 0 on success, non-zero if the name is invalid.
 */
static int	process_export_with_equals(t_env_var **env_vars, char *arg)
{
	char *name, *value, *equals_pos;
	equals_pos = ft_strchr(arg, '=');
	*equals_pos = '\0';
	name = arg;
	value = equals_pos + 1;
	if (!is_valid_env_name(name))
	{
		*equals_pos = '=';
		return (print_export_error(arg));
	}
	update_env_var(env_vars, name, value, 1);
	*equals_pos = '=';
	return (0);
}

/**
 * Processes an export argument containing only a name without an equals sign.
 * Marks the variable for export or initializes it with an empty value.
 *
 * @param env_vars Pointer to the list of environment variables.
 * @param name The variable name to process.
 * @return 0 on success, non-zero if the name is invalid.
 */
static int	process_export_name_only(t_env_var **env_vars, char *name)
{
	t_env_var	*existing;

	if (!is_valid_env_name(name))
		return (print_export_error(name));
	existing = find_env_var(*env_vars, name);
	if (existing)
		existing->exported = 1;
	else
		update_env_var(env_vars, name, "", 1);
	return (0);
}

/**

	* Handles the logic of the `export` command by validating
	and processing each argument.
 * Determines whether each argument is a name or a name-value pair.
 *
 * @param env_vars Pointer to the list of environment variables.
 * @param args Array of argument strings to process.
 * @return 0 if all arguments are valid, 1 if any argument fails.
 */
int	cmd_export(t_env_var **env_vars, char **args)
{
	char	*equals_pos;
	int		i;
	int		status;

	if (!args || !args[0])
		return (-1);
	status = 0;
	i = 0;
	while (args[i])
	{
		equals_pos = ft_strchr(args[i], '=');
		if (equals_pos)
			status |= process_export_with_equals(env_vars, args[i]);
		else
			status |= process_export_name_only(env_vars, args[i]);
		i++;
	}
	return (status);
}
