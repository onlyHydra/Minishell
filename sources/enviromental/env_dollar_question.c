/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_specials.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:31:44 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 13:58:34 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "envir.h"

/**
 * Handle special variables like $? and $$
 */
char	*handle_special_var(char var_char, int exit_status)
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
