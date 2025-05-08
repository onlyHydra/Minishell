/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_dollar_question.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:31:44 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/08 13:43:56 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

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
