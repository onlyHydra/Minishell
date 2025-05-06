/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:00:00 by schiper           #+#    #+#             */
/*   Updated: 2025/05/06 14:06:05 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

/* External reference to global signal indicator */
extern volatile sig_atomic_t	g_received_signal;

/**
 * Checks if the argument is a valid numeric string for exit.
 */
int	is_valid_numeric_argument(const char *str)
{
	long long unsigned int	val;
	int						i;

	if (!str)
		return (-1);
	val = 0;
	i = 0;
	// Skip leading sign
	if (str[i] == '-' || str[i] == '+')
		i++;
	// Check if all characters are digits
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		val = val * 10 + (str[i] - '0');
		if (val > LONG_MAX)
			return (-1);
		i++;
	}
	return (0);
}

/**
 * Count arguments in parsed_data
 */
static int	count_exit_args(t_parsed_data *data)
{
	int				count;
	t_parsed_data	*current;

	count = 0;
	current = data;
	while (current && current->data)
	{
		count++;
		current++;
	}
	// Subtract 1 for the command itself
	if (count > 0)
		return (count - 1);
	return (0);
}

/**
 * Handles the exit built-in command
 */
int	builtin_exit(t_parsed_data *data, int *exit_flag)
{
	t_parsed_data	*first_arg;
	int				exit_code;
	int				arg_count;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_code = 0;
	arg_count = count_exit_args(data);
	if (arg_count > 0)
	{
		first_arg = data + 1; // Skip "exit" command
		// Check if argument is numeric
		if (is_valid_numeric_argument(first_arg->data) != 0)
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n",
				STDERR_FILENO);
			*exit_flag = 0;
			return (2);
		}
		// Convert to exit code (modulo 256 to get valid exit code)
		exit_code = ft_atoi(first_arg->data) % 256;
		if (exit_code < 0)
			exit_code += 256;
		// Check if too many arguments
		if (arg_count > 1)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO);
			return (EXIT_FAILURE);
		}
	}
	// Signal that we're exiting, but don't modify the signal variable
	// since it's strictly for signal numbers
	*exit_flag = 0;
	return (exit_code);
}
