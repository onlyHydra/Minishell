/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviromental_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:59:29 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 19:17:25 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Check if a character is valid for a variable name
 * Valid chars: alphanumeric and underscore
 */
int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * Free string array used for args
 */
void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * Check if a string starts with a $ character and is an environment variable
 * @param str: String to check
 * @return: 1 if it's an environment variable, 0 otherwise
 */
int is_environment_variable(const char *str)
{
	return (str && str[0] == '$' && str[1] && str[1] != ' ' && str[1] != '\t');
}

