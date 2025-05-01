/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 23:14:19 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 02:02:47 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>  // For LONG_MAX
#include "envir.h"
#include "minishell.h"

/**
 * Checks if the argument is a valid numeric string for exit.
 */
// static int	is_valid_numeric_argument(const char *str)
// {
// 	long long unsigned int	val;
// 	int						i;

// 	val = 0;
// 	i = 0;
// 	if (str[i] == '-' || str[i] == '+')
// 		i++;
// 	while (str[i])
// 	{
// 		if (!ft_isdigit(str[i]))
// 			return (-1);
// 		val = val * 10 + (str[i] - '0');
// 		if (val > LONG_MAX)
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

/**
 * Handles the custom `exit` built-in logic.
 */
// int	builtin_exit(t_list *arguments, t_parsed_data *data)
// {
// 	t_argument	*first_arg;
// 	int			exit_code;

// 	exit_code = 0;
// 	ft_putstr_fd("exit\n", STDOUT_FILENO);
// 	if (arguments)
// 	{
// 		first_arg = (t_argument *)arguments->content;
// 		if (!is_valid_numeric_argument(first_arg->word))
// 		{
// 			ft_putstr_fd("minishell: numeric argument required\n", STDERR_FILENO);
// 			data->exit = 0;
// 			return (2);
// 		}
// 		exit_code = ft_atoi(first_arg->word) % 256;
// 		if (exit_code < 0)
// 			exit_code += 256;
// 		if (ft_lstsize(arguments) > 1)
// 		{
// 			ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO);
// 			return (EXIT_FAILURE);
// 		}
// 	}
// 	data->exit = 0;
// 	return (exit_code);
// }

