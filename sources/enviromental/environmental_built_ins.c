/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environmental_built_ins.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:19:16 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/30 20:27:47 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * Check if variable name is valid
 * Valid names start with letter or underscore and contain only
 * alphanumeric characters and underscores
 */
// static int	is_valid_var_name(const char *name)
// {
// 	int	i;

// 	if (!name || !*name)
// 		return (0);
// 	if (!ft_isalpha(name[0]) && name[0] != '_')
// 		return (0);
// 	i = 1;
// 	while (name[i])
// 	{
// 		if (!ft_isalnum(name[i]) && name[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// /**
//  * Parse export argument (NAME=VALUE or NAME)
//  */
// static int	parse_export_arg(t_env_var **env_vars, char *arg)
// {
// 	char	*equal_pos;
// 	char	*name;
// 	char	*value;
// 	int		result;

// 	equal_pos = ft_strrchr(arg, '=');
// 	if (!equal_pos)
// 	{
// 		// Just mark existing var as exported
// 		if (!is_valid_var_name(arg))
// 		{
// 			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
// 			ft_putstr_fd(arg, STDERR_FILENO);
// 			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
// 			return (1);
// 		}
// 		t_env_var *var = find_env_var(*env_vars, arg);
// 		if (var)
// 			var->exported = 1;
// 		else
// 			return (update_env_var(env_vars, arg, "", 1));
// 		return (0);
// 	}
	
// 	// Handle NAME=VALUE format
// 	name = malloc(equal_pos - arg + 1);
// 	if (!name)
// 		return (1);
// 	ft_strlcpy(name, arg, equal_pos - arg + 1);
	
// 	if (!is_valid_var_name(name))
// 	{
// 		ft_putstr_fd("minishell: export: `", STDERR_FILENO);
// 		ft_putstr_fd(arg, STDERR_FILENO);
// 		ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
// 		free(name);
// 		return (1);
// 	}
	
// 	value = ft_strdup(equal_pos + 1);
// 	if (!value)
// 	{
// 		free(name);
// 		return (1);
// 	}
	
// 	result = update_env_var(env_vars, name, value, 1);
// 	free(name);
// 	free(value);
// 	return (result);
// }

// /**
//  * Display all exported variables in export format
//  */
// static void	display_exported_vars(t_env_var *env_vars)
// {
// 	t_env_var	*current;

// 	current = env_vars;
// 	while (current)
// 	{
// 		if (current->exported)
// 		{
// 			ft_putstr_fd("declare -x ", STDOUT_FILENO);
// 			ft_putstr_fd(current->name, STDOUT_FILENO);
// 			ft_putstr_fd("=\"", STDOUT_FILENO);
// 			ft_putstr_fd(current->value, STDOUT_FILENO);
// 			ft_putstr_fd("\"\n", STDOUT_FILENO);
// 		}
// 		current = current->next;
// 	}
// }

// /**
//  * Handle export command
//  */
// int	cmd_export(t_env_var **env_vars, char **args)
// {
// 	int	i;
// 	int	exit_status;

// 	if (!env_vars)
// 		return (1);
// 	if (!args || !args[0])
// 	{
// 		display_exported_vars(*env_vars);
// 		return (0);
// 	}
	
// 	exit_status = 0;
// 	i = 0;
// 	while (args[i])
// 	{
// 		if (parse_export_arg(env_vars, args[i]) != 0)
// 			exit_status = 1;
// 		i++;
// 	}
// 	return (exit_status);
// }

// /**
//  * Handle unset command
//  */
// int	cmd_unset(t_env_var **env_vars, char **args)
// {
// 	int	i;
// 	int	exit_status;

// 	if (!env_vars || !args || !args[0])
// 		return (0);
	
// 	exit_status = 0;
// 	i = 0;
// 	while (args[i])
// 	{
// 		if (!is_valid_var_name(args[i]))
// 		{
// 			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
// 			ft_putstr_fd(args[i], STDERR_FILENO);
// 			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
// 			exit_status = 1;
// 		}
// 		else if (remove_env_var(env_vars, args[i]) != 0)
// 		{
// 			// Variable not found - this is not an error in unset
// 			exit_status = -1;
// 		}
// 		i++;
// 	}
// 	return (exit_status);
// }

// /**
//  * Handle env command
//  */
// int	cmd_env(t_env_var *env_vars)
// {
// 	t_env_var	*current;

// 	current = env_vars;
// 	while (current)
// 	{
// 		if (current->exported && current->value && *current->value)
// 		{
// 			ft_putstr_fd(current->name, STDOUT_FILENO);
// 			ft_putchar_fd('=', STDOUT_FILENO);
// 			ft_putstr_fd(current->value, STDOUT_FILENO);
// 			ft_putchar_fd('\n', STDOUT_FILENO);
// 		}
// 		current = current->next;
// 	}
// 	return (0);
// }