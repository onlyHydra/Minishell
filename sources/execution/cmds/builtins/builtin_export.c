/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 01:42:16 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/06 15:27:57 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"
#include "error_message.h"
#include "minishell.h"

/**
 * Display exported variables in alphabetical order
 * Returns 0 on success
 */
int	display_exported_vars(t_env_var *env_vars)
{
	t_env_var	*current;
	t_env_var	**sorted_vars;
	int			count;
	int			i;
	int			j;
	t_env_var	*temp;

	// Count variables
	count = 0;
	current = env_vars;
	while (current)
	{
		if (current->exported)
			count++;
		current = current->next;
	}
	// Create array for sorting
	sorted_vars = (t_env_var **)malloc(sizeof(t_env_var *) * count);
	if (!sorted_vars)
		return (1);
	// Fill array with exported vars
	i = 0;
	current = env_vars;
	while (current)
	{
		if (current->exported)
		{
			sorted_vars[i] = current;
			i++;
		}
		current = current->next;
	}
	// Simple bubble sort by name
	for (i = 0; i < count - 1; i++)
	{
		for (j = 0; j < count - i - 1; j++)
		{
			if (ft_strcmp(sorted_vars[j]->name, sorted_vars[j + 1]->name) > 0)
			{
				temp = sorted_vars[j];
				sorted_vars[j] = sorted_vars[j + 1];
				sorted_vars[j + 1] = temp;
			}
		}
	}
	// Print in format: declare -x NAME="VALUE"
	for (i = 0; i < count; i++)
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(sorted_vars[i]->name, STDOUT_FILENO);
		if (sorted_vars[i]->value)
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(sorted_vars[i]->value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	free(sorted_vars);
	return (0);
}

// Adding validation function in case it's missing
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
 * Execute the export command
 * Format: export [name[=value] ...]
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
 * Validate and process export arguments
 * Returns 0 on success, 1 on error
 */
int	cmd_export(t_env_var **env_vars, char **args)
{
	int			i;
	int			status;
	char		*name;
	char		*value;
	char		*equals_pos;
	t_env_var	*existing;

	status = 0;
	if (!args || !args[0])
		return (display_exported_vars(*env_vars));
	i = 0;
	while (args[i])
	{
		equals_pos = ft_strchr(args[i], '=');
		if (equals_pos)
		{
			// Extract just the name part for validation
			*equals_pos = '\0'; // Temporarily split string
			name = args[i];
			value = equals_pos + 1;
			if (!is_valid_env_name(name))
			{
				*equals_pos = '='; // Restore string
				status = print_export_error(args[i]);
				i++;
				continue ;
			}
			// Name is valid, perform the update
			update_env_var(env_vars, name, value, 1); // Export=1
			*equals_pos = '=';                        // Restore string
		}
		else
		{
			// Case: just name (mark as exported if exists)
			name = args[i];
			if (!is_valid_env_name(name))
			{
				status = print_export_error(args[i]);
				i++;
				continue ;
			}
			existing = find_env_var(*env_vars, name);
			if (existing)
				existing->exported = 1;
			else
				update_env_var(env_vars, name, "", 1); // Empty value, exported
		}
		i++;
	}
	display_exported_vars(*env_vars);
	return (status);
}
