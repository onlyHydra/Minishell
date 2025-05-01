/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iatilla- <iatilla-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 22:54:23 by iatilla-          #+#    #+#             */
/*   Updated: 2025/05/01 13:54:53 by iatilla-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokener.h"

/**
 * Extract variable name from input string (after $)
 * Returns pointer to var name or NULL if invalid
 */
static char	*extract_var_name(char *str)
{
	if (!str || !*str || str[0] != '$')
		return (NULL);
	str++;
	while (*str == '$')
		str++;
	if (!*str)
		return (NULL);
	return (str);
}

/**
 * Checks if a string contains a reference to a valid environment variable
 * Now only checks if the string starts with $ followed by at least one character
 // We don't check if the variable exists in the environment anymore
 // Just that it's a valid environment variable syntax
 */
int	has_env_vars(char *str)
{
	char	*var_name;
	
	var_name = extract_var_name(str);
	if (!var_name)
	return (0);
	return (1);
}

/**
 * Check if var_name matches any entry in envp
 */
// static int	match_env_var(char *var_name, char **envp)
// {
// 	int		i;
// 	char	*equal_sign;
// 	size_t	env_name_len;
// 	i = 0;
// 	while (envp[i])
// 	{
// 		equal_sign = ft_strchr(envp[i], '=');
// 		if (equal_sign)
// 		{
// 			env_name_len = equal_sign - envp[i];
// 			if (ft_strlen(var_name) == env_name_len && ft_strncmp(envp[i],
// 					var_name, env_name_len) == 0)
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
