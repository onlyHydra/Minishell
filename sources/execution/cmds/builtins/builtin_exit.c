/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schiper <schiper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 18:00:00 by schiper           #+#    #+#             */
/*   Updated: 2025/05/06 20:58:45 by schiper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "minishell.h"

/* External reference to global signal indicator */
extern volatile sig_atomic_t	g_received_signal;

/**
 * Checks if the argument is a valid numeric string for exit.
 */
int	is_valid_numeric_argument(char *str)
{
	long long unsigned int	val;
	int						i;

	if (!str)
		return (-1);
	val = 0;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
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
static int	count_exit_args(char **data)
{
	int		count;
	char	**current;

	count = 0;
	current = data;
	while (current)
	{
		count++;
		current++;
	}
	if (count > 0)
		return (count - 1);
	return (0);
}

/**
 * Handles the exit built-in command
 */
int	builtin_exit(char **data, int *exit_flag)
{
	int	exit_code;
	int	arg_count;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit_code = 0;
	arg_count = count_exit_args(data);
	if (arg_count > 0)
	{
		if (is_valid_numeric_argument(*(data + 1)) != 0)
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n",
				STDERR_FILENO);
			*exit_flag = 0;
			return (2);
		}
		exit_code = ft_atoi((const char *)*(data + 1)) % 256;
		if (exit_code < 0)
			exit_code += 256;
		if (arg_count > 1)
			return (ft_putstr_fd("minishell: exit: too many arguments\n",
					STDERR_FILENO), EXIT_FAILURE);
	}
	*exit_flag = 0;
	return (exit_code);
}
