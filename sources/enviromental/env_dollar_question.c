/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dollar_question.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:31:44 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 23:43:10 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "components/envir.h"
#include <unistd.h>

/**
 * Handle special variables like $? and $$
 * @param var_char The character after the $
 * @param exit_status Current exit status value
 * @return String containing the value of the special variable
 */
char	*handle_dollar_var(char var_char, int exit_status)
{
	char	*value;

	if (var_char == '?')
		return (ft_itoa(exit_status));
	else if (var_char == '$')
		return (ft_itoa(getpid()));
	else
	{
		value = (char *)malloc(1);
		if (value)
			value[0] = '\0';
		return (value);
	}
}

/**
 * Print the exit status to the terminal
 * Can be called directly when "$?" is encountered as a standalone command
 * @param exit_status Current exit status value
 * @return Exit status value (unchanged)
 */
int	print_dollar_question(int exit_status)
{
	char	*status_str;

	status_str = ft_itoa(exit_status);
	if (status_str)
	{
		write(STDOUT_FILENO, status_str, ft_strlen(status_str));
		write(STDOUT_FILENO, "\n", 1);
		free(status_str);
	}
	return (exit_status);
}

/**
 * Check if a string is the $? command
 * @param str String to check
 * @return 1 if it's $?, 0 otherwise
 */
int	is_dollar_question(const char *str)
{
	if (str && ft_strcmp(str, "$?") == 0)
		return (1);
	return (0);
}
