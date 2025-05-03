/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:39:22 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/03 06:38:35 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * Handle export when the argument is just NAME (no '=')
 */
static int	handle_export_name_only(t_env_var **env_vars, char *arg)
{
	t_env_var	*var;

	if (!is_valid_var_name(arg))
	{
		print_export_error(arg);
		return (1);
	}
	var = find_env_var(*env_vars, arg);
	if (var)
		var->exported = 1;
	else
		return (update_env_var(env_vars, arg, "", 1));
	return (0);
}

/**
 * Handle export when the argument is NAME=VALUE
 */
static int	handle_export_with_value(t_env_var **env_vars, char *arg,
		char *equal_pos)
{
	char	*name;
	char	*value;
	int		result;

	name = malloc(equal_pos - arg + 1);
	if (!name)
		return (1);
	ft_strlcpy(name, arg, equal_pos - arg + 1);
	if (!is_valid_var_name(name))
	{
		print_export_error(arg);
		free(name);
		return (1);
	}
	value = ft_strdup(equal_pos + 1);
	if (!value)
	{
		free(name);
		return (1);
	}
	result = update_env_var(env_vars, name, value, 1);
	free(name);
	free(value);
	return (result);
}

/**
 * Parse export argument (NAME=VALUE or NAME)
 */
static int	parse_export_arg(t_env_var **env_vars, char *arg)
{
	char	*equal_pos;

	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (handle_export_name_only(env_vars, arg));
	return (handle_export_with_value(env_vars, arg, equal_pos));
}

/**
 * Display all exported variables in export format
 */
static void	display_exported_vars(t_env_var *env_vars)
{
	t_env_var	*current;

	current = env_vars;
	while (current)
	{
		if (current->exported)
		{
			ft_putstr_fd("declare -x ", STDOUT_FILENO);
			ft_putstr_fd(current->name, STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(current->value, STDOUT_FILENO);
			ft_putstr_fd("\"\n", STDOUT_FILENO);
		}
		current = current->next;
	}
}

/**
 * Handle export command
 */
int	cmd_export(t_env_var **env_vars, char **args)
{
	int	i;
	int	exit_status;

	if (!env_vars)
		return (1);
	if (!args || !args[0])
	{
		display_exported_vars(*env_vars);
		return (0);
	}
	exit_status = 0;
	i = 0;
	while (args[i])
	{
		if (parse_export_arg(env_vars, args[i]) != 0)
			exit_status = 1;
		i++;
	}
	return (exit_status);
}
