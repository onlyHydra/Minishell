/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:54:23 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/25 00:38:03 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_env_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 23:10:50 by iatilla-          #+#    #+#             */
/*   Updated: 2025/04/23 23:50:00 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Checks if a string matches the value of any environment variable
 * Returns 1 if match found, 0 otherwise
 */
int	has_env_vars(char *str)
{
	extern char	**environ;
	int			i;
	char		*env_entry;
	char		*equal_sign;
	char		*value;

	i = 0;
	if (!str)
		return (0);
	while (environ[i])
	{
		env_entry = environ[i];
		equal_sign = ft_strchr(env_entry, '=');
		if (equal_sign)
		{
			value = equal_sign + 1;
			if (ft_strncmp(str, value, ft_strlen(str)) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}
